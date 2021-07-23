#pragma once
#include "EnemyControler.h"

class ProjectileManager;

class EnemyPlaneControler :
	public EnemyControler
{
private:
	int _randomAngle;				//angle�� �������� �������ֱ� ���� ����
	bool _test;
	GameObject* _testCore;
	Transform* _coreTransform;
	ProjectileManager* _projectileManager;

	Transform* _playerTr;
	
//	GameObject* _player;
//	Transform* _playerTr;

public:
	EnemyPlaneControler();
	~EnemyPlaneControler();

	virtual void Init();
	virtual void Update();

	void RandomAngle();				// Core���� ���������� angle�� �ٲ��ִ� �Լ�

	void SetTestCore(GameObject* testCore) { _testCore = testCore; _coreTransform = testCore->transform;}
	void SetProjectileManager(ProjectileManager* projectileManager) { _projectileManager = projectileManager; }
//void SetPlayerTransform(Transform* playertr) { _playerTr = playertr; }
//	void SetPlayerTransform(GameObject* player) { _player = player; _playerTr = player->transform; }
	float GetDeltaAngle() const { return _deltaAngle; }
};

