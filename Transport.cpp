#include "stdafx.h"
#include "Transport.h"
#include "Item.h"
#include "Conveyor.h"

//int moveDir[4][2] = { {1, 0},{0,1},{-1,0},{0,-1} };

void Transport::Init()
{
	_animator = gameObject->GetComponent<Animator>();
}

void Transport::Update()
{
	if (_unLackFlag == true)
	{
		_unLackTerm += TIMEMANAGER->getElapsedTime();
		if (_unLackTerm >= 1.f)
		{
			_unLackTerm = 0;
			_unLackFlag = false;
			_isLack = false;
		}
	}
	//for (int i = 0; i < _resInfo.size(); i++)
	//{
	//	_resInfo[i].second->SetSpeed(60.f);
	//	_resInfo[i].second->Move(_resInfo[i].second->GetSpeed() * TIMEMANAGER->getElapsedTime() * moveDir[_resInfo[i].first][0],
	//		_resInfo[i].second->GetSpeed() * TIMEMANAGER->getElapsedTime() * moveDir[_resInfo[i].first][1]);

	//	switch (_resInfo[i].first) {
	//	case 0:
	//		if (_resInfo[i].second->transform->GetX() > transform->GetX())
	//		{
	//			_resInfo[i].second->transform->SetPosition(transform->position);
	//			_resInfo[i].first = _outDir;
	//		}
	//		break;
	//	case 1:
	//		if (_resInfo[i].second->transform->GetY() > transform->GetY())
	//		{
	//			_resInfo[i].second->transform->SetPosition(transform->position);
	//			_resInfo[i].first = _outDir;
	//		}
	//		break;
	//	case 2:
	//		if (_resInfo[i].second->transform->GetX() < transform->GetX())
	//		{
	//			_resInfo[i].second->transform->SetPosition(transform->position);
	//			_resInfo[i].first = _outDir;
	//		}
	//		break;
	//	case 3:
	//		if (_resInfo[i].second->transform->GetY() < transform->GetY())
	//		{
	//			_resInfo[i].second->transform->SetPosition(transform->position);
	//			_resInfo[i].first = _outDir;
	//		}
	//		break;
	//	}
	//}
}
void Transport::OnTriggerEnter(GameObject* gameObject)
{
	if (gameObject->tag != TAGMANAGER->GetTag("resource"))
		return;
	((Item*)gameObject)->SetConveyor((Conveyor*)this->gameObject);
	_inResource = (Item*)gameObject;
}
void Transport::OnTriggerExit(GameObject* gameObject)
{
	if (gameObject->tag != TAGMANAGER->GetTag("resource"))
		return;
	_inResource = nullptr;
	//for (int i = 0; i < _resInfo.size(); i++)
	//{
	//	if (gameObject == _resInfo[i].second)
	//	{
	//		_resInfo[i].second->SetSpeed(0.f);
	//		_resInfo.erase(_resInfo.begin() + i);
	//		break;
	//	}
	//}
}
/***************************************************************
* �����̾� ��Ʈ�� ���� �ɶ����� �ִϸ��̼� Ŭ���� ��ȯ ���ִ� �Լ�
* dir = ������ ���� ����
* outDir�� ���� ������ ��� �����Ѵ�
****************************************************************/
void Transport::LinkConveyor(PROPDIR dir)
{
	if (_outDir == dir)
		return;

	bool clock = true;
	if (dir - _outDir == -1 || dir - _outDir == 3)
	{
		clock = false;
	}
	if (_shape == O)
	{
		if (Math::Abs(_outDir - dir) == 2)
		{
			_shape = I;
			_animator->SetClip("conveyor_I", _firstConveyorAnimator->GetCurFrameX());
		}
		else if (clock == false)
		{
			_shape = L;
			_animator->SetClip("conveyor_L", _firstConveyorAnimator->GetCurFrameX());
		}
		else if (clock == true)
		{
			_shape = L2;
			_animator->SetClip("conveyor_L2", _firstConveyorAnimator->GetCurFrameX());
		}
	}
	else if (_shape == I)
	{
		float deltaAngle = Math::Abs(transform->GetAngle() - dir * 90);
		if (deltaAngle == 180)
			return;
		if (clock == false)
		{
			_shape = T3;
			_animator->SetClip("conveyor_T3", _firstConveyorAnimator->GetCurFrameX());
		}
		else if (clock == true)
		{
			_shape = T;
			_animator->SetClip("conveyor_T", _firstConveyorAnimator->GetCurFrameX());
		}
	}
	else if (_shape == L)
	{
		float deltaAngle = transform->GetAngle() - dir * 90;
		if (deltaAngle < 0) deltaAngle += 360;
		if (deltaAngle == 90)
			return;
		if (Math::Abs(_outDir - dir) == 2)
		{
			_shape = T3;
			_animator->SetClip("conveyor_T3", _firstConveyorAnimator->GetCurFrameX());
		}
		else
		{
			_shape = T2;
			_animator->SetClip("conveyor_T2", _firstConveyorAnimator->GetCurFrameX());
		}
	}
	else if (_shape == L2)
	{
		float deltaAngle = dir * 90 - transform->GetAngle();
		if (deltaAngle < 0) deltaAngle += 360;
		if (deltaAngle == 90)
			return;
		if (Math::Abs(_outDir - dir) == 2)
		{
			_shape = T;
			_animator->SetClip("conveyor_T", _firstConveyorAnimator->GetCurFrameX());
		}
		else
		{
			_shape = T2;
			_animator->SetClip("conveyor_T2", _firstConveyorAnimator->GetCurFrameX());
		}
	}
	else
	{
		_shape = CROSS;
		_animator->SetClip("conveyor_cross", _firstConveyorAnimator->GetCurFrameX());
	}

	_animator->SetFrameTime(_firstConveyorAnimator->GetFrameTime());
	/***************************************************
	* ���� ����
	* ���� outDir �� dir�� ������ ����(Ŭ���� �ٲ��� ����)
	* Ŭ���� �ٲܶ� Ŭ�������Ӱ� �ð��� �����Ұ�
	* ���ῡ ���� �ٲ��� �Ұ�. angle, clip
	* O���� �ݴ�������� ������ I�� ��
	* O���� ������������ ������ L�� ��
	* T�� �ΰ���. 
	* T2�� ����� OUT�� ��
	* T1�� ���������� OUT�ΰ�
	* I���� ��������� ����ǵ� T1�� �ȴ�. ������ ���⿡ ���� �޶���
	* L���� OUT �� ������ �������� ������ T2�� �ݴ�����̸� T1
	* 
	* �ݴ������ dir ���̰� 2, ������ 1
	* T���� �����̵Ǹ� cross�� �ȴ�
	***************************************************/
}

void Transport::SetIsLack(bool isLack)
{
	if (isLack == true)
		_isLack = true;
	else
	{
		_unLackFlag = true;
	}
}
