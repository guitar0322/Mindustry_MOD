#pragma once
#include "Component.h"

class ProjectileManager;
class PlayerLaser;
class EnemyInfo;

#define DEFAULT_WEAPON_DISTANCE 11.41f
#define ATTACK_WEAPON_DISTANCE 9.41f
#define DEFAULT_WEAPON_ANGLE 60.f
#define BULLET_DISTANCE 17.11f
#define BULLET_ANGLE 60.f


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
	float _respawnTime;
	float _weaponLTrackRadius; //r2
	float _weaponRTrackRadius; //r2
	float _weaponLTrackAngle;
	float _weaponRTrackAngle;
	float _weaponLdistanceAngle;
	float _weaponRdistanceAngle;
	float _attackSpeed;
	float worldX, worldY;
	
	int _hp;

	DIRECTION _dir;
	bool _isLeft;
	bool _isDiagonal;
	bool _shootLeft;
	bool _shootRight;
	bool _isSlow;
	bool _isGathering;
	bool _isFire;
	bool _isDead;
	bool _isRespawn;
	ProjectileManager* _projectileManager;

	//자원 추출 레이저
	PlayerLaser* _playerLaser;


	EnemyInfo* _enemyInfo;

public:
	virtual void Init();
	virtual void Update();
	virtual void Render();

	void PlayerDirection();

	float GetHp() const { return _hp; }
	float GetSpeed() const { return _speed; }
	float GetTargetAngle() const { return _targetAngle; }
	bool GetPlayerDead() const { return _isDead; }
	bool GetPlayerRespawn() const { return _isRespawn; }
	void SetProjectileManager(ProjectileManager* projectileManager) { _projectileManager = projectileManager; }

	void Hit(float damage);
	void Dead();
	void Respawn();
	void RespawnTime();
};

