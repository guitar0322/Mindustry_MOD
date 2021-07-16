#pragma once
#include "Component.h"

class EnemyInfo;
class ProjectileManager;

class EnemyControler :
	public Component
{
protected:
	EnemyInfo* _enemyInfo;
	EnemyControler* _enemyControler;

	ProjectileManager* _projectileManager;

	float _speed;
	float _angle;

	float _speedX;
	float _speedY;

	float _attackSpeed;

	bool _chaseCore;				//Core�� ���� ���°�?
	bool _isAttack;					//������ �ϴ°�?

	float _deltaX;
	float _deltaY;
	float _deltaAngle;
	float _enemyRadius;
public:
	EnemyControler();
	~EnemyControler();

	virtual void Init();
	virtual void Update();
};

