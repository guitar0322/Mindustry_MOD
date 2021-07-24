#include "stdafx.h"
#include "Projectile.h"
#include "EnemyInfo.h"
#include "PlayerControler.h"
#include "PropStat.h"

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
	if (GetDistance(_firePt, transform->position) >= 500)
	{
		EFFECTMANAGER->ActiveSmallParticle(transform->GetX(), transform->GetY());
		gameObject->SetActive(false);
	}
}

void Projectile::OnTriggerEnter(GameObject* gameObject)
{
	if (gameObject->tag == TAGMANAGER->GetTag(_targetTag))
	{
		if (_targetTag.compare("player") == 0)
		{
			this->gameObject->SetActive(false);
			EFFECTMANAGER->ActiveSmallParticle(transform->GetX(), transform->GetY());
			gameObject->GetComponent<PlayerControler>()->Hit(_damage);

		}
		if (_targetTag.compare("enemy") == 0)
		{
			this->gameObject->SetActive(false);
			EFFECTMANAGER->ActiveSmallParticle(transform->GetX(), transform->GetY());
			gameObject->GetComponent<EnemyInfo>()->Hit(_damage);

		}
		if (_targetTag.compare("prop") == 0)
		{
			this->gameObject->SetActive(false);
			EFFECTMANAGER->ActiveSmallParticle(transform->GetX(), transform->GetY());
			gameObject->GetComponent<PropStat>()->Hit(_damage);
		}
	}
}
