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

	//��ġ�� ���ǵ� ���� �� ������ �ʿ䰡 ���� 
	// ��ǥ�� �ʿ��ϴ� Transform�� �������°� ����
	
	//��� ����� �� ����������� ��¥ AnimObject
	//AnimObject ���̴� Reneder ANimator�� ����
	//TEstCore�� render�� animator�� enemyinfo�� �� �ʿ䰡 ����
	
	GameObject* _testCore;
	//���� testCore�� GameObject�� ������ (�� ���� �� ������)
	
	Transform* _testCoreTransform;
	//testCore�� transform�� ���� ���� ���� transform ����

	
public:
	EnemyInfo();
	~EnemyInfo();

	virtual void Init();
	virtual void Update();

	void SetTestCore(GameObject* testCore) {_testCore = testCore;
	_testCoreTransform = testCore->transform;}

	Transform* GetCoreTransform() const { return _testCoreTransform; }
	//testCore�� ���� �־���. _testCore�� transform�� ���� ���� �ƴϴ�
	//_testCoreTransform �� �� �ֱ�

	void SetSpeed(float speed) { _speed = speed; }
	float GetSpeed() const { return _speed; }
	float GetCoreAngle() const { return _angle; }
	float GetSpeedX() const { return _speedX; }
	float GetSpeedY() const { return _speedY; }

	float GetEnemyAngle() const { return _enemyAngle; }
};

