#pragma once
#include "Component.h"

class Player;

class Projectile :
	public Component
{
private:
	float _speed;
	float _angle;
	float _speedX, _speedY;
	float _radius;

	float _camX;
	float _camY;

	int _damage;
	string _targetTag;

	Player* _player;
	Transform* _projectileTransform;

public:
	Projectile();
	~Projectile();

	virtual void Init();
	virtual void Update();
	virtual void OnTriggerEnter(GameObject* gameObject);
	void EreaseProjectile();

	float GetSpeed() const { return _speed; }
	void SetSpeed(float speed) { _speed = speed; }

	float GetAngle() const { return _angle; }
	void SetAngle(float angle) { _angle = angle; }

	int GetDamage()  const { return _damage; }
	void SetDamage(int damage) { _damage = damage; }

	void SetTargetTag(string targetTag) { _targetTag = targetTag; }
	Transform* GetProjectileTransform(Transform* projectiletransform) { _projectileTransform = projectiletransform; }

	void Move();
};

