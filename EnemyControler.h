#pragma once
#include "Component.h"

class EnemyInfo;
class AnimObject;
class ProjectileManager;

class EnemyControler :
	public Component
{
protected:
	EnemyInfo* _enemyInfo;
	EnemyControler* _enemyControler;

	//GameObject* _projectileManager;
	ProjectileManager* _projectileManager;
	//Transform* _projectileManagerTransform;

	float _speed;
	float _angle;

	float _speedX;
	float _speedY;

	float _attackSpeed;

	bool _chaseCore;				//Core를 향해 가는가?
	bool _isAttack;					//공격을 하는가?

	float _deltaX;
	float _deltaY;
	float _deltaAngle;
	float _enemyRadius;

	
public:
	EnemyControler();
	~EnemyControler();

	virtual void Init();
	virtual void Update();

	void SetProjectileManagerTransform(ProjectileManager* projectileManager) { _projectileManager = projectileManager; }// _projectileManagerTransform = projectileManager->transform;
};

