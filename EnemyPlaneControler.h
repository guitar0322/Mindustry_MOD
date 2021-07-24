#pragma once
#include "EnemyControler.h"

class ProjectileManager;

class EnemyPlaneControler :
	public EnemyControler
{
private:
	int _randomAngle;				//angle�� �������� �������ֱ� ���� ����
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
	void RandomAngle();				// Core���� ���������� angle�� �ٲ��ִ� �Լ�

	void SetTestCore(GameObject* testCore) { _testCore = testCore; _coreTransform = testCore->transform;}
	void SetProjectileManager(ProjectileManager* projectileManager) { _projectileManager = projectileManager; }
	void SetPlayerTransform(Transform* playertr) { _playerTr = playertr; }
	float GetDeltaAngle() const { return _deltaAngle; }
	/*******************************************************************
	* ���� �ֳʹ� ����
	* 1.������ �ھ���� ������ �׻� ���Ѵ�(targetAngle)
	* 2.�ھ �ִ°����� ����
	* 3.���� �濡 ���� �ֳʹ��� ������ �÷��̾���� �������̰� ���� ���� ���ϰ�, _attackRange�ȿ� ������ �÷��̾�� ���.
	* 3.attackRange���� �Ÿ��� ��������� �����Ѵ�.
	* 4.attackSpeed�� ������������ �����Ѵ�.
	* 
	* �̵� ����
	* 1.�߰����̴� ��� ������ true�϶� Ÿ�ٰ� �����Ÿ� ������ ������ false�� �ٲ�
	* 2.�߰����� �ƴҶ��� �����ð����� ���� ������ ����
	* 3.�ð��� ������ ��ȸ�ϸ鼭 ���� Ÿ���� ���Ѵ�.
	* 
	* 
	* ��ȸ ��� ����
	* 1.����, ������ �������� ����.
	* 2.Ÿ�ٰ��� ������ ���� �ֳʹ��� ������ ��ġ���������� ��ȸ
	* 
	* *Ÿ�ٰ��� ����(targetAngle)�� �ǽð����� ��� ���ؾߵǰ�, �������� �ֳʹ��� ������ ���� ������.
	********************************************************************/
};

