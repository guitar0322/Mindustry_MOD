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
	int _damage;

	vector<string> _targetTag;
	Vector2 _firePt;

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

	void AddTargetTag(string targetTag) {_targetTag.push_back(targetTag); }

	//Projecitle
	//addTagerTag해서 호출될때마다 걔가 벡터에 추가

	void Move();

	void SetFirePoint(Vector2 pt) { _firePt = pt; }
};

