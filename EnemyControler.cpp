#include "stdafx.h"
#include "EnemyControler.h"
#include "EnemyObject.h"
#include "EnemyInfo.h"
#include "ProjectileManager.h"
EnemyControler::EnemyControler()
{
}

EnemyControler::~EnemyControler()
{
}

void EnemyControler::Init()
{
	//Scene에서 PlaneControler를 Add해줬따
	//그리고 PlaneControler Init을 했다
	//PlaneControler의 Init이 없어서 그 부모인
	//EnemyControler의 Init이 실행됨
	//그래서 EnemyInfo를 GetComponent으로 바로 가져올수 있음	

	/*_enemyInfo = gameObject->GetComponent<EnemyInfo>();
	_speed = _enemyInfo->GetSpeed();
	_angle = _enemyInfo->GetAngle();

	_speedX = 0.f;
	_speedY = 0.f;*/
	//_angle = _enemyInfo->GetCoreAngle();

	//_projectileManager = gameObject->GetComponent<ProjectileManager>();
	_speedX = 0.f;
	_speedY = 0.f;

}

void EnemyControler::Update()
{
	//_speedX = cosf(_angle) * _speed * TIMEMANAGER->getElapsedTime();
	//_speedY = -sinf(_angle) * _speed * TIMEMANAGER->getElapsedTime();
	//
	//transform->Move(_speedX, _speedY);
}

