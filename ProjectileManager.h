#pragma once
#include "Component.h"

#define ENEMY_PROJECTILE_MAX 50
#define PLAYER_PROJECTILE_MAX 20

class ProjectileObject;
class EnemyManager;
class Player;

static enum PROJECTILE_TYPE
{
	ENEMYPLANE,
	ENEMYGROUND,
	PLAYER,
};	

class ProjectileManager :
	public Component
{
private:
	vector<ProjectileObject*> _enemyPlaneProjectileV;
	vector<ProjectileObject*> _enemyGroundProjectileV;
	vector<ProjectileObject*> _playerProjectileV;
public:
	ProjectileManager();
	~ProjectileManager();
	
	virtual void Init();
	virtual void Update();
	virtual void Render();

	void ProjectileMove();
	void FireProjectile(float x, float y, float angle, PROJECTILE_TYPE type);
};

