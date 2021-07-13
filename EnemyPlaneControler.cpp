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

	_angle = 0;	
	_attackSpeed = 0;

	_chaseCore = true;				//Core를 향해 가고있는가?
	_isAttack = false;				//Enemy가 공격을 하고 있는가?

	_deltaX = 0.f;
	_deltaY = 0.f;
	_deltaAngle = 0.f;
	_projectileRadius = 24.f;
}

void EnemyPlaneControler::Update()
{
	_angle = _enemyInfo->GetCoreAngle();						//deltaAngle값을 저장

	if (_chaseCore)							
	{
		//여기에 angle getcoreangle있었음
		_isAttack = false;
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
	}

	if (_isAttack == true)
	{
		_attackSpeed += TIMEMANAGER->getElapsedTime();
		if (GetDistance(transform->position, _testCoreTransform->position) <= 700)
		{
			if (Math::FloatEqual(_deltaAngle, _angle) <= 30 && _attackSpeed >= 8.f)
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

	transform->SetAngle(ConvertAngleD2D(_deltaAngle));

	_projectileManager->transform->SetAngle(ConvertAngleD2D(_angle));

}

void EnemyPlaneControler::RandomAngle()		
{
	if (_randomAngle == 1)
	{
		_deltaAngle += 1.f * TIMEMANAGER->getElapsedTime();					//deltaANgle
	}
	else _deltaAngle -= 1.f * TIMEMANAGER->getElapsedTime();					//deltaAngle

}
