#include "stdafx.h"
#include "EnemyManager.h"
#include "EnemyObject.h"
#include "EnemyPlane.h"
#include "EnemyGround.h"
#include "ProjectileManager.h"
#include "EnemyPlaneControler.h" 
#include "EnemyGroundControler.h"
#include "EnemyInfo.h"
#include "EnemyObject.h"

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Init()
{
	SetEnemyTime();
	SetEnemy();
	_curWave = 0;
	SOUNDMANAGER->addSound("wave", "sounds/wave.ogg", true, false);
	SOUNDMANAGER->addSound("explosion", "sounds/explosion.ogg", true, false);
}

void EnemyManager::Update()
{
	EnemyTimer();
	EnemyUpdate();
}

void EnemyManager::Render()
{
	EnemyRender();
}

void EnemyManager::SetEnemyTime()
{
	_enemySpawnTime = 3.f;
	_timeSecond = 0;
	_timeMinute = 0;
	_spawnEnemy = false;
	_enemyTime = true;
}

void EnemyManager::SetEnemy()
{
	for (int i = 0; i < 8; i++)
	{
		_enemyGround = new EnemyGround();
		_enemyGround->tag = TAGMANAGER->GetTag("enemy");
		_enemyGround->GetComponent<Renderer>()->Init("enemy_dagger_walk");
		_enemyGround->GetComponent<Animator>()->AddClip("enemy_dagger_walk", CLIPMANAGER->FindClip("enemy_dagger_walk"));
		_enemyGround->GetComponent<Animator>()->SetClip("enemy_dagger_walk", 0);
		_enemyGround->GetComponent<EnemyInfo>()->SetEnemyManager(this);
		_enemyGround->GetComponent<EnemyInfo>()->SetTestCore(_testCore);
		_enemyGround->GetComponent<EnemyInfo>()->GetCoreAngle();
		_enemyGround->GetComponent<EnemyInfo>()->SetSpeed(200.f);
		_enemyGround->GetComponent<EnemyInfo>()->SetHp(100);
		_enemyGround->transform->SetScale(0.5f, 0.5f);
		_enemyGround->GetComponent<EnemyGroundControler>()->SetProjectileManager(_projectileManager);
		_enemyGround->SetActive(false);
		_enemyV.push_back(_enemyGround);
	}
	for (int i = 7; i < 30; i++)
	{
		_enemyPlane = new EnemyPlane();
		_enemyPlane->tag = TAGMANAGER->GetTag("enemy");
		_enemyPlane->GetComponent<Renderer>()->Init("enemy_atrax");
		_enemyPlane->GetComponent<EnemyInfo>()->SetEnemyManager(this);
		_enemyPlane->GetComponent<EnemyInfo>()->SetTestCore(_testCore);
		_enemyPlane->GetComponent<EnemyInfo>()->GetCoreAngle();
		_enemyPlane->GetComponent<EnemyInfo>()->SetSpeed(400.f);
		_enemyPlane->GetComponent<EnemyInfo>()->SetHp(100);
		_enemyPlane->transform->SetScale(0.5f, 0.5f);
		_enemyPlane->GetComponent<EnemyPlaneControler>()->SetProjectileManager(_projectileManager);
		_enemyPlane->SetActive(false);
		_enemyV.push_back(_enemyPlane);
	}


	for (int i = 0; i < 1; i++)
	{
		_waveV[0].push_back(i);
	}

	for (int i = 7; i < 9; i++)
	{
		_waveV[0].push_back(i);
	}	

	for (int i = 0; i < 3; i++)
	{
		_waveV[1].push_back(i);
	}

	for (int i = 7; i < 11; i++)
	{
		_waveV[1].push_back(i);
	}	

	for (int i = 0; i < 5; i++)
	{
		_waveV[2].push_back(i);
	}

	for (int i = 7; i < 14; i++)
	{
		_waveV[2].push_back(i);
	}	

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

		if (_spawnEnemy == true && _enemyTime == false)
		{
			SpawnEnemy();
			_spawnEnemy = false;
			_enemyTime = false;
			_enemySpawnTime = 3.f;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		SpawnEnemy();
	}
}

void EnemyManager::EnemyUpdate()
{
	for (int i = 0; i < _waveV[_curWave].size(); i++)
	{
		if (_enemyV[_waveV[_curWave][i]]->isActive == false) continue;
		_enemyV[_waveV[_curWave][i]]->Update();
	}
}

void EnemyManager::EnemyRender()
{
	for (int i = 0; i < _waveV[_curWave].size(); i++)
	{
		if (_enemyV[_waveV[_curWave][i]]->isActive == false) continue;
		_enemyV[_waveV[_curWave][i]]->Render();
	}
}

void EnemyManager::SpawnEnemy()
{
	SOUNDMANAGER->play("wave", 10.0f);
	for (int i = 0; i < _waveV[_curWave].size(); i++)
	{
		if (_enemyV[_waveV[_curWave][i]]->isActive == true) 
			continue;

		_enemyV[_waveV[_curWave][i]]->SetActive(true);
		_enemyV[_waveV[_curWave][i]]->transform->SetPosition(100 + 200 * i , 100 + 50 * i);
	}
}

void EnemyManager::DeadEvent()
{
	SOUNDMANAGER->play("explosion", 40.0f);

	for (int i = 0; i < _waveV[_curWave].size(); i++)
	{ 
		if (_enemyV[_waveV[_curWave][i]]->isActive == true) return;
	}
	_enemyTime = true;
	_curWave++;
	return;
}
																																																			