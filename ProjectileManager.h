#pragma once
#include "Component.h"

#define ENEMY_PROJECTILE_MAX 20
#define PLAYER_PROJECTILE_MAX 5

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
	GameObject* _enemyPlaneControler;
	Transform* _enemyPlaneControlerTransform;

	float _deltaAngle;

public:
	ProjectileManager();
	~ProjectileManager();
	
	virtual void Init();
	virtual void Update();
	virtual void Render();

	void ProjectileMove();
	void FireProjectile(float x, float y, float angle, PROJECTILE_TYPE type);

	void SetEnemyPlanecontrolerTransform(GameObject* enemyPlaneControler) { _enemyPlaneControler = enemyPlaneControler; _enemyPlaneControlerTransform = enemyPlaneControler->transform; }
};

