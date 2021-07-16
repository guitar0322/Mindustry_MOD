#pragma once
#include "EnemyObject.h"

class EnemyGroundControler;
class EnemyGround :
	public EnemyObject
{
private:
	EnemyGroundControler* _enemyGroundControler;

public:
	EnemyGround();
	~EnemyGround();
};

