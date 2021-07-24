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

	string _targetTag;
	Vector2 _firePt;

	//Vector2 _targetTag1;
	//Vector2 _targetTag;
	//string _targetTag1;
	//string _targetTag2;

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

	void SetTargetTag(string targetTag) { _targetTag = targetTag; }
	//Projecitle
	//addTagerTag해서 호출될때마다 걔가 벡터에 추가
	
	//void SetTargetTag1(Vector2 targetTag){ _targetTag1 = targetTag;}
	//void SetTargetTag1(string targetTag, string targetTag1) { _targetTag1 = targetTag;  _targetTag2 = targetTag1; }

	void Move();

	void SetFirePoint(Vector2 pt) { _firePt = pt; }
};

