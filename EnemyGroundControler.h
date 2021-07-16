#pragma once
#include "EnemyControler.h"

class ProjectileManager;

class EnemyGroundControler :
	public EnemyControler
{
private:
	bool _rightFire;
	bool _leftFire;

	GameObject* _testCore;
	Transform* _testCoreTransform;
	ProjectileManager* _projectileManager;

public:
	EnemyGroundControler();
	~EnemyGroundControler();

	virtual void Init();
	virtual void Update();

	void SetTestCore(GameObject* testCore) { _testCore = testCore; _testCoreTransform = testCore->transform; }
	void SetProjectileManager(ProjectileManager* projectileManager) { _projectileManager = projectileManager; }
};

