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
	//gameObject->GetComponent<BoxCollider>();
	transform->SetScale(3, 3);
	//_projectileManager = gameObject->GetComponent<ProjectileManager>();
}

void Projectile::Update()
{
	Move();
}

void Projectile::Move()
{
	_speedX = cosf(transform->GetAngle()) * _speed * TIMEMANAGER->getElapsedTime();
	_speedY = -sinf(transform->GetAngle()) * _speed * TIMEMANAGER->getElapsedTime();

	transform->Move(_speedX, _speedY);
}

void Projectile::OnTriggerEnter(GameObject * gameObject)
{
	if (gameObject->tag == TAGMANAGER->GetTag("player"))
	{
		transform->gameObject->SetActive(false);
	}
}