#include "stdafx.h"
#include "EnemyObject.h"

EnemyObject::EnemyObject()
{
	_renderer = new Renderer();
	AddComponent(_renderer);

	_animator = new Animator();
	AddComponent(_animator);
	_animator->Init();

	_collider = new BoxCollider();
	AddComponent(_collider);
	_collider->Init();
	
	_enemyInfo = new EnemyInfo();
	AddComponent(_enemyInfo);
}

EnemyObject::~EnemyObject()
{
}
