#pragma once
#include "GameObject.h"

class Projectile;

class ProjectileObject :
	public GameObject
{
private:
	Renderer* _renderer;
	BoxCollider* _collider;
	Projectile* _projectile;

public:
	ProjectileObject();
	~ProjectileObject();

	Renderer* GetRendererComponent() const { return _renderer; }
	Projectile* GetProjectileComponent() const { return _projectile; }
	BoxCollider* GetColliderComponent() const { return _collider; }
};

