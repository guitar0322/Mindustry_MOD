#pragma once
#include "Component.h"

class EnemyInfo :
	public Component
{
private:
	float _speed;
	float _angle;
	float _enemyAngle;

	float _speedX;
	float _speedY;

	//위치만 쓸건데 굳이 다 가져올 필요가 없다 
	// 좌표만 필요하니 Transform을 가져오는게 좋다
	
	//모든 기능을 다 쓰고싶을떄는 진짜 AnimObject
	//AnimObject 차이는 Reneder ANimator가 있음
	//TEstCore의 render와 animator가 enemyinfo가 알 필요가 없음
	
	GameObject* _testCore;
	//현재 testCore을 GameObject로 선언함 (값 없는 빈 껍데기)
	
	Transform* _testCoreTransform;
	//testCore의 transform을 갖고 오기 위해 transform 선언

	
public:
	EnemyInfo();
	~EnemyInfo();

	virtual void Init();
	virtual void Update();

	void SetTestCore(GameObject* testCore) {_testCore = testCore;
	_testCoreTransform = testCore->transform;}

	Transform* GetCoreTransform() const { return _testCoreTransform; }
	//testCore에 값을 주었다. _testCore의 transform는 이제 빈값이 아니니
	//_testCoreTransform 에 값 주기

	void SetSpeed(float speed) { _speed = speed; }
	float GetSpeed() const { return _speed; }
	float GetCoreAngle() const { return _angle; }
	float GetSpeedX() const { return _speedX; }
	float GetSpeedY() const { return _speedY; }

	float GetEnemyAngle() const { return _enemyAngle; }
};

