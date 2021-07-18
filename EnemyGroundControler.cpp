#include "stdafx.h"
#include "EnemyGroundControler.h"
#include "ProjectileManager.h"
#include "EnemyInfo.h"

EnemyGroundControler::EnemyGroundControler()
{
}

EnemyGroundControler::~EnemyGroundControler()
{
}

void EnemyGroundControler::Init()
{
	_enemyInfo = gameObject->GetComponent<EnemyInfo>();
	_speed = _enemyInfo->GetSpeed();
	_testCoreTransform = _enemyInfo->GetCoreTransform();
	_angle = 0.f;
	_speedX = 0.f;
	_speedY = 0.f;
	
	_deltaX = 0.f;
	_deltaY = 0.f;
	_deltaAngle = 0.f;

	_attackSpeed = 0.f;
	_enemyRadius = 57.f;

	_chaseCore = true;
	_isAttack = false;

	_leftFire = true;
}

void EnemyGroundControler::Update()
{
	_testCoreTransform = _enemyInfo->GetCoreTransform();
	_speed = _enemyInfo->GetSpeed();
	_angle = GetAngle(transform->position, _testCoreTransform->position);

	if (_chaseCore)
	{
		_deltaAngle = _angle;
		_isAttack = false;
	}

	if (GetDistance(transform->position, _testCoreTransform->position) <= 1000)
	{
		_chaseCore = false;
		_isAttack = true;
	}

	if (GetDistance(transform->position, _testCoreTransform->position) >= 700 && !_chaseCore)
	{
		_chaseCore = true;
	}

	if (_isAttack)
	{
		_attackSpeed += TIMEMANAGER->getElapsedTime();
		_deltaX = cosf(_deltaAngle) * _enemyRadius;
		_deltaY = -sinf(_deltaAngle) * _enemyRadius;
		if (_attackSpeed >= 1.f && _leftFire == false)
		{
			_projectileManager->FireProjectile(transform->GetX() + _deltaX + 50, transform->GetY() + _deltaY, ConvertAngleD2D(_deltaAngle), PROJECTILE_TYPE::ENEMYGROUND);
			_leftFire = true;	
			_attackSpeed = 0.f;
		}

		if (_attackSpeed >= 1.f && _leftFire == true)
		{
			_projectileManager->FireProjectile(transform->GetX() + _deltaX - 50, transform->GetY() + _deltaY, ConvertAngleD2D(_deltaAngle), PROJECTILE_TYPE::ENEMYGROUND);
			_leftFire = false;
			_attackSpeed = 0.f;
		}
	}

	_speedX = cosf(_deltaAngle) * _speed * TIMEMANAGER->getElapsedTime();
	_speedY = -sinf(_deltaAngle) * _speed * TIMEMANAGER->getElapsedTime();

	transform->Move(_speedX, _speedY);
	transform->SetAngle(ConvertAngleD2D(_angle));
}
