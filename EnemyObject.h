#pragma once
#include "GameObject.h"
#include "EnemyControler.h"
#include "EnemyInfo.h"

class EnemyObject :
	public GameObject
{
private:
	Renderer* _renderer;
	Animator* _animator;
	BoxCollider* _collider;
	EnemyInfo* _enemyInfo;
public:
	EnemyObject();
	~EnemyObject();
};

