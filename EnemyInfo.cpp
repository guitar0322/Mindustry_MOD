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
	//_isDeath = false;
}

void EnemyInfo::Update()
{
	_angle = GetAngle(transform->position, _testCoreTransform->position);
	_deadTime += TIMEMANAGER->getElapsedTime();

	//if (_hp < 0 && _isDeath == false)
	//{
	//	_isDeath = true;
	//	HitEnemy();
	//}

	//if (KEYMANAGER->isOnceKeyDown('P'))
	//{
	//	_enemyManager->DeadEvent();
	//}
	//if (_hp < 0)
	//{
	//	_enemyManager->DeadEvent();
	//	_isDeath = false;
	//}
	if (_hp < 0)
	{
		//gameObject->SetActive(false);
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
	//_isDeath = false;
}
 