#include "stdafx.h"
#include "EnemyGroundControler.h"

EnemyGroundControler::EnemyGroundControler()
{
}

EnemyGroundControler::~EnemyGroundControler()
{
}

void EnemyGroundControler::Init()
{
	_speed = gameObject->GetComponent<EnemyInfo>()->GetSpeed();
	//_angle = GetAngle(transform->position, _testCoreTransform->position);
	_angle = 0.f;
	_speedX = 0.f;
	_speedY = 0.f;

}

void EnemyGroundControler::Update()
{
	_angle = GetAngle(transform->position, _testCoreTransform->position);

	_speedX = cosf(_angle) * _speed * TIMEMANAGER->getElapsedTime();
	_speedY = -sinf(_angle) * _speed * TIMEMANAGER->getElapsedTime();

	transform->Move(_speedX, _speedY);
	transform->SetAngle(ConvertAngleD2D(_angle));
}
