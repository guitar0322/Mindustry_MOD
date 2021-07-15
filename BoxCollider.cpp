#include "stdafx.h"
#include "BoxCollider.h"

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
	COLLIDERMANAGER->AddCollider(this);
}

void BoxCollider::Update()
{
	_rc = RectMakeCenter(transform->GetX(), transform->GetY(), _width, _height);
	TriggerEventHandler();
}
/********************************************************************
* @bool CheckCollision : 씬의 모든 충돌체와 충돌여부 검사
* 충돌이 발생하면 true, 아니면 false를 반환
* 충돌이 발생했을때 OnCollision이벤트 호출,
* 겹쳐진 _intersectRc의 크기만큼 밀어냄
* isTrigger가 true면 OnCollisionEnter를 발생, _overlapColV에 충돌체 추가
*********************************************************************/
bool BoxCollider::CheckCollision()
{
	vector<BoxCollider*> colV = COLLIDERMANAGER->GetColliderVector();
	_rc = RectMakeCenter(transform->GetX(), transform->GetY(), _width, _height);
	bool result = false;
	for (int i = 0; i < colV.size(); i++)
	{
		if (colV[i] == this) continue;
		if (colV[i]->gameObject->isActive == false) continue;
		if (colV[i]->enable == false) continue;

		if (IntersectRect(&_intersectRc, &this->_rc, &colV[i]->_rc))
		{
			if (this->_isTrigger == false && colV[i]->_isTrigger == false)
			{
				float w = _intersectRc.right - _intersectRc.left;
				float h = _intersectRc.bottom - _intersectRc.top;
				if (w > h)
				{
					if (_intersectRc.bottom == colV[i]->_rc.bottom)
					{
						this->transform->MoveY(h);
					}
					else if (_intersectRc.top == colV[i]->_rc.top)
					{
						this->transform->MoveY(-h);
					}
				}
				else
				{
					if (_intersectRc.left == colV[i]->_rc.left)
					{
						this->transform->MoveX(-w);
					}
					else if (_intersectRc.right == colV[i]->_rc.right)
					{
						this->transform->MoveX(w);
					}
				}
				result = true;
				this->gameObject->OnCollision(colV[i]->gameObject);
			}
			else
			{
				AddOverlapCol(colV[i]);
				colV[i]->AddOverlapCol(this);
			}
		}
	}

	return result;
}
/***********************************************************
* @void TriggerEventHandler : _overlapColV를 통해 TriggerEvent함수 호출
* _overlapColV에 있는 충돌체와 Intersect연산 수행
* 겹쳐져 있을 경우 OnTriggerStay를 호출
* 겹쳐져 있을 경우 OnTriggerExit을 호출
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
* @void RemoveOverlapCol : _overlapColV에서 충돌체를 제거
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
* @void AddOverlapCol : _overlapColV에 충돌체를 추가
* _overlapColV에 이미 같은 충돌체가 있을 경우 추가하지 않음
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
	for (int i = 0; i < _overlapColV.size(); i++)
	{
		this->gameObject->OnTriggerExit(_overlapColV[i]->gameObject);
		_overlapColV[i]->gameObject->OnTriggerExit(this->gameObject);
		RemoveOverlapCol(_overlapColV[i]);
	}
	//COLLIDERMANAGER->RemoveCollider(this);
}

void BoxCollider::OnEnable()
{
	COLLIDERMANAGER->AddCollider(this);

	//COLLIDERMANAGER->InsertCollider(this);
}