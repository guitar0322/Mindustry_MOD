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
	//Scene���� PlaneControler�� Add�����
	//�׸��� PlaneControler Init�� �ߴ�
	//PlaneControler�� Init�� ��� �� �θ���
	//EnemyControler�� Init�� �����
	//�׷��� EnemyInfo�� GetComponent���� �ٷ� �����ü� ����	

	/*_enemyInfo = gameObject->GetComponent<EnemyInfo>();
	_speed = _enemyInfo->GetSpeed();
	_angle = _enemyInfo->GetAngle();

	_speedX = 0.f;
	_speedY = 0.f;*/
	//_angle = _enemyInfo->GetCoreAngle();
	_speedX = 0.f;
	_speedY = 0.f;
}

void EnemyControler::Update()
{
	//_projectileManager = gameObject->GetComponent<ProjectileManager>();
	//_speedX = cosf(_angle) * _speed * TIMEMANAGER->getElapsedTime();
	//_speedY = -sinf(_angle) * _speed * TIMEMANAGER->getElapsedTime();
	//
	//transform->Move(_speedX, _speedY);
}

