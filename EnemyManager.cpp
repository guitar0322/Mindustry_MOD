#include "stdafx.h"
#include "EnemyManager.h"
#include "EnemyObject.h"
#include "EnemyPlane.h"
#include "EnemyGround.h"
#include "ProjectileManager.h"
#include "EnemyPlaneControler.h"
#include "EnemyGroundControler.h"

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Init()
{
	SetEnemyTime();
	_curWave = 0;
	for (int i = 0; i < 5; i++)
	{
		_enemyPlane = new EnemyPlane();
		_enemyPlane->GetComponent<Renderer>()->Init("enemy_atrax");
		//_enemyPlane->GetComponent<EnemyInfo>()->SetSpeed(400.f);
		_enemyPlane->GetComponent<EnemyInfo>()->SetTestCore(_testCore);
		_enemyPlane->GetComponent<EnemyInfo>()->GetCoreAngle();
		//_enemyPlane->GetComponent<EnemyPlaneControler>()->SetProjectileManagerTransform(_projectileManager);
		_enemyPlane->SetActive(false);
		_enemyV.push_back(_enemyPlane);
	}

	for (int i = 5; i < 10; i++)
	{
		_enemyGround = new EnemyGround();
		_enemyGround->GetComponent<Renderer>()->Init("enemy_dagger_walk");
	//	_enemyGround->GetComponent<EnemyInfo>()->SetSpeed(200.f);
		_enemyGround->GetComponent<EnemyInfo>()->SetTestCore(_testCore);
		_enemyGround->GetComponent<EnemyInfo>()->GetCoreAngle();
	//	_enemyGround->GetComponent<EnemyGroundControler>()->SetProjectileManagerTransform(_projectileManager);
		_enemyGround->SetActive(false);
		_enemyV.push_back(_enemyGround);
	}

	for (int i = 0; i < 2; i++)
	{
		_waveV[0].push_back(i);
	}

	for (int i = 5; i < 7; i++)
	{
		_waveV[0].push_back(i);
	}
}

void EnemyManager::Update()
{
	EnemyTimer();
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (_enemyV[i]->isActive == false) continue;
		_enemyV[i]->Update();
	}
}

void EnemyManager::Render()
{
	for(int i = 0; i < ENEMY_MAX; i++)
	{
		if (_enemyV[i]->isActive == false) continue;
		_enemyV[i]->Render();
	}
}
void EnemyManager::SetEnemyTime()
{
	_enemySpawnTime = 3.f;
	_timeSecond = 0;
	_timeMinute = 0;
	_spawnEnemy = false;
	_enemyTime = true;
}

void EnemyManager::EnemyTimer()
{
	if (_enemyTime)
	{
		_enemySpawnTime -= TIMEMANAGER->getElapsedTime();
		int _intEnemySpawnTime = int(_enemySpawnTime);

		_timeSecond = _intEnemySpawnTime % 3;		//60
		_timeMinute = _intEnemySpawnTime / 3;		//60
		if (_intEnemySpawnTime == 0)
		{
			_spawnEnemy = true;
			_enemyTime = false;
		}
	}
	if (_spawnEnemy == true && _enemyTime == false)
	{
		SpawnEnemy();
	}
}

void EnemyManager::SpawnEnemy()
{
	for (int i = 0; i < _waveV[_curWave].size(); i++)
	{
		_enemyV[_waveV[_curWave][i]]->SetActive(true);
		if (_enemyV[i]->isActive == true) continue;
		{
			_enemyV[i]->SetActive(true);
			_enemyV[i]->transform->SetPosition(100 + 500 * i, 100);
			break;
		}
	}
}
