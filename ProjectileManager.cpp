#include "stdafx.h"
#include "ProjectileManager.h"
#include "ProjectileObject.h"
#include "EnemyManager.h"
#include "Player.h"


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
		_enemyPlaneProjectile = new ProjectileObject();
		_enemyPlaneProjectile->tag = TAGMANAGER->GetTag("enemy");
		_enemyPlaneProjectile->GetRendererComponent()->Init("projectile");
		_enemyPlaneProjectile->GetProjectileComponent()->SetSpeed(1000.f);
		_enemyPlaneProjectile->GetProjectileComponent()->SetDamage(50);
		_enemyPlaneProjectile->SetActive(false);
		_enemyPlaneProjectileV.push_back(_enemyPlaneProjectile);
	}
	for (int i = 0; i < ENEMY_PROJECTILE_MAX; i++)
	{
		_enemyGroundProjectile = new ProjectileObject();
		_enemyGroundProjectile->tag = TAGMANAGER->GetTag("enemy");
		_enemyGroundProjectile->GetRendererComponent()->Init("projectile");
		_enemyGroundProjectile->GetProjectileComponent()->SetSpeed(1000.f);
		_enemyGroundProjectile->GetProjectileComponent()->SetDamage(50);
		_enemyGroundProjectile->SetActive(false);
		_enemyGroundProjectileV.push_back(_enemyGroundProjectile);
	}

	for (int i = 0; i < PLAYER_PROJECTILE_MAX; i++)
	{
		_playerProjectile = new ProjectileObject();
		_playerProjectile->GetRendererComponent()->Init("projectile");
		_playerProjectile->transform->SetScale(0.5f, 0.5f);
		_playerProjectile->GetProjectileComponent()->SetSpeed(150.f);
		_playerProjectile->SetActive(false);
		_playerProjectileV.push_back(_playerProjectile);
	}
	SOUNDMANAGER->addSound("shooting", "sounds/shoot.ogg", true, false);
}

void ProjectileManager::Update()
{
	ProjectileMove();
}

void ProjectileManager::Render()
{
	for (int i = 0; i < ENEMY_PROJECTILE_MAX; i++)
	{
		if (_enemyPlaneProjectileV[i]->isActive == false) continue;
		_enemyPlaneProjectileV[i]->Render();

		if (_enemyGroundProjectileV[i]->isActive == false) continue;
		_enemyGroundProjectileV[i]->Render();
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
		if (_enemyPlaneProjectileV[i]->isActive == false) continue;
		_enemyPlaneProjectileV[i]->Update();
		
		if (_enemyGroundProjectileV[i]->isActive == false) continue;
		_enemyGroundProjectileV[i]->Update();
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
	case ENEMYPLANE:
		SOUNDMANAGER->play("shooting", 20.0f);
		for (int i = 0; i < ENEMY_PROJECTILE_MAX; i++)
		{
			if (_enemyPlaneProjectileV[i]->isActive == true) continue;
			_enemyPlaneProjectileV[i]->SetActive(true);
			_enemyPlaneProjectileV[i]->transform->SetPosition(x, y);
			_enemyPlaneProjectileV[i]->transform->SetAngle(angle);
			break;
		}
		break;
	case ENEMYGROUND:
		SOUNDMANAGER->play("shooting", 20.0f);
		for (int i = 0; i < ENEMY_PROJECTILE_MAX; i++)
		{
			if (_enemyGroundProjectileV[i]->isActive == true) continue;
			_enemyGroundProjectileV[i]->SetActive(true);
			_enemyGroundProjectileV[i]->transform->SetPosition(x, y);
			_enemyGroundProjectileV[i]->transform->SetAngle(angle);
			break;
		}
		break;
	case PLAYER:
		SOUNDMANAGER->play("shooting", 20.0f);
		for (int i = 0; i < PLAYER_PROJECTILE_MAX; i++)
		{
			if (_playerProjectileV[i]->isActive == true) continue;
			_playerProjectileV[i]->SetActive(true);
			_playerProjectileV[i]->transform->SetPosition(x, y);
			_playerProjectileV[i]->transform->SetAngle(angle);
			break;
		}
		break;
	}
}

