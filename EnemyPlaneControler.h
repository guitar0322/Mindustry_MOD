#pragma once
#include "EnemyControler.h"

class ProjectileManager;

class EnemyPlaneControler :
	public EnemyControler
{
private:
	bool _chaseCore;				//Core�� ���� ���°�?
	bool _isAttack;					//angle���� random���� �ִ°�?
	bool _weaponRebound;			//����ݵ�

	float _attackSpeed;
	float _projectileRadius;		//Projectile ������
	float _deltaX;
	float _deltaY;
	float _weaponRadius;			//���� ������
	float _rebound;					//���� �ݵ���
	float _reboundTime;

	float _x, _y;

	float _weaponCorrectionX, _weaponCorrectionY;		//���� ��ǥ ���� x,y

	float _deltaAngle;

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
