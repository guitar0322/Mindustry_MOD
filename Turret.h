#pragma once
#include "Component.h"

class ProjectileManager;
class EnemyManager;
class EnemyObject;

#define BULLET_MAX 20
class Turret :
    public Component
{
private:
    float _attackSpeed;
    float _attackRange;
    float _barrelLength;
    float _minDistance;
    int _preWave;
    int _nearEnemyIdx;
    int _bulletNum;
    float _distance;
    bool _isMax;
    ProjectileManager* _projectileManager;
    EnemyManager* _enemyManager;
    EnemyObject* _nearEnemy;
    vector<EnemyObject*> _curWaveEnemyV;
public:
    Turret();
    ~Turret();
    virtual void Init(float attackSpeed, float attackRange, float barrelLength);
    virtual void Update();
    virtual void Render();
    virtual void OnTriggerEnter(GameObject* gameObject);

    void AddBullet();

    void SetAttackRange(float range) { _attackRange = range; }
    float GetAttackRange() const { return _attackRange; }

    void SetAttackSpeed(float speed) { _attackSpeed = speed; }
    float GetAttackSpeed() const { return _attackSpeed; }

    void SetBarrelLength(float length) { _barrelLength = length; }
    void Fire();
    void ProbeEnemy();

    void LinkProjectileManager(ProjectileManager* projectileManager) { _projectileManager = projectileManager; }
    void LinkEnemyManager(EnemyManager* enemyManager) { _enemyManager = enemyManager; }

    bool GetIsMax() const { return _isMax; }
};

