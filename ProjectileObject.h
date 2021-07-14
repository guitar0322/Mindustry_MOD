#pragma once
#include "GameObject.h"
//#include "ProjectileManager.h"

//class Projectile;

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

	Projectile* GetProjectileComponent() const { return _projectile; }
	Renderer* GetRendererComponent() const { return _renderer; }
	BoxCollider* GetColliderComponent() const { return _collider; }
};

