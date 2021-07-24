#include "stdafx.h"
#include "EnemyPlaneControler.h"
#include "ProjectileManager.h"
#include "EnemyInfo.h"
#include "Player.h"

EnemyPlaneControler::EnemyPlaneControler()
{
}

EnemyPlaneControler::~EnemyPlaneControler()
{
}

void EnemyPlaneControler::Init()
{
	_enemyInfo = gameObject->GetComponent<EnemyInfo>();
	_coreTransform = _enemyInfo->GetCoreTransform();
	_speed = _enemyInfo->GetSpeed();
	_speedX = 0.f;
	_speedY = 0.f;

	_angle = 0.f;	
	_attackSpeed = 0.f;

	_chaseCore = true;				//Core를 향해 가고있는가?
	_isAttack = false;				//Enemy가 공격을 하고 있는가?

	_deltaX = 0.f;
	_deltaY = 0.f;

	_deltaAngle = 0.f;
	_enemyRadius = 164.5f;
}

void EnemyPlaneControler::Update()
{
	_angle = _enemyInfo->GetCoreAngle();						//deltaAngle값을 저장
	//_angle = _playerTr->angle;
	_coreTransform = _enemyInfo->GetCoreTransform();
	_speed = _enemyInfo->GetSpeed();

	if (_chaseCore)
	{
		_isAttack = false;
		_deltaAngle = _angle;
	}

	if (GetDistance(transform->position, _coreTransform->position) <= 700 && _isAttack == false)
	{
		_chaseCore = false;
		_isAttack = true;
		_deltaAngle = _angle;
	}
	
	if (_isAttack == true)
	{
		_attackSpeed += TIMEMANAGER->getElapsedTime();

		if (_attackSpeed >= 0.5f && Math::FloatEqual(_deltaAngle, _angle))
		{	
			_deltaX = _enemyRadius * cosf(_deltaAngle);
			_deltaY = _enemyRadius * -sinf(_deltaAngle);

			_projectileManager->FireProjectile(transform->GetX() + _deltaX, transform->GetY() + _deltaY, ConvertAngleD2D(_deltaAngle), ENEMYPLANE);
			_attackSpeed = 0.f;
		}
		_randomAngle = RND->getInt(2);
	}

	if (GetDistance(transform->position, _coreTransform->position) >= 1300)
	{
		RandomAngle();
		_isAttack = false;
	}

	_speedX = cosf(_deltaAngle) * _speed * TIMEMANAGER->getElapsedTime();
	_speedY = -sinf(_deltaAngle) * _speed * TIMEMANAGER->getElapsedTime();

	transform->Move(_speedX, _speedY);

	transform->SetAngle(ConvertAngleD2D(_deltaAngle));
}

void EnemyPlaneControler::RandomAngle()		
{
	if (_randomAngle == 1)
	{
		_deltaAngle += 1.f * TIMEMANAGER->getElapsedTime();					//deltaANgle
	}
	else _deltaAngle -= 1.f * TIMEMANAGER->getElapsedTime();					//deltaAngle

}
