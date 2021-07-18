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
	isDeath = false;
}

void EnemyInfo::Update()
{
	_angle = GetAngle(transform->position, _testCoreTransform->position);

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_deadTime += TIMEMANAGER->getElapsedTime();
	}
	if (_deadTime >= 3)
	{
		HitEnemy();
		//isDeath = true;
		//_enemyManager->DeadEvent();
	}
}

void EnemyInfo::HitEnemy()
{
	_enemyManager->DeadEvent();
}
