#pragma once
#include "Component.h"
#include "GameInfo.h"

class ProjectileManager;
class PlayerLaser;
class PlayerConstructLaser;
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
	EnemyInfo* _enemyInfo;
	ProjectileManager* _projectileManager;

	/*================================================*/
	//플레이어 상태//
	float _speed;			//스피드
	float _accel;			//가속도
	float _targetAngle;		//회전방향
	float _angleSpeed;		//회전속도
	float _friction;		//마찰력
	int _hp;				//체력
	float _damage;

	/*================================================*/
	//웨폰 관련//
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
	float _barrelLength;
	int _hp;

	//상태 관련//
	DIRECTION _dir;
	bool _isLeft;
	bool _isSlow;
	bool _isCollecting;
	Vector2 _collectTile;
	bool _isDead;
	int _scaleFlag;
	bool _isHit;

	/*================================================*/
	//0720 유림 -> 자원 추출용
	PlayerLaser* _playerLaser;
	GameMap* _gameMap;
	GameInfo* _gameInfo;
	int _copperAmount, _leadAmount;
	float _correctingTIme;
	RESOURCE _colletingResources;
	/*================================================*/
	//0721 유림 -> 건축용
	PlayerConstructLaser* _playerConstructLaser;

public:
	virtual void Init();
	virtual void Update();
	virtual void Render();

	void KeyHandle();
	void PlayerDirection();
	void ResoucesCollect();
	void ShootResoucesLaser();
	void ShootConstructLaser();

	void BoosterFireScale();

	float GetHp() const { return _hp; }
	float GetSpeed() const { return _speed; }
	float GetTargetAngle() const { return _targetAngle; }
	bool GetPlayerDead() const { return _isDead; }
	void KeyHandle();
	bool GetPlayerRespawn() const { return _isRespawn; }
	void SetProjectileManager(ProjectileManager* projectileManager) { _projectileManager = projectileManager; }
	void SetGameInfo(GameInfo* gameInfo) { _gameInfo = gameInfo; }
	void SetGameMap(GameMap* gameMap) { _gameMap = gameMap; }

	void Hit(float damage);
	void Dead();
	void Respawn();
	void MoveHandler();

	/*===================================================================*/
	/*UI관련*/
	//UI ->유림 210721
	UIBase playerUI;
	UIBase playerHpUI;
	UIBase playerHpUIAlpha;
	UIBase playerHpUIPane;
	float hpUI;
	float reduceHP;
	float reduceTime;
	float alphaTime;

	void PlayerUIInit();
	void PlayerUIUpdate();
	void PlayerHpAlpha();
	/*===================================================================*/

};

