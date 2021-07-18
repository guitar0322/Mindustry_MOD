#pragma once
#include "Component.h"

class Player;
class EnemyInfo;

class Projectile :
	public Component
{
private:
	float _speed;
	float _angle;
	float _speedX, _speedY;
	float _radius;

	int _damage;

	Player* _player;
	EnemyInfo* _enemyInfo;

public:
	Projectile();
	~Projectile();

	virtual void Init();
	virtual void Update();
	virtual void OnTriggerEnter(GameObject* gameObject);

	float GetSpeed() const { return _speed; }
	void SetSpeed(float speed) { _speed = speed; }

	float GetAngle() const { return _angle; }
	void SetAngle(float angle) { _angle = angle; }

	int GetDamage()  const { return _damage; }
	void SetDamage(int damage) { _damage = damage; }

	void Move();
};

