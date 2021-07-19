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

	//_camX = MainCam->GetRenderWidth() - MainCam->transform->GetX();
	//_camY = MainCam->GetRenderHeight() - MainCam->transform->GetY();
	//_camX = MainCam->GetRenderWidth() - MainCam->GetCameraStartX();
	//_camY = MainCam->GetRenderHeight() - MainCam->GetCameraStartY();
	//_camX = MainCam->GetScreenHeight() - MainCam->GetRenderHeight();
	//MainCam->GetScreenStart 
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
	/*if (_camX * 2 > transform->GetX() || MainCam->transform->GetScaleX() - _camX * 2 < transform->GetX())
	{
		transform->gameObject->SetActive(false);
	}
	if (_camY * 2 > transform->GetY() || MainCam->transform->GetScaleY() - _camY * 2 < transform->GetY())
	{
		transform->gameObject->SetActive(false);
	}*/
	//if (MainCam->GetRenderWidth() - 700 < transform->GetX())
	//{
	//	transform->gameObject->SetActive(false);
	//}
	//MainCam->Get
	/*if (MainCam->GetCameraStartY()  + 500> transform->GetY())
	{
		transform->gameObject->SetActive(false);
	}*/
	/*if (MainCam-> + 200 < transform->GetX())
	{
		transform->gameObject->SetActive(false);
	}*/
}
