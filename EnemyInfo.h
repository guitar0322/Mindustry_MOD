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

	float _enemyAngle;
	float _deadTime;

	int _hp;

	bool _isDeath;

	GameObject* _testCore;
	Transform* _testCoreTransform;
	EnemyManager* _enemyManager;
	
public:
	EnemyInfo();
	~EnemyInfo();

	virtual void Init();
	virtual void Update();
	void Hit(int damage);
	void Dead();

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

