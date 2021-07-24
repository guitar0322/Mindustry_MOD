#include "stdafx.h"
#include "Turret.h"
#include "ProjectileObject.h"
#include "Projectile.h"
#include "EnemyManager.h"
#include "EnemyObject.h"
#include "ProjectileManager.h"
#include "Item.h";
Turret::Turret()
	:_preWave(-1), _bulletNum(0), _isMax(false)
{
}

Turret::~Turret()
{
}

void Turret::Init(float attackSpeed, float attackRange, float barrelLength)
{
	_attackSpeed = attackSpeed;
	_attackRange = attackRange;
	_barrelLength = barrelLength;
}

void Turret::Update()
{
	if (_preWave != _enemyManager->GetCurWave())
	
	{	_preWave = _enemyManager->GetCurWave();
		_curWaveEnemyV = _enemyManager->GetCurWaveEnemy();
		_minDistance = INT_MAX;
		_nearEnemyIdx = -1;
	}

	ProbeEnemy();
}

void Turret::Render()
{

}

void Turret::OnTriggerEnter(GameObject* gameObject)
{
	if (gameObject->tag != TAGMANAGER->GetTag("resource"))
		return;
	if (_isMax == true)
		return;
	gameObject->SetActive(false);
	_bulletNum++;
	if (_bulletNum >= BULLET_MAX)
		_isMax = true;
}

void Turret::AddBullet()
{
	_bulletNum++;
	if (_bulletNum >= BULLET_MAX)
		_isMax = true;
}

void Turret::Fire()
{
	if (_curWaveEnemyV[_nearEnemyIdx]->isActive == false || _bulletNum == 0)
	{
		return;
	}
	_attackSpeed += TIMEMANAGER->getElapsedTime();
	if (_attackSpeed >= 0.5f)
	{
		float angle = GetAngle(transform->position, _curWaveEnemyV[_nearEnemyIdx]->transform->position);
		transform->SetAngle(ConvertAngleD2D(angle));
		_projectileManager->FireProjectile(transform->GetX() + cosf(angle) * _barrelLength, transform->GetY() - sinf(angle) * _barrelLength, ConvertAngleD2D(angle), PLAYER);
		EFFECTMANAGER->EmissionEffect("shoot", transform->GetX() + cosf(angle) * _barrelLength, transform->GetY() - sinf(angle) * _barrelLength, ConvertAngleD2D(angle));
		_attackSpeed = 0;
		_bulletNum--;
		_isMax = false;
	}
}
void Turret::ProbeEnemy()
{
	_nearEnemyIdx = -1;
	_minDistance = INT_MAX;

	for (int i = 0; i < _curWaveEnemyV.size(); i++)
	{
		if (_curWaveEnemyV[i]->isActive == false) continue;
		_distance = GetDistance(_curWaveEnemyV[i]->transform->position, transform->position);
		if (_distance > _attackRange)
			continue;
		if (_distance < _minDistance) {
			_minDistance = _distance;
			_nearEnemyIdx = i;
		}
	}

	if(_nearEnemyIdx != -1)
		Fire();
}