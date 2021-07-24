#pragma once
#include "EnemyControler.h"

class ProjectileManager;

class EnemyPlaneControler :
	public EnemyControler
{
private:
	int _randomAngle;				//angle값 랜덤으로 설정해주기 위한 변수
	bool _playerAttack;
	float _playerAttackAngle;
	float test;
	bool test1;
	bool test2;

	GameObject* _testCore;
	Transform* _coreTransform;
	ProjectileManager* _projectileManager;
	Transform* _playerTr;
	ImageObject* _shadow;


public:
	EnemyPlaneControler();
	~EnemyPlaneControler();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	void SetShadow();
	void RandomAngle();				// Core와의 범위내에서 angle값 바꿔주는 함수

	void SetTestCore(GameObject* testCore) { _testCore = testCore; _coreTransform = testCore->transform;}
	void SetProjectileManager(ProjectileManager* projectileManager) { _projectileManager = projectileManager; }
	void SetPlayerTransform(Transform* playertr) { _playerTr = playertr; }
	float GetDeltaAngle() const { return _deltaAngle; }
	/*******************************************************************
	* 비행 애너미 설계
	* 1.각도는 코어와의 각도를 항상 구한다(targetAngle)
	* 2.코어가 있는곳으로 직진
	* 3.가는 길에 현재 애너미의 각도와 플레이어와의 각도차이가 일정 각도 이하고, _attackRange안에 있으면 플레이어에게 쏜다.
	* 3.attackRange보다 거리가 가까워지면 공격한다.
	* 4.attackSpeed가 충족했을때만 공격한다.
	* 
	* 이동 설계
	* 1.추격중이다 라는 변수가 true일때 타겟과 일정거리 안으로 들어오면 false로 바꿈
	* 2.추격중이 아닐때는 랜덤시간동안 현재 방향대로 직진
	* 3.시간이 지나면 선회하면서 다음 타겟을 정한다.
	* 
	* 
	* 선회 방식 설계
	* 1.왼쪽, 오른쪽 랜덤으로 설정.
	* 2.타겟과의 각도와 현재 애너미의 각도가 일치해질때까지 선회
	* 
	* *타겟과의 각도(targetAngle)를 실시간으로 계속 구해야되고, 실질적인 애너미의 각도는 따로 가진다.
	********************************************************************/
};

