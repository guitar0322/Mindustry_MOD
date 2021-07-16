#include "stdafx.h"
#include "EnemyGround.h"
#include "EnemyGroundControler.h"

EnemyGround::EnemyGround()
{
	_enemyGroundControler = new EnemyGroundControler();
	AddComponent(_enemyGroundControler);
	_enemyGroundControler->Init();
}

EnemyGround::~EnemyGround()
{
}
