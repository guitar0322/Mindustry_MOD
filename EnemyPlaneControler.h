#pragma once
#include "EnemyControler.h"

class ProjectileManager;

class EnemyPlaneControler :
	public EnemyControler
{
private:
	int _randomAngle;				//angle값 랜덤으로 설정해주기 위한 변수

	GameObject* _testCore;
	Transform* _testCoreTransform;
	ProjectileManager* _projectileManager;

public:
	EnemyPlaneControler();
	~EnemyPlaneControler();

	virtual void Init();
	virtual void Update();

	void RandomAngle();			// Core와의 범위내에서 angle값 바꿔주는 함수

	void SetTestCore(GameObject* testCore) { _testCore = testCore; _testCoreTransform = testCore->transform;}
	void SetProjectileManager(ProjectileManager* projectileManager) { _projectileManager = projectileManager; }

	float GetDeltaAngle() const { return _deltaAngle; }
};

