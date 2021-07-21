#include "stdafx.h"
#include "Projectile.h"
#include "EnemyInfo.h"
#include "PlayerControler.h"

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
	_camX = 0.f;
	_camY = 0.f;
	_fireX = transform->GetX();
	_fireY = transform->GetY();
}

void Projectile::Update()
{
	Move();
	EreaseProjectile();
}

void Projectile::Move()
{
	_speedX = cosf(ConvertAngleAPI(transform->GetAngle())) * _speed * TIMEMANAGER->getElapsedTime();
	_speedY = -sinf(ConvertAngleAPI(transform->GetAngle())) * _speed * TIMEMANAGER->getElapsedTime();

	transform->Move(_speedX, _speedY);

}

void Projectile::OnTriggerEnter(GameObject* gameObject)
{
	if (gameObject->tag == TAGMANAGER->GetTag(_targetTag))
	{
		if (_targetTag.compare("player") == 0)
		{
			transform->gameObject->SetActive(false);
			gameObject->GetComponent<PlayerControler>()->Hit(_damage);
		}
		if (_targetTag.compare("enemy") == 0)
		{
			transform->gameObject->SetActive(false);
			gameObject->GetComponent<EnemyInfo>()->Hit(_damage);
		}
	}
}

void Projectile::EreaseProjectile()
{
	if (Math::Abs(_fireX) - Math::Abs(transform->GetX()) >= 350)
		gameObject->SetActive(false);

	//if (Math::Abs(_fireX) + Math::Abs(transform->GetX()) <= 150)
	//	gameObject->SetActive(false);
	//if (MainCam->GetRenderWidth() + 150 <= transform->GetX())
	//{
	//	gameObject->SetActive(false);
	//}
	//if (MainCam->GetCameraStartX() - 150 >= transform->GetX())
	//{
	//	gameObject->SetActive(false);
	//}

	//if (MainCam->GetRenderHeight() + 150 <= transform->GetY())
	//{
	//	gameObject->SetActive(false);
	//}
	//if (MainCam->GetCameraStartY() - 150 >= transform->GetY())
	//{
	//	gameObject->SetActive(false);
	//}
}
