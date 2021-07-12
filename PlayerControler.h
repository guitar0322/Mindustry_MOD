#pragma once
#include "Component.h"

class PlayerControler :
	public Component
{
private:
	enum DIRECTION {
		LEFT,
		UP,
		RIGHT,
		DOWN,
		LEFT_UP,
		RIGHT_UP,
		LEFT_DOWN,
		RIGHT_DOWN,
	};
private:
	float _speed;
	float _armRecoverySpeed;
	float _targetAngle;
	float _angleSpeed;
	DIRECTION _dir;
	bool _isLeft;
	bool _shootLeft;
	bool _shootRight;
public:
	virtual void Init();
	virtual void Update();
};

