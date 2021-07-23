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
	PropFactory���� �ؾ��Ұ�
	1.PropFactory�� EnemyManger������ �����Ű��
	2.CrateTurret���� Turret���� ����� �ͷ����� SetEnemyManager�� ��������ֱ�
	3.ProjectileManager�� 1,2���� ���������� ���ְ�

	TODO
	0.projectileManger ������ �����Ű��
	1.curWaveEnemy�߿��� ���� ������ ���Ѵ�.
	2.���� ������� GetAngle�� ������ ���Ѵ�
	3.���� ������ �� ��ġ x,y ����ؼ� ���ϰ�, ProjectileManger���� FireProjectile�Լ� ȣ���Ѵ�.
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
