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
* 컨베이어 벨트가 연결 될때마다 애니메이션 클립을 변환 해주는 함수
* dir = 연결이 들어온 방향
* outDir과 같은 방향일 경우 무시한다
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
	* 연결 설계
	* 현재 outDir 과 dir이 같으면 무시(클립을 바꾸지 않음)
	* 클립을 바꿀때 클립프레임과 시간을 유지할것
	* 연결에 따라 바뀌어야 할것. angle, clip
	* O에서 반대방향으로 들어오면 I가 됨
	* O에서 수직방향으로 들어오면 L이 됨
	* T는 두가지. 
	* T2가 가운데가 OUT인 것
	* T1은 오른쪽으로 OUT인것
	* I에서 어느곳으로 연결되든 T1이 된다. 각도는 방향에 따라 달라짐
	* L에서 OUT 과 수직인 방향으로 들어오면 T2고 반대방향이면 T1
	* 
	* 반대방향은 dir 차이가 2, 수직은 1
	* T에서 연결이되면 cross가 된다
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
