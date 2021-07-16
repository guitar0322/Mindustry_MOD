#include "stdafx.h"
#include "Projectile.h"
//#include "ProjectileManager.h"

Projectile::Projectile()
{
}

Projectile::~Projectile()
{
}

void Projectile::Init()
{
	_speed = 0.f;
	_angle = 0.f;
	_speedX, _speedY = 0.f;
	transform->SetScale(1.5f, 1.5f);
}

void Projectile::Update()
{
	Move();
}

void Projectile::Move()
{
	_speedX = cosf(ConvertAngleAPI(transform->GetAngle())) * _speed * TIMEMANAGER->getElapsedTime();
	_speedY = -sinf(ConvertAngleAPI(transform->GetAngle())) * _speed * TIMEMANAGER->getElapsedTime();

	transform->Move(_speedX, _speedY);
}

void Projectile::OnTriggerEnter(GameObject* gameObject)
{
	if (TAGMANAGER->GetTag("player") == gameObject->tag)
	if (gameObject->tag == TAGMANAGER->GetTag("player"))
	{
		transform->gameObject->SetActive(false);
	}
}