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
}

void EnemyInfo::Update()
{
	_angle = GetAngle(transform->position, _testCoreTransform->position);
	_deadTime += TIMEMANAGER->getElapsedTime();

	if (_hp < 0)
	{
		Dead();
	}
}

void EnemyInfo::Hit(int damage)
{
	_hp -= damage;
}

void EnemyInfo::Dead()
{
	gameObject->SetActive(false);
	_enemyManager->DeadEvent();
}
 