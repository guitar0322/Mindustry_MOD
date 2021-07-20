#include "stdafx.h"
#include "CameraControler.h"
#include "Player.h"
#include "PlayerControler.h"

CameraControler::CameraControler()
{
}

CameraControler::~CameraControler()
{
}

void CameraControler::Init()
{
	_speedX = 0.f;
	_speedY = 0.f;
	_angle = 0.f;
	_speed = 4000.f;
	_accel = 30.f;
	_deltaX = 0.f;
}

void CameraControler::Update()
{
	_angle = GetAngle(MainCam->transform->position, _player->transform->position);

	_speedX = cosf(_angle) * _speed * TIMEMANAGER->getElapsedTime();
	_speedY = -sinf(_angle) * _speed * TIMEMANAGER->getElapsedTime();

	MainCam->transform->Move(_speedX, _speedY);

	/*if (MainCam->transform->GetX() > _player->transform->GetX() &&
		MainCam->transform->GetY() > _player->transform->GetY())
	{
		_deltaX = MainCam->transform->GetX() - _player->transform->GetX();
		_deltaY = MainCam->transform->GetY() - _player->transform->GetY();

		if (_deltaX >= _speedX * TIMEMANAGER->getElapsedTime() &&
			_deltaY >= _speedY * TIMEMANAGER->getElapsedTime())
		{
			MainCam->transform->Move(-_speedX, -_speedY);
		}

		else if (_deltaX <= _speedX * TIMEMANAGER->getElapsedTime() &&
				_deltaY >= _speedY * TIMEMANAGER->getElapsedTime())
		{
			MainCam->transform->Move(-_deltaX, _speedY);
		}
	
		else if (_deltaX >= _speedX * TIMEMANAGER->getElapsedTime() &&
				_deltaY <= _speedY * TIMEMANAGER->getElapsedTime())
		{
			MainCam->transform->Move(-_speedX, -_deltaY);
		}
	}

	if (MainCam->transform->GetX() < _player->transform->GetX() &&
		MainCam->transform->GetY() < _player->transform->GetY())
	{
		_deltaX = _player->transform->GetX() - MainCam->transform->GetX();
		_deltaY = _player->transform->GetY() - MainCam->transform->GetY();

		if (_deltaX >= _speedX * TIMEMANAGER->getElapsedTime() &&
			_deltaY >= _speedY * TIMEMANAGER->getElapsedTime())
		{
			MainCam->transform->Move(_speedX, -_speedY);
		}

		else if (_deltaX <= _speedX * TIMEMANAGER->getElapsedTime() &&
			_deltaY >= _speedY * TIMEMANAGER->getElapsedTime())
		{
			MainCam->transform->Move(_deltaX, _speedY);
		}

		else if (_deltaX >= _speedX * TIMEMANAGER->getElapsedTime() &&
			_deltaY <= _speedY * TIMEMANAGER->getElapsedTime())
		{
			MainCam->transform->Move(_speedX, -_deltaY);
		}
	}*/





	//if (_deltaX < _speedX && _deltaY < _speedY)
	//{
	//	MainCam->transform->Move(_deltaX * TIMEMANAGER->getElapsedTime(), _deltaY * TIMEMANAGER->getElapsedTime());
	//}

	//if (Math::FloatEqual(_player->transform->GetY(), MainCam->GetRenderHeight() / 2) <= 100
	//	&& Math::FloatEqual(_player->transform->GetX(), MainCam->GetRenderWidth() / 2) <= 100)
	//{
	//	MainCam->transform->Move(0, 0);
	//}
	//if (Math::FloatEqual(_speedX, MainCam->GetRenderWidth() / 2 ) <= 100 && Math::FloatEqual(_speedY, MainCam->GetRenderHeight() / 2 ) <= 100)
	//{
	//	//MainCam->transform->Move(0, 0);
	//	//MainCam->transform->Move(_deltaX * TIMEMANAGER->getElapsedTime(), _deltaY * TIMEMANAGER->getElapsedTime());
	//}
}

void CameraControler::PlayerRespawn()
{
	//if(_player->controler->GetPlayerRespawn() == true)
	//_player->controler->Respawn();
}

