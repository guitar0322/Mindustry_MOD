#pragma once
#include "Component.h"
#include "GameInfo.h"

class ProjectileManager;
class PlayerLaser;
class PlayerConstructLaser;
class EnemyInfo;
class GameMap;
class PropFactory;

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
	PropFactory* _propFactory;

	/*================================================*/
	//�÷��̾� ����//
	float _speed;			//���ǵ�
	float _accel;			//���ӵ�
	float _targetAngle;		//ȸ������
	float _angleSpeed;		//ȸ���ӵ�
	float _friction;		//������
	int _hp;				//ü��
	float _damage;

	/*================================================*/
	//���� ����//
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

	//���� ����//
	DIRECTION _dir;
	bool _isLeft;
	bool _isSlow;
	bool _isCollecting;
	Vector2 _collectTile;
	bool _isDead;
	int _scaleFlag;
	bool _isHit;

	/*================================================*/
	//0720 ���� -> �ڿ� �����
	PlayerLaser* _playerLaser;
	GameMap* _gameMap;
	GameInfo* _gameInfo;
	int _copperAmount, _leadAmount;
	float _correctingTIme;
	RESOURCE _colletingResources;


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
	void SetHp(int hp) { _hp = hp; }
	float GetSpeed() const { return _speed; }
	float GetTargetAngle() const { return _targetAngle; }
	bool GetPlayerDead() const { return _isDead; }
	void SetProjectileManager(ProjectileManager* projectileManager) { _projectileManager = projectileManager; }
	void SetGameInfo(GameInfo* gameInfo) { _gameInfo = gameInfo; }
	void SetGameMap(GameMap* gameMap) { _gameMap = gameMap; }
	void LinkProFactory(PropFactory* propFactory) { _propFactory = propFactory; }
	void SetConstructLaser(int x, int y, int size);

	bool GetIsCollecting() const { return _isCollecting; }
	void Hit(float damage);
	void Dead();
	void Respawn();
	void MoveHandler();
	/*================================================*/
	//0721 ���� -> �����
	PlayerConstructLaser* playerConstructLaser;
	/*===================================================================*/
	/*UI����*/
	//UI ->���� 210721
	UIBase playerUI;
	UIBase playerHpUI;
	UIBase playerHpUIPane;
	float hpUI;
	float reduceTime;

	void PlayerUIInit();
	void PlayerUIUpdate();
	void PlayerHpBar();
	/*===================================================================*/

};

