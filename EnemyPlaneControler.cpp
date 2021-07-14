#include "stdafx.h"
#include "EnemyPlaneControler.h"
#include "ProjectileManager.h"
EnemyPlaneControler::EnemyPlaneControler()
{
}

EnemyPlaneControler::~EnemyPlaneControler()
{
}

void EnemyPlaneControler::Init()
{
	_enemyInfo = gameObject->GetComponent<EnemyInfo>();
	_speed = _enemyInfo->GetSpeed();
	
	_speedX = 0.f;
	_speedY = 0.f;

	_angle = 0.f;	
	_attackSpeed = 0.f;

	_chaseCore = true;				//Core를 향해 가고있는가?
	_isAttack = false;				//Enemy가 공격을 하고 있는가?
	_weaponRebound = false;

	_deltaX = 0.f;
	_deltaY = 0.f;
	_deltaAngle = 0.f;
	_projectileRadius = 24.f;

	_weaponRadius = 70.f;
	_rebound = 630.f;
	_reboundTime = 0.f;

	_x = 0.f;
	_y = 0.f;

	_weaponCorrectionX, _weaponCorrectionY = 0.f;
}

void EnemyPlaneControler::Update()
{
	_angle = _enemyInfo->GetCoreAngle();						//deltaAngle값을 저장

	if (_chaseCore)							
	{
		_isAttack = false;
		_weaponRebound = false;
		_deltaAngle = _angle;
	}

	if (GetDistance(transform->position, _testCoreTransform->position) <= 800 && _isAttack == false)   //200
	{
		_chaseCore = false;											//getangle값을 안 주기 위함 false되면 그 전의 Angle값이 게속 남아있음
		_isAttack = true;
		_randomAngle = RND->getInt(2);

		_deltaX = _projectileRadius * cosf(_deltaAngle);
		_deltaY = _projectileRadius * -sinf(_deltaAngle);
		 
		_projectileManager->FireProjectile(transform->GetX() + _deltaX, transform->GetY() + _deltaY, _deltaAngle, PROJECTILE_TYPE::ENEMY);
		_weaponRebound = true;
	}

	if (_isAttack == true)
	{
		_attackSpeed += TIMEMANAGER->getElapsedTime();
		if (GetDistance(transform->position, _testCoreTransform->position) <= 700)
		{
			if (Math::FloatEqual(_deltaAngle, _angle) <= 30 && _attackSpeed >= 7.f)
			{
				_isAttack = false;
				_attackSpeed = 0.f;
			}
		}
	}
	
	if (GetDistance(transform->position, _testCoreTransform->position) >= 900)
	{
		RandomAngle();
	}

	_speedX = cosf(_deltaAngle) * _speed * TIMEMANAGER->getElapsedTime();	//deltaAngle 
	_speedY = -sinf(_deltaAngle) * _speed * TIMEMANAGER->getElapsedTime();	//deltaAngle 

	transform->Move(_speedX, _speedY);
	
	_weaponCorrectionX = cosf(_deltaAngle) * _weaponRadius;
	_weaponCorrectionY = -sinf(_deltaAngle) * _weaponRadius;

	transform->GetChild(0)->SetPosition(transform->GetX() + _weaponCorrectionX * 1.5f, transform->GetY() + _weaponCorrectionY * 1.5f);
	//transform->GetChild(0)->SetScale(3, 3);

	_x = GetAngle(transform->position, _testCoreTransform->position);
	_x = _y;

	float PI = Math::PI;
	if(_weaponRebound)
	{
		if (_x <= Math ::PI || _x >= -Math::PI)
		{
			transform->GetChild(0)->Move(_rebound * TIMEMANAGER->getElapsedTime(), _rebound * TIMEMANAGER->getElapsedTime() + _y);
			_reboundTime += TIMEMANAGER->getElapsedTime();
			     
			if (_reboundTime >= 1.f)
			{
				transform->GetChild(0)->Move(-_rebound * TIMEMANAGER->getElapsedTime(), -_rebound * TIMEMANAGER->getElapsedTime());
				_reboundTime = 0.f;
				_weaponRebound = false;
			}
		}
		//else
		//{
		//	transform->GetChild(0)->Move(-_rebound * TIMEMANAGER->getElapsedTime() , -_rebound * TIMEMANAGER->getElapsedTime()- _y);
		//	_reboundTime += TIMEMANAGER->getElapsedTime();
		//
		//	if (transform->GetChild(0)->GetX() >= transform->GetX() && _reboundTime >= 1.f)
		//	{
		//		transform->GetChild(0)->Move(_rebound * TIMEMANAGER->getElapsedTime(), _rebound * TIMEMANAGER->getElapsedTime());
		//		_reboundTime = 0.f;
		//		_weaponRebound = false;
		//	}
		//}
	}

	transform->SetAngle(ConvertAngleD2D(_deltaAngle));
	transform->GetChild(0)->SetAngle(ConvertAngleD2D(_deltaAngle));
}

void EnemyPlaneControler::RandomAngle()		
{
	if (_randomAngle == 1)
	{
		_deltaAngle += 1.f * TIMEMANAGER->getElapsedTime();					//deltaANgle
	}
	else _deltaAngle -= 1.f * TIMEMANAGER->getElapsedTime();					//deltaAngle

}
