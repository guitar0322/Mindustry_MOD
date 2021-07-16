#pragma once
#include "Component.h"

#define ENEMY_PROJECTILE_MAX 20
#define PLAYER_PROJECTILE_MAX 200

//class Projectile;
class ProjectileObject;
class EnemyManager;

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

	Transform* _enemyControlerTransform;
	EnemyManager* _enemyManager;
	//GameObject* _enemyManager;

	float _deltaAngle;

public:
	ProjectileManager();
	~ProjectileManager();
	
	virtual void Init();
	virtual void Update();
	virtual void Render();

	void ProjectileMove();
	void FireProjectile(float x, float y, float angle, PROJECTILE_TYPE type);

	void SetEnemyManager(EnemyManager* enemyManager) { _enemyManager = enemyManager; }
	//void SetEnemyManager(GameObject* enemyManager) { _enemyManager = enemyManager; }
};

