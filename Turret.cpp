#include "stdafx.h"
#include "Turret.h"
#include "ProjectileObject.h"
Turret::Turret()
	: _projectileSpeed(100.f)
{
}

Turret::~Turret()
{
}

void Turret::Init(float attackSpeed, float attackRange, float damage, float projectileSpeed, float barrelLength)
{
	_attackSpeed = attackSpeed;
	_attackRange = attackRange;
	_damage = damage;
	_projectileSpeed = projectileSpeed;
	_barrelLength = barrelLength;

	for (int i = 0; i < PROJECTILE_MIN; i++)
	{
		_projectileV.push_back(new ProjectileObject());
		_projectileV[i]->GetProjectileComponent()->SetSpeed(_projectileSpeed);
	}
}

void Turret::Update()
{
	ProbeEnemy();
}

void Turret::Render()
{
}

void Turret::SetProjectileSpeed(float speed)
{
	for (int i = 0; i < _projectileV.size(); i++)
	{
		_projectileV[i]->GetProjectileComponent()->SetSpeed(speed);
	}
}

void Turret::Fire()
{
	if (PROJECTILE_MIN == GetActiveProjectileNum())
	{
		ProjectileObject* newProjectile = new ProjectileObject();
		newProjectile->GetProjectileComponent()->SetSpeed(_projectileSpeed);
		newProjectile->transform->SetPosition(
			Vector2
			(
				this->transform->GetX() + cosf(ConvertAngleAPI(transform->GetAngle())) * _barrelLength,
				this->transform->GetY() - sinf(ConvertAngleAPI(transform->GetAngle())) * _barrelLength
			)
		);
		newProjectile->SetActive(true);
		_projectileV.push_back(newProjectile);
	}
	else
	{
		for (int i = 0; i < _projectileV.size(); i++)
		{
			if (_projectileV[i]->isActive == true) continue;
			_projectileV[i]->transform->SetPosition(
				Vector2
				(
					this->transform->GetX() + cosf(ConvertAngleAPI(transform->GetAngle())) * _barrelLength,
					this->transform->GetY() - sinf(ConvertAngleAPI(transform->GetAngle())) * _barrelLength
				)
			);
			_projectileV[i]->SetActive(true);
			break;
		}
	}
}

void Turret::ProbeEnemy()
{
	if(false)
		Fire();
}

int Turret::GetActiveProjectileNum()
{
	int result = 0;
	for (int i = 0; i < _projectileV.size(); i++)
	{
		if (_projectileV[i]->isActive == true)
			result++;
	}
	return result;
}
