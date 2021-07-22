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


}

void EnemyInfo::Hit(int damage)
{
	_hp -= damage;
	if (_hp < 0)
	{
		Dead();
	}
}

void EnemyInfo::Dead()
{
	EFFECTMANAGER->EmissionEffect("explosion", transform->GetX(), transform->GetY(), 0);
	EFFECTMANAGER->ActiveSmokeParticle(transform->GetX(), transform->GetY());
	gameObject->SetActive(false);
	_enemyManager->DeadEvent();
}
 