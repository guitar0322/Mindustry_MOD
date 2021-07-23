#pragma once
#include "Component.h"
#include "EnemyInfo.h"

#define ENEMY_MAX 30
#define WAVE_NUM 10

class EnemyPlane;
class EnemyGround;
class ProjectileManager;
class EnemyInfo;
class EnemyObject;

class EnemyManager :
	public Component
{
private:
	vector<EnemyObject*> _enemyV;
	vector<int> _waveV[WAVE_NUM];

	EnemyPlane* _enemyPlane;
	EnemyGround* _enemyGround;

	EnemyInfo* _enemyInfo;

	ProjectileManager* _projectileManager;

	GameObject* _testCore;
	Transform* _testCoreTransform;
	
	int _curWave;					//현재 웨이브
	int _timeSecond;				//시간 초
	int _timeMinute;				//시간 분

	float _enemySpawnTime;			//에너미 스폰 시간재주기
	
	bool _spawnEnemy;				//에너미가 생성 되는가?
	bool _enemyTime;				//enemy 스폰시간이 진행중인가?

public:
	EnemyManager();
	~EnemyManager();

	virtual void Init();
	virtual void Update();
	virtual void Render();

	void SetEnemyTime();
	void SetEnemy();
	void EnemyTimer();
	void EnemyUpdate();
	void EnemyRender();
	void SpawnEnemy();
	void DeadEvent();

	float GetTimeSecond() const { return _timeSecond; }
	float GetTimeMinute() const { return _timeMinute; }
	float GetCurWave() const { return _curWave; }

	void SetProjectileManager(ProjectileManager* projectileManager){ _projectileManager = projectileManager; }
	void SetTestCoreTransform(GameObject* testCore) { _testCore = testCore; _testCoreTransform = testCore->transform; }
	void SetEnemyInfo(EnemyInfo* enemyInfo) { _enemyInfo = enemyInfo; }
	vector<EnemyObject*> GetCurWaveEnemy();
};

