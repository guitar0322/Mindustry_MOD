#pragma once
#include "Component.h"

#define ENEMY_PROJECTILE_MAX 100
#define PLAYER_PROJECTILE_MAX 200

class ProjectileObject;
class EnemyManager;
class Player;

static enum PROJECTILE_TYPE
{
	ENEMYPLANE,
	ENEMYGROUND,
	PLAYER
};	

class ProjectileManager :
	public Component
{
private:
	vector<ProjectileObject*> _enemyPlaneProjectileV;
	vector<ProjectileObject*> _playerProjectileV;

	ProjectileObject* _enemyPlaneProjectile;
	ProjectileObject* _playerProjectile;

	vector<ProjectileObject*> _enemyGroundProjectileV;
	ProjectileObject* _enemyGroundProjectile;
	
	Transform* _enemyControlerTransform;
	EnemyManager* _enemyManager;
	Player* _player;

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
	void SetPlayer(Player* player) { _player = player; }
};

