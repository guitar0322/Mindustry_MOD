#pragma once
#include "Component.h"

#define ENEMY_MAX 10
#define WAVE_NUM 10

class EnemyPlane;
class EnemyGround;
class ProjectileManager;

class EnemyManager :
	public Component
{
private:
	vector<EnemyObject*> _enemyV;
	vector<int> _waveV[WAVE_NUM];

	EnemyPlane* _enemyPlane;
	EnemyGround* _enemyGround;

	ProjectileManager* _projectileManager;
	//GameObject* _projectileManager;

	GameObject* _testCore;
	Transform* _testCoreTransform;

	int _curWave;					//���� ���̺�
	float _enemySpawnTime;			//���ʹ� ���� �ð����ֱ�
	int _timeSecond;				//�ð� ��
	int _timeMinute;				//�ð� ��
	bool _spawnEnemy;				//���ʹ̰� ���� �Ǵ°�?
	bool _enemyTime;				//enemy �����ð��� �������ΰ�?

	
public:
	EnemyManager();
	~EnemyManager();

	virtual void Init();
	virtual void Update();
	virtual void Render();

	void SetEnemyTime();
	void EnemyTimer();
	void SpawnEnemy();

	float GetTimeSecond() const { return _timeSecond; }
	float GetTimeMinute() const { return _timeMinute; }

	//void SetProjectileManager(GameObject* projectileManager){ _projectileManager = projectileManager; }
	void SetProjectileManager(ProjectileManager* projectileManager){ _projectileManager = projectileManager; }
	void SetTestCoreTransform(GameObject* testCore) { _testCore = testCore; _testCoreTransform = testCore->transform; }
};

