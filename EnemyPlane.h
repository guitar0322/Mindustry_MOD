#pragma once
#include "EnemyObject.h"
class EnemyPlaneControler;

class EnemyPlane :
	public EnemyObject
{
private:
	EnemyPlaneControler* _enemyPlaneControler;
public:
	EnemyPlane();
	~EnemyPlane();
};

