#include "stdafx.h"
#include "Turret.h"
#include "ProjectileObject.h"
#include "Projectile.h"
#include "ProjectileManager.h"
#include "Duo.h"
#include "EnemyManager.h"
#include "EnemyObject.h"
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
	_isFire = false;
	_attackAngle = 0.f;

	for (int i = 0; i < PROJECTILE_MIN; i++)
	{
		_projectileV.push_back(new ProjectileObject());
		_projectileV[i]->GetProjectileComponent()->SetSpeed(_projectileSpeed);
		
	}
	_preWave = -1;
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
	/********************************************
	PropFactory에서 해야할거
	1.PropFactory에 EnemyManger포인터 연결시키기
	2.CrateTurret에서 Turret새로 만들고 터렛한테 SetEnemyManager로 연결시켜주기
	3.ProjectileManager도 1,2번과 마찬가지로 해주고

	TODO
	0.projectileManger 포인터 연결시키기
	1.curWaveEnemy중에서 가장 가까운놈 구한다.
	2.가장 가까운놈과 GetAngle로 각도를 구한다
	3.구한 각도로 쏠 위치 x,y 계산해서 구하고, ProjectileManger에서 FireProjectile함수 호출한다.
	*******************************************/
	
	ProjectileManager* newProjectilemanager = new ProjectileManager();

	_attackSpeed += TIMEMANAGER->getElapsedTime();


	//if (PROJECTILE_MIN == GetActiveProjectileNum())
	//{

	//	ProjectileObject* newProjectile = new ProjectileObject();
	//	newProjectile->GetProjectileComponent()->SetSpeed(_projectileSpeed);
	//	newProjectile->transform->SetPosition(
	//		Vector2
	//		(
	//			this->transform->GetX() + cosf(ConvertAngleAPI(transform->GetAngle())) * _barrelLength,
	//			this->transform->GetY() - sinf(ConvertAngleAPI(transform->GetAngle())) * _barrelLength
	//		)
	//	);
	//	newProjectile->SetActive(true);
	//	_projectileV.push_back(newProjectile);
	//}
	//else
	//{
	//	for (int i = 0; i < _projectileV.size(); i++)
	//	{
	//		if (_projectileV[i]->isActive == true) continue;
	//		_projectileV[i]->transform->SetPosition(
	//			Vector2
	//			(
	//				this->transform->GetX() + cosf(ConvertAngleAPI(transform->GetAngle())) * _barrelLength,
	//				this->transform->GetY() - sinf(ConvertAngleAPI(transform->GetAngle())) * _barrelLength
	//			)
	//		);
	//		_projectileV[i]->SetActive(true);
	//		break;
	//	}
	//}
}

void Turret::ProbeEnemy()
{
	if (_preWave != _enemyManager->GetCurWave())
	{
		_curWaveEnemy = _enemyManager->GetCurWaveEnemy();
		_preWave = _enemyManager->GetCurWave();
	}
	for (int i = 0; i < _curWaveEnemy.size(); i++)
	{
		if (GetDistance(transform->position, _curWaveEnemy[i]->transform->position) <= 400)
		{
			Fire();
			_isFire = true;
		}
	}

	if (_isFire == true)
	{
		_fireCount += TIMEMANAGER->getElapsedTime();
		if (_fireCount >= 0.5f)
		{
			_fireCount = 0;
			_isFire = false;
		}
	}
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
