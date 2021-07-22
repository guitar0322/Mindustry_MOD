#include "stdafx.h"
#include "ProjectileManager.h"
#include "ProjectileObject.h"
#include "EnemyManager.h"
#include "Projectile.h"
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

		ProjectileObject* enemyPlaneProjectile = new ProjectileObject();
		enemyPlaneProjectile->GetRendererComponent()->Init("projectile");
		enemyPlaneProjectile->name = L"plane_projecilte";
		enemyPlaneProjectile->GetProjectileComponent()->SetSpeed(1000.f);
		enemyPlaneProjectile->GetProjectileComponent()->SetDamage(5);
		enemyPlaneProjectile->GetProjectileComponent()->SetTargetTag("player");
		enemyPlaneProjectile->GetColliderComponent()->SetSize(16, 16);
		enemyPlaneProjectile->SetActive(false);
		_enemyPlaneProjectileV.push_back(enemyPlaneProjectile);
	}
	for (int i = 0; i < ENEMY_PROJECTILE_MAX; i++)
	{
		ProjectileObject* enemyGroundProjectile = new ProjectileObject();
		enemyGroundProjectile->name = L"ground_projecilte";
		enemyGroundProjectile->GetRendererComponent()->Init("projectile");
		enemyGroundProjectile->GetProjectileComponent()->SetSpeed(1000.f);
		enemyGroundProjectile->GetProjectileComponent()->SetDamage(20);
		enemyGroundProjectile->GetProjectileComponent()->SetTargetTag("player");
		enemyGroundProjectile->GetColliderComponent()->SetSize(16, 16);
		enemyGroundProjectile->SetActive(false);
		_enemyGroundProjectileV.push_back(enemyGroundProjectile);
	}

	for (int i = 0; i < PLAYER_PROJECTILE_MAX; i++)
	{
		ProjectileObject* playerProjectile = new ProjectileObject();
		playerProjectile->GetRendererComponent()->Init("bullet");
		playerProjectile->name = L"player_projecilte";
		playerProjectile->transform->SetScale(0.7f, 0.7f);
		playerProjectile->GetProjectileComponent()->SetSpeed(800.f);
		playerProjectile->GetProjectileComponent()->SetDamage(100);
		playerProjectile->GetProjectileComponent()->SetTargetTag("enemy");
		playerProjectile->GetColliderComponent()->SetSize(16, 16);
		playerProjectile->SetActive(false);
		_playerProjectileV.push_back(playerProjectile);
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
		if (_enemyPlaneProjectileV[i]->isActive == false)
			continue;
		_enemyPlaneProjectileV[i]->Render();
	}
	for (int i = 0; i < ENEMY_PROJECTILE_MAX; i++)
	{
		if (_enemyGroundProjectileV[i]->isActive == false) 
			continue;
		_enemyGroundProjectileV[i]->Render();
	}
	for (int i = 0; i < PLAYER_PROJECTILE_MAX; i++)
	{
		if (_playerProjectileV[i]->isActive == false)
			continue;
		_playerProjectileV[i]->Render();
	}
}

void ProjectileManager::ProjectileMove()
{
	for (int i = 0; i < ENEMY_PROJECTILE_MAX; i++)
	{
		if (_enemyPlaneProjectileV[i]->isActive == false) 
			continue;
		_enemyPlaneProjectileV[i]->Update();
	}

	for (int i = 0; i < ENEMY_PROJECTILE_MAX; i++)
	{
		if (_enemyGroundProjectileV[i]->isActive == false)
			continue;
		_enemyGroundProjectileV[i]->Update();
	}
	
	for (int i = 0; i < PLAYER_PROJECTILE_MAX; i++)
	{
		if (_playerProjectileV[i]->isActive == false) 
			continue;
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
			_enemyPlaneProjectileV[i]->GetColliderComponent()->RefreshPartition();
			_enemyPlaneProjectileV[i]->transform->SetAngle(angle);
			_enemyPlaneProjectileV[i]->GetProjectileComponent()->SetFirePoint(Vector2(x, y));
			_enemyPlaneProjectileV[i]->GetProjectileComponent()->SetAngle(ConvertAngleAPI(angle));
			break;
		}
		break;

	case ENEMYGROUND:
		SOUNDMANAGER->play("shooting", 20.0f);
		for (int i = 0; i < ENEMY_PROJECTILE_MAX; i++)
		{
			if (_enemyGroundProjectileV[i]->isActive == true) 
				continue;
			_enemyGroundProjectileV[i]->SetActive(true);
			_enemyGroundProjectileV[i]->transform->SetPosition(x, y);
			_enemyGroundProjectileV[i]->GetColliderComponent()->RefreshPartition();
			_enemyGroundProjectileV[i]->transform->SetAngle(angle);
			_enemyGroundProjectileV[i]->GetProjectileComponent()->SetFirePoint(Vector2(x, y));
			_enemyGroundProjectileV[i]->GetProjectileComponent()->SetAngle(ConvertAngleAPI(angle));
			break;
		}
		break;

	case PLAYER:
		SOUNDMANAGER->play("shooting", 20.0f);
		for (int i = 0; i < PLAYER_PROJECTILE_MAX; i++)
		{
			if (_playerProjectileV[i]->isActive == true)
				continue;
			_playerProjectileV[i]->SetActive(true);
			_playerProjectileV[i]->transform->SetPosition(x, y);
			_playerProjectileV[i]->GetColliderComponent()->RefreshPartition();
			_playerProjectileV[i]->transform->SetAngle(angle);
			_playerProjectileV[i]->GetProjectileComponent()->SetFirePoint(Vector2(x, y));
			_playerProjectileV[i]->GetProjectileComponent()->SetAngle(ConvertAngleAPI(angle));
			break;
		}
		break;
	}
}

