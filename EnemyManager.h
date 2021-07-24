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
class Astar;

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

	Astar* _aStar;

	Transform* _playerTr;

	int _curWave;					//���� ���̺�
	int _timeSecond;				//�ð� ��
	int _timeMinute;				//�ð� ��

	float _enemySpawnTime;			//���ʹ� ���� �ð����ֱ�
	
	bool _spawnEnemy;				//���ʹ̰� ���� �Ǵ°�?
	bool _enemyTime;				//enemy �����ð��� �������ΰ�?
	bool _waveSkip;

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

	int GetTimeSecond() const { return _timeSecond; }
	void SetTimeSecond(int second) { _timeSecond = second; }
	int GetTimeMinute() const { return _timeMinute; }
	void SetTimeMinute(int minute) { _timeMinute = minute; }
	int GetCurWave() const { return _curWave; }
	void SetCurWave(int wave) { _curWave = wave; }

	vector<EnemyObject*> GetCurWaveEnemy();
	vector<int> GetWave(int wave) { return _waveV[wave]; }
	EnemyObject* GetEnemy(int idx);
	void SetWaveSkip(bool waveskip) { _waveSkip = waveskip; }

	void SetProjectileManager(ProjectileManager* projectileManager){ _projectileManager = projectileManager; }
	void SetTestCoreTransform(GameObject* testCore) { _testCore = testCore; _testCoreTransform = testCore->transform; }
	void SetEnemyInfo(EnemyInfo* enemyInfo) { _enemyInfo = enemyInfo; }
	void SetAstar(Astar* aStar) { _aStar = aStar; }
	void SetPlayerTransform(Transform* playetr) { _playerTr = playetr;}
};

