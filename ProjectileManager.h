#pragma once
#include "Component.h"

#define ENEMY_PROJECTILE_MAX 20
#define PLAYER_PROJECTILE_MAX 200

class Projectile;
class ProjectileObject;

static enum PROJECTILE_TYPE
{
	ENEMY,
	PLAYER
};

class ProjectileManager :
	public Component
{
private:
	vector<ProjectileObject*> _enemyProjectileV;
	vector<ProjectileObject*> _playerProjectileV;

	ProjectileObject* _enemyProjectile;
	ProjectileObject* _playerProjectile;

public:
	ProjectileManager();
	~ProjectileManager();
	
	virtual void Init();
	virtual void Update();
	virtual void Render();

	void ProjectileMove();
	void FireProjectile(float x, float y, float angle, PROJECTILE_TYPE type);

};

