#pragma once
#include "Component.h"
//#include "AnimObject.h"

class EnemyInfo;

class EnemyControler :
	public Component
{
protected:
	EnemyInfo* _enemyInfo;
	float _speed;
	float _angle;

	float _speedX;
	float _speedY;
	
public:
	EnemyControler();
	~EnemyControler();

	virtual void Init();
	virtual void Update();
};
