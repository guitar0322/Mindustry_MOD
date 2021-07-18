#include "stdafx.h"
#include "EnemyManager.h"
#include "EnemyObject.h"
#include "EnemyPlane.h"
#include "EnemyGround.h"
#include "ProjectileManager.h"
#include "EnemyPlaneControler.h"
#include "EnemyGroundControler.h"
#include "EnemyInfo.h"

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Init()
{
	//_enemyInfo = gameObject->GetComponent<EnemyInfo>();//->SetEnemyManager;
	//this->SetEnemyInfo(_enemyInfo);
	
	//_enemyInfo->SetEnemyManager(this);
	SetEnemyTime();
	SetEnemy();
	_curWave = 1;
	SOUNDMANAGER->addSound("wave", "sounds/wave.ogg", true, false);
	SOUNDMANAGER->addSound("explosion", "sounds/place.ogg", true, false);
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
	for (int i = 0; i < 5; i++)
	{
		_enemyPlane = new EnemyPlane();
		_enemyPlane->GetComponent<Renderer>()->Init("enemy_atrax");
		_enemyPlane->GetComponent<EnemyInfo>()->SetEnemyManager(this);
		_enemyPlane->GetComponent<EnemyInfo>()->SetTestCore(_testCore);
		_enemyPlane->GetComponent<EnemyInfo>()->GetCoreAngle();
		_enemyPlane->GetComponent<EnemyInfo>()->SetSpeed(400.f);
		_enemyPlane->GetComponent<EnemyInfo>()->SetHp(100);
		_enemyPlane->GetComponent<EnemyPlaneControler>()->SetProjectileManager(_projectileManager);
		_enemyPlane->SetActive(false);
		_enemyV.push_back(_enemyPlane);
	}

	for (int i = 5; i < 10; i++)
	{
		_enemyGround = new EnemyGround();
		_enemyGround->GetComponent<Renderer>()->Init("enemy_dagger_walk");
		_enemyGround->GetComponent<Animator>()->Init();
		_enemyGround->GetComponent<Animator>()->SetClip("enemy_dagger_walk", 1);
		_enemyGround->GetComponent<EnemyInfo>()->SetEnemyManager(this);
		_enemyGround->GetComponent<EnemyInfo>()->SetTestCore(_testCore);
		_enemyGround->GetComponent<EnemyInfo>()->GetCoreAngle();
		_enemyGround->GetComponent<EnemyInfo>()->SetSpeed(200.f);
		_enemyGround->GetComponent<EnemyInfo>()->SetHp(100);
		_enemyGround->GetComponent<EnemyGroundControler>()->SetProjectileManager(_projectileManager);
		_enemyGround->SetActive(false);
		_enemyV.push_back(_enemyGround);
	}

	for (int i = 0; i < 2; i++)
	{
		_waveV[0].push_back(i);
	}

	for (int i = 6; i < 8; i++)
	{
		_waveV[0].push_back(i);
	}
	
	for (int i = 0; i < 5; i++)
	{
		_waveV[1].push_back(i);
	}
	for (int i = 5; i < 8; i++)
	{
		_waveV[1].push_back(i);
	}
}

void EnemyManager::EnemyTimer()
{
	//if (_enemyTime)
	//{
	//	_enemySpawnTime -= TIMEMANAGER->getElapsedTime();
	//	int _intEnemySpawnTime = int(_enemySpawnTime);

	//	_timeSecond = _intEnemySpawnTime % 3;		//60
	//	_timeMinute = _intEnemySpawnTime / 3;		//60

	//	if (_intEnemySpawnTime == 0)
	//	{
	//		_spawnEnemy = true;
	//		_enemyTime = false;
	//	}
	//}
	//if (_spawnEnemy == true && _enemyTime == false)
	//{
	//	SpawnEnemy();
	//}
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
		if (_enemyV[i]->isActive == true) continue;
		{
			_enemyV[_waveV[_curWave][i]]->SetActive(true);
			_enemyV[_waveV[_curWave][i]]->transform->SetPosition(100 + 500 * i, 100 + 50 * i);
			break;
		}
	}
}

void EnemyManager::DeadEvent()
{
	SOUNDMANAGER->play("explosion", 40.0f);
	//if (_enemyInfo->isDeath)
	//{
		for (int i = 0; i < _waveV[_curWave].size(); i++)
		{ 
			if (_enemyV[_waveV[_curWave][i]]->isActive == false) continue;
			_enemyV[_waveV[_curWave][i]]->SetActive(false);
		}
	//}
	_curWave++;
	return;
}
																																																			