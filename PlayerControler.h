#pragma once
#include "Component.h"
#include "GameInfo.h"

class ProjectileManager;
class PlayerLaser;
class EnemyInfo;
class GameMap;

#define DEFAULT_WEAPON_DISTANCE 10.269f
#define ATTACK_WEAPON_DISTANCE 9.13f
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
	float _accel;
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
	float _worldX, _worldY;
	float _boosterTime;

	int _hp;

	DIRECTION _dir;
	bool _isLeft;
	bool _isSlow;
	bool _isCollecting;
	Vector2 _collectTile;
	bool _isDead;
	bool _isRespawn;
	int _scaleFlag;
	ProjectileManager* _projectileManager;

	//자원 추출 레이저
	PlayerLaser* _playerLaser;

	EnemyInfo* _enemyInfo;

	//0720 유림 -> 자원 추출용
	GameMap* _gameMap;
	GameInfo* _gameInfo;
	int _copperAmount, _leadAmount;
	float _correctingTIme;
	RESOURCE _colletingResources;


public:
	virtual void Init();
	virtual void Update();
	virtual void Render();

	void PlayerDirection();
	void ResoucesCollect();
	void ShootResoucesLaser();
	void BoosterFireScale();

	float GetHp() const { return _hp; }
	float GetSpeed() const { return _speed; }
	float GetTargetAngle() const { return _targetAngle; }
	bool GetPlayerDead() const { return _isDead; }
	bool GetPlayerRespawn() const { return _isRespawn; }
	void KeyHandle();
	void SetProjectileManager(ProjectileManager* projectileManager) { _projectileManager = projectileManager; }
	void SetGameInfo(GameInfo* gameInfo) { _gameInfo = gameInfo; }
	void SetGameMap(GameMap* gameMap) { _gameMap = gameMap; }


	void Hit(float damage);
	void Dead();
	void Respawn();
	void RespawnTime();
	void MoveHandler();
};

