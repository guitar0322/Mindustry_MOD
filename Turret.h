#pragma once
#include "Component.h"
class ProjectileObject;

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
    vector<ProjectileObject*> _projectileV;
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

    void Fire();
    void ProbeEnemy();
    int GetActiveProjectileNum();
};

