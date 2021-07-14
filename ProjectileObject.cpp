#include "stdafx.h"
#include "ProjectileObject.h"
#include "Projectile.h"
ProjectileObject::ProjectileObject()
{
	_renderer = new Renderer();
	AddComponent(_renderer);

	_collider = new BoxCollider();
	AddComponent(_collider);
	_collider->Init();

	_projectile = new Projectile();
	AddComponent(_projectile);
	_projectile->Init();
}

ProjectileObject::~ProjectileObject()
{
}
