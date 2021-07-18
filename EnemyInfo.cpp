#include "stdafx.h"
#include "EnemyInfo.h"
#include "EnemyManager.h"

EnemyInfo::EnemyInfo()
{
}

EnemyInfo::~EnemyInfo()
{
}

void EnemyInfo::Init()
{
	_angle = GetAngle(transform->position, _testCoreTransform->position);
	_deadTime = 0.f;
	_isDeath = false;
	//_hp = 100;
}

void EnemyInfo::Update()
{
	_angle = GetAngle(transform->position, _testCoreTransform->position);
	_deadTime += TIMEMANAGER->getElapsedTime();

	//if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	//{
	//	_deadTime += TIMEMANAGER->getElapsedTime();
	//}
	//if (_deadTime >= 3)
	//{
	//	HitEnemy();
	//	//isDeath = true;
	//	//_enemyManager->DeadEvent();
	//}
	//if (_deadTime >= 5)
	//{
	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		_enemyManager->DeadEvent();
	}

	//if (_hp < 0 && _isDeath == false)
	//{
	//	_isDeath = true;
	//	HitEnemy();
	//}

}

void EnemyInfo::HitEnemy()
{
	_enemyManager->DeadEvent();
	_isDeath = false;
}
 