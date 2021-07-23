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
	
	int _curWave;					//���� ���̺�
	int _timeSecond;				//�ð� ��
	int _timeMinute;				//�ð� ��

	float _enemySpawnTime;			//���ʹ� ���� �ð����ֱ�
	
	bool _spawnEnemy;				//���ʹ̰� ���� �Ǵ°�?
	bool _enemyTime;				//enemy �����ð��� �������ΰ�?

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

