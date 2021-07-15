#include "stdafx.h"
#include "ProjectileManager.h"
#include "ProjectileObject.h"
#include "EnemyManager.h"
ProjectileManager::ProjectileManager()
{
}

ProjectileManager::~ProjectileManager()
{
}

void ProjectileManager::Init()
{
	for (int i = 0; i < ENEMY_PROJECTILE_MAX;  i++)
	{
		_enemyProjectile = new ProjectileObject();
		_enemyProjectile->tag = TAGMANAGER->GetTag("enemy");
		_enemyProjectile->GetRendererComponent()->Init("enemy_projectile");
		_enemyProjectile->GetProjectileComponent()->SetSpeed(1000.f);
		_enemyProjectile->SetActive(false);
		_enemyProjectileV.push_back(_enemyProjectile);
	}
	for (int i = 0; i < PLAYER_PROJECTILE_MAX; i++)
	{
		_playerProjectile = new ProjectileObject();
		_playerProjectile->GetRendererComponent()->Init("enemy_projectile");
		_playerProjectile->GetProjectileComponent()->SetSpeed(150.f);
		_playerProjectile->SetActive(false);
		_playerProjectileV.push_back(_playerProjectile);
	}
	//_deltaAngle = _enemyPlaneControlerTransform->angle;
}

void ProjectileManager::Update()
{
	ProjectileMove();
}

void ProjectileManager::Render()
{
	for (int i = 0; i < ENEMY_PROJECTILE_MAX; i++)
	{
		if (_enemyProjectileV[i]->isActive == false) continue;
		_enemyProjectileV[i]->Render();
	}
	for (int i = 0; i < PLAYER_PROJECTILE_MAX; i++)
	{
		if (_playerProjectileV[i]->isActive == false) continue;
		_playerProjectileV[i]->Render();
	}
}

void ProjectileManager::ProjectileMove()
{
	for (int i = 0; i < ENEMY_PROJECTILE_MAX; i++)
	{
		if (_enemyProjectileV[i]->isActive == false) continue;
		_enemyProjectileV[i]->Update();
	}
	for (int i = 0; i < PLAYER_PROJECTILE_MAX; i++)
	{
		if (_playerProjectileV[i]->isActive == false) continue;
		_playerProjectileV[i]->Update();
	}
}

void ProjectileManager::FireProjectile(float x, float y, float angle, PROJECTILE_TYPE type)
{
	switch(type) 
	{
	case ENEMY:
		for (int i = 0; i < ENEMY_PROJECTILE_MAX; i++)
		{
			if (_enemyProjectileV[i]->isActive == true) continue;
			_enemyProjectileV[i]->SetActive(true);
			_enemyProjectileV[i]->transform->SetPosition(x, y);
			_enemyProjectileV[i]->transform->SetAngle(ConvertAngleD2D(angle));
			break;
		}
		break;
	case PLAYER:
		for (int i = 0; i < PLAYER_PROJECTILE_MAX; i++)
		{
			if (_playerProjectileV[i]->isActive == true) continue;
			_playerProjectileV[i]->SetActive(true);
			_playerProjectileV[i]->transform->SetPosition(x, y);
			_playerProjectileV[i]->transform->SetAngle(ConvertAngleD2D(angle));
			break;
		}
		break;
	}
}

