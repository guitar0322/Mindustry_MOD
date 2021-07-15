#pragma once
#include "Component.h"

class ProjectileManager;

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
		IDLE
	};
private:
	float _speed;
	float _armRecoverySpeed;
	float _targetAngle;
	float _angleSpeed;
	float _breakTime;
	DIRECTION _dir;
	bool _isLeft;
	bool _isDiagonal;
	bool _shootLeft;
	bool _shootRight;
	bool _isSlow;
	bool _isGathering;
	bool _isFire;
	ProjectileManager* _projectileManager;
public:
	virtual void Init();
	virtual void Update();
	float GetSpeed() const { return _speed; }
	float GetTargetAngle() const { return _targetAngle; }
	void SetProjectileManager(ProjectileManager* projectileManager) { _projectileManager = projectileManager; }
};

