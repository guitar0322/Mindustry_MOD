#pragma once
#include "Component.h"

class EnemyManager;

class EnemyInfo :
	public Component
{
private:
	float _speed;
	float _angle;

	float _speedX;
	float _speedY;

	int _hp;

	float _enemyAngle;

	float _deadTime;


	GameObject* _testCore;
	Transform* _testCoreTransform;
	
	EnemyManager* _enemyManager;
	
public:
	EnemyInfo();
	~EnemyInfo();

	bool isDeath;

	virtual void Init();
	virtual void Update();
	void HitEnemy();

	void SetTestCore(GameObject* testCore) {_testCore = testCore;
	_testCoreTransform = testCore->transform;}
	Transform* GetCoreTransform() const { return _testCoreTransform; }
	
	void SetEnemyManager(EnemyManager* enemyManager) {_enemyManager = enemyManager;	}

	void SetSpeed(float speed) { _speed = speed; }

	void SetHp(int hp) { hp = _hp; }
	int GetHp() const { return _hp; }

	float GetSpeed() const { return _speed; }
	float GetCoreAngle() const { return _angle; }
	float GetSpeedX() const { return _speedX; }
	float GetSpeedY() const { return _speedY; }

	float GetEnemyAngle() const { return _enemyAngle; }
};

