#include "stdafx.h"
#include "EnemyPlane.h"
#include "EnemyPlaneControler.h"
EnemyPlane::EnemyPlane()
{
	_enemyPlaneControler = new EnemyPlaneControler();
	AddComponent(_enemyPlaneControler);
	_enemyPlaneControler->Init();
}

EnemyPlane::~EnemyPlane()
{
}

