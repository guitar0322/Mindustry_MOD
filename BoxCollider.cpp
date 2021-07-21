#include "stdafx.h"
#include "BoxCollider.h"
#include <iostream>

using namespace std;

BoxCollider::BoxCollider()
{
	_width = 100;
	_height = 100;
	_isTrigger = true;
	//_colliderCheckOffset = 50;
}

BoxCollider::~BoxCollider()
{

}

void BoxCollider::Init()
{
	//COLLIDERMANAGER->InsertCollider(this);
	_rc = RectMakeCenter(transform->GetX(), transform->GetY(), _width, _height);
	_partitionIdx = COLLIDERMANAGER->GetIntersectPartition(_rc);
	COLLIDERMANAGER->AddCollider(this);
}

void BoxCollider::Update()
{
	TriggerEventHandler();
}

/********************************************************************
* @bool CheckCollision : ���� ��� �浹ü�� �浹���� �˻�
* �浹�� �߻��ϸ� true, �ƴϸ� false�� ��ȯ
* �浹�� �߻������� OnCollision�̺�Ʈ ȣ��,
* ������ _intersectRc�� ũ�⸸ŭ �о
* isTrigger�� true�� OnCollisionEnter�� �߻�, _overlapColV�� �浹ü �߰�
*********************************************************************/
bool BoxCollider::CheckCollision()
{
	_rc = RectMakeCenter(transform->GetX(), transform->GetY(), _width, _height);
	_partitionIdx = COLLIDERMANAGER->ChangeColliderIdx(this);
	vector<vector<BoxCollider*>> partitionColV = COLLIDERMANAGER->GetPartitionColliderV(_partitionIdx);
	bool result = false;
	for (int i = 0; i < partitionColV.size(); i++)
	{
		for (int j = 0; j < partitionColV[i].size(); j++)
		{
			if (partitionColV[i][j] == this) continue;

			if (partitionColV[i][j]->gameObject->isActive == false) continue;

			if (partitionColV[i][j]->enable == false) continue;

			if (IntersectRect(&_intersectRc, &this->_rc, &partitionColV[i][j]->_rc))
			{
				if (this->_isTrigger == false && partitionColV[i][j]->_isTrigger == false)
				{
					float w = _intersectRc.right - _intersectRc.left;
					float h = _intersectRc.bottom - _intersectRc.top;
					if (w > h)
					{
						if (_intersectRc.bottom == partitionColV[i][j]->_rc.bottom)
						{
							this->transform->MoveY(h);
						}
						else if (_intersectRc.top == partitionColV[i][j]->_rc.top)
						{
							this->transform->MoveY(-h);
						}
					}
					else
					{
						if (_intersectRc.left == partitionColV[i][j]->_rc.left)
						{
							this->transform->MoveX(-w);
						}
						else if (_intersectRc.right == partitionColV[i][j]->_rc.right)
						{
							this->transform->MoveX(w);
						}
					}
					result = true;
					this->gameObject->OnCollision(partitionColV[i][j]->gameObject);
				}
				else
				{
					AddOverlapCol(partitionColV[i][j]);
					partitionColV[i][j]->AddOverlapCol(this);
				}
			}
		}
	}
	return result;
}

/***********************************************************
* @void TriggerEventHandler : _overlapColV�� ���� TriggerEvent�Լ� ȣ��
* _overlapColV�� �ִ� �浹ü�� Intersect���� ����
* ������ ���� ��� OnTriggerStay�� ȣ��
* ������ ���� ��� OnTriggerExit�� ȣ��
************************************************************/
void BoxCollider::TriggerEventHandler()
{
	for (int i = 0; i < _overlapColV.size(); i++)
	{
		if (!IntersectRect(&_overlapColV[i]->_rc, &this->_rc) || _overlapColV[i]->gameObject->isActive == false)
		{
			this->gameObject->OnTriggerExit(_overlapColV[i]->gameObject);
			_overlapColV[i]->gameObject->OnTriggerExit(this->gameObject);
			RemoveOverlapCol(_overlapColV[i]);
		}
		else
		{
			wstring name = gameObject->name;
			this->gameObject->OnTriggerStay(_overlapColV[i]->gameObject);
			_overlapColV[i]->gameObject->OnTriggerStay(this->gameObject);
		}
	}
}

void BoxCollider::SetWidth(float width)
{
	this->_width = width;
	_rc = RectMakeCenter(transform->GetX(), transform->GetY(), width, _height);
}

void BoxCollider::SetHeight(float height)
{
	this->_height = height;
	_rc = RectMakeCenter(transform->GetX(), transform->GetY(), _width, height);
}

void BoxCollider::SetSize(float width, float height)
{
	this->_width = width;
	this->_height = height;
	_rc = RectMakeCenter(transform->GetX(), transform->GetY(), width, height);
}
/*****************************************************************
* @void RemoveOverlapCol : _overlapColV���� �浹ü�� ����
*******************************************************************/
void BoxCollider::RemoveOverlapCol(BoxCollider* exitCollider)
{
	for (int i = 0; i < _overlapColV.size(); i++)
	{
		if (exitCollider == _overlapColV[i])
		{
			_overlapColV.erase(_overlapColV.begin() + i);
			break;
		}
	}
}

/**************************************************************
* @void AddOverlapCol : _overlapColV�� �浹ü�� �߰�
* _overlapColV�� �̹� ���� �浹ü�� ���� ��� �߰����� ����
***************************************************************/
void BoxCollider::AddOverlapCol(BoxCollider* overlapCollider)
{
	for (int i = 0; i < _overlapColV.size(); i++)
	{
		if (_overlapColV[i] == overlapCollider)
		{
			return;
		}
	}
	_overlapColV.push_back(overlapCollider);
	gameObject->OnTriggerEnter(overlapCollider->gameObject);
}

void BoxCollider::RefreshPartition()
{
	_rc = RectMakeCenter(transform->GetX(), transform->GetY(), _width, _height);
	_partitionIdx = COLLIDERMANAGER->ChangeColliderIdx(this);
}

void BoxCollider::Render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		D2DRENDERER->DrawRectangle(_rc, D2DRenderer::DefaultBrush::Green);
	}
}

void BoxCollider::OnDisable()
{
	COLLIDERMANAGER->EraseCollider(this);
	int colNum = _overlapColV.size();
	for (int i = 0; i < colNum; i++)
	{
		this->gameObject->OnTriggerExit(_overlapColV[0]->gameObject);
		_overlapColV[0]->gameObject->OnTriggerExit(this->gameObject);
		RemoveOverlapCol(_overlapColV[0]);
	}
	//COLLIDERMANAGER->RemoveCollider(this);
}

void BoxCollider::OnEnable()
{
	COLLIDERMANAGER->AddCollider(this);

	//COLLIDERMANAGER->InsertCollider(this);
}