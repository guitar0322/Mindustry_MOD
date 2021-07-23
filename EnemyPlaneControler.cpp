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
	//_playerTr = _player->GetComponent<Player>()->transform;
	_speedX = 0.f;
	_speedY = 0.f;

	_angle = 0.f;	
	_attackSpeed = 0.f;

	_chaseCore = true;				//Core�� ���� �����ִ°�?
	_isAttack = false;				//Enemy�� ������ �ϰ� �ִ°�?

	_deltaX = 0.f;
	_deltaY = 0.f;

	_deltaAngle = 0.f;
	_enemyRadius = 164.5f;
}

void EnemyPlaneControler::Update()
{
	_angle = _enemyInfo->GetCoreAngle();						//deltaAngle���� ����
	_coreTransform = _enemyInfo->GetCoreTransform();
	_speed = _enemyInfo->GetSpeed();
//	_playerTr = _player->GetComponent<Player>()->transform;


	if (_chaseCore)
	{
		_isAttack = false;
		_deltaAngle = _angle;
	}
	/*if (GetDistance(transform->position, _playerTr->position) <= 500)
	{
		_deltaAngle = GetAngle(transform->position, _playerTr->position);
	}*/

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

	/*
	1.Plane�� Core�� player�� �Ÿ��� ���Ѵ�
	2. Plane�� Core�� Distance�� A
	3.Core������ ���ٰ� A�� 500���� �۾����� Player�� GetAngle���� ���ϰ�, �̵� �� ,�߻�
	4.A�� 500���� Ŀ���� �ٽ� Core������ �̵�

	*/

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
