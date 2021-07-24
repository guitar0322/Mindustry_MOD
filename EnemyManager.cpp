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
#include "Astar.h"

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
	SOUNDMANAGER->addSound("explosion", "sounds/bang.ogg", true, false);
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
	_enemySpawnTime = 124.f;
	_timeSecond = 0;
	_timeMinute = 0;
	_spawnEnemy = false;
	_enemyTime = true;
	_waveSkip = false;
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
		_enemyGround->GetComponent<EnemyInfo>()->SetSpeed(150.f);
		_enemyGround->GetComponent<EnemyInfo>()->SetHp(100);
		_enemyGround->transform->SetScale(1.5f, 1.5f);
		_enemyGround->GetComponent<EnemyGroundControler>()->SetProjectileManager(_projectileManager);
		_enemyGround->GetComponent<EnemyGroundControler>()->SetAstar(_aStar);
		_enemyGround->GetComponent<BoxCollider>()->SetSize(48, 48);
		_enemyGround->GetComponent<BoxCollider>()->SetIsTrigger(false);
		_enemyGround->SetActive(false);
		_enemyV.push_back(_enemyGround);
	}

	for (int i = 8; i < 30; i++)
	{
		_enemyPlane = new EnemyPlane();
		_enemyPlane->tag = TAGMANAGER->GetTag("enemy");
		_enemyPlane->GetComponent<Renderer>()->Init("enemy_scepter");
		_enemyPlane->GetComponent<EnemyInfo>()->SetEnemyManager(this);
		_enemyPlane->GetComponent<EnemyInfo>()->SetTestCore(_testCore);
		_enemyPlane->GetComponent<EnemyInfo>()->GetCoreAngle();
		_enemyPlane->GetComponent<EnemyInfo>()->SetSpeed(450);								//450
		_enemyPlane->GetComponent<EnemyInfo>()->SetHp(100);
		_enemyPlane->transform->SetScale(0.5f, 0.5f);
		_enemyPlane->GetComponent<EnemyPlaneControler>()->SetProjectileManager(_projectileManager);
		_enemyPlane->GetComponent<EnemyPlaneControler>()->SetPlayerTransform(_playerTr);
		_enemyPlane->SetActive(false);
		_enemyV.push_back(_enemyPlane);
	}

	for (int i = 0; i < 1; i++)
	{
		_waveV[0].push_back(i);
	}

	for (int i = 8; i < 10; i++)
	{
		_waveV[0].push_back(i);
	}	

	for (int i = 0; i < 2; i++)				
	{
		_waveV[1].push_back(i);
	}	

	for (int i = 10; i < 13; i++)			
	{
		_waveV[1].push_back(i);
	}

	for (int i = 0; i < 4; i++)
	{
		_waveV[2].push_back(i);
	}
	for (int i = 13; i < 16; i++)
	{
		_waveV[2].push_back(i);
	}

	for (int i = 0; i < 5; i++)
	{
		_waveV[3].push_back(i);
	}
	for (int i = 16; i < 22; i++)
	{
		_waveV[3].push_back(i);
	}
}

void EnemyManager::EnemyTimer()
{
	if (_enemyTime)
	{
		_enemySpawnTime -= TIMEMANAGER->getElapsedTime();
		int _intEnemySpawnTime = int(_enemySpawnTime);

		_timeSecond = _intEnemySpawnTime % 60;		//60
		_timeMinute = _intEnemySpawnTime / 60;		//60

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
			_enemySpawnTime = 124.f;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		SpawnEnemy();
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
		_enemyV[_waveV[_curWave][i]]->transform->SetPosition(10 * 32 , 2 * 32);
	}
	_enemySpawnTime = 0.f;
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

vector<EnemyObject*> EnemyManager::GetCurWaveEnemy()
{
	vector<EnemyObject*> result;
	for (int i = 0; i < _waveV[_curWave].size(); i++)
	{
		result.push_back(_enemyV[_waveV[_curWave][i]]);
	}
	return result;
}

EnemyObject* EnemyManager::GetEnemy(int idx)
{
	return _enemyV[idx];
}
