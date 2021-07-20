#include "stdafx.h"
#include "CameraControler.h"

CameraControler::CameraControler()
	:_angle(0), _speed(4000.f), _speedX(0), _speedY(0)
{

}

CameraControler::~CameraControler()
{

}

void CameraControler::Init()
{

}

void CameraControler::Update()
{
	_angle = GetAngle(MainCam->transform->position, _playerTr->position);

	_speedX = _speed * cosf(_angle) * TIMEMANAGER->getElapsedTime();
	_speedY = _speed * -sinf(_angle) * TIMEMANAGER->getElapsedTime();

	float deltaX = _playerTr->GetX() - MainCam->transform->GetX();
	float deltaY = _playerTr->GetY() - MainCam->transform->GetY();

	if (Math::FloatEqual(MainCam->transform->GetX(), _playerTr->GetX()) == false ||
		Math::FloatEqual(MainCam->transform->GetY(), _playerTr->GetY()) == false)
	{
		if (Math::Abs(deltaX) <= Math::Abs(_speedX))
		{
			MainCam->transform->MoveX(deltaX);
		}
		else
		{
			MainCam->transform->MoveX(_speedX);
		}

		if (Math::Abs(deltaY) <= Math::Abs(_speedY))
		{
			MainCam->transform->MoveY(deltaY);
		}
		else
		{
			MainCam->transform->MoveY(_speedY);
		}
	}
}

