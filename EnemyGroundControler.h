#pragma once
#include "EnemyControler.h"

class ProjectileManager;
class Astar;
class Prop;

#define DEFAULT_WEAPON_RADIUS 25.f
#define ATTACK_WEAPON_RADIUS 23.f
#define DEFAULT_WEAPON_ANGLE 72.f
class EnemyGroundControler :
	public EnemyControler
{
private:
	bool _rightFire;
	bool _leftFire;

	ImageObject* _groundWeaponL;
	ImageObject* _groundWeaponR;

	GameObject* _testCore;
	Transform* _testCoreTransform;
	ProjectileManager* _projectileManager;
	Astar* _aStar;
	vector<pair<int, int>> _corePath;
	vector<Prop*> _curPropV;

	float _barrelAngle;

	float _barrelRRadius;
	float _barrelLRadius;
	float _barrelLDeltaAngle;
	float _barrelRDeltaAngle;

	float _pathFindTime;
	float _targetX;
	float _targetY;
	int _tileIdx;
	int _targetIdx;
	float _attackRange;
public:
	EnemyGroundControler();
	~EnemyGroundControler();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	void SetGroundWeapon();
	void SetGroundWeaponUpdate();
	void Attack();
	void SetTestCore(GameObject* testCore) { _testCore = testCore; _testCoreTransform = testCore->transform; }
	void SetProjectileManager(ProjectileManager* projectileManager) { _projectileManager = projectileManager; }
	void SetAstar(Astar* aStar) { _aStar = aStar; }
};

