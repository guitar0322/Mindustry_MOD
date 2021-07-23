#pragma once
#include "Component.h"
class ProjectileObject;
class EnemyObject;
class EnemyManager;
class ProjectileManager;

#define PROJECTILE_MIN 3
class Turret :
    public Component
{
private:
    float _attackSpeed;
    float _attackRange;
    float _damage;
    float _projectileSpeed;
    float _barrelLength;
	float _attackAngle;
    vector<ProjectileObject*> _projectileV;
	EnemyObject* _enemyObject;
	bool _isFire;
	float _fireCount;
	int _preWave;
	EnemyManager* _enemyManager;
	ProjectileManager* _projectilemanager;
	vector<EnemyObject*> _curWaveEnemy;
public:
    Turret();
    ~Turret();
    virtual void Init(float attackSpeed, float attackRange, float damage, float projectileSpeed, float barrelLength);
    virtual void Update();
    virtual void Render();

    void SetDamage(float damage) { _damage = damage; }
    float GetDamage() const { return _damage; }

    void SetAttackRange(float range) { _attackRange = range; }
    float GetAttackRange() const { return _attackRange; }

    void SetAttackSpeed(float speed) { _attackSpeed = speed; }
    float GetAttackSpeed() const { return _attackSpeed; }

    void SetBarrelLength(float length) { _barrelLength = length; }
    void SetProjectileSpeed(float speed);
	Transform* GetEnemy(EnemyObject* enemyobject){ _enemyObject = enemyobject; }

    void Fire();
    void ProbeEnemy();
    int GetActiveProjectileNum();

	void SetEnemyManager(EnemyManager* enemyManager) { _enemyManager = enemyManager; }
};

