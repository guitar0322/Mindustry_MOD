#pragma once
#include "Component.h"

//class ProjectileManager;
class Projectile :
	public Component
{
private:
	//ProjectileManager* _projectileManager;
	float _speed;
	float _angle;
	float _speedX, _speedY;
	float _radius;


public:
	Projectile();
	~Projectile();

	virtual void Init();
	virtual void Update();

	float GetSpeed() const { return _speed; }
	void SetSpeed(float speed) { _speed = speed; }

	float GetAngle() const { return _angle; }
	void SetAngle(float angle) { _angle = angle; }

	void Move();
	void OnTriggerEnter(GameObject* gameObject);
};

