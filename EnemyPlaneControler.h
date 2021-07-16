#pragma once
#include "EnemyControler.h"

class ProjectileManager;

class EnemyPlaneControler :
	public EnemyControler
{
private:
	int _randomAngle;				//angle�� �������� �������ֱ� ���� ����

	GameObject* _testCore;
	Transform* _testCoreTransform;
	ProjectileManager* _projectileManager;

public:
	EnemyPlaneControler();
	~EnemyPlaneControler();

	virtual void Init();
	virtual void Update();

	void RandomAngle();			// Core���� ���������� angle�� �ٲ��ִ� �Լ�

	void SetTestCore(GameObject* testCore) { _testCore = testCore; _testCoreTransform = testCore->transform;}
	void SetProjectileManager(ProjectileManager* projectileManager) { _projectileManager = projectileManager; }

	float GetDeltaAngle() const { return _deltaAngle; }
};

