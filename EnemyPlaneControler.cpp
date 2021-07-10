#include "stdafx.h"
#include "EnemyPlaneControler.h"

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
	//_angle = _enemyInfo->GetAngle();

	_speedX = 0.f;
	_speedY = 0.f;
}

