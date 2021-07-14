#pragma once
#include "Scene.h"
#include "EnemyPlane.h"
#include "AnimObject.h"
#include "EnemyObject.h"
#include "EnemyPlaneControler.h"
#include "EnemyGround.h"
#include "EnemyGroundControler.h"

class ShootingScene :
	public Scene
{
private:
	ImageObject _shootingScene;
	GameObject* _enemyControler;
	EnemyObject* _enemyObject;

	AnimObject* _testCore;					//TEST���Դϴ� �����ص� �˴ϴ�
	
	EnemyPlane* _enemyPlane;
	GameObject* _enemyPlaneWeapon;

	EnemyGround* _enemyGround;
	GameObject* _enemyGround_Leg_Right;
	GameObject* _enemyGround_Leg_Left;
	GameObject* _enemyGround_Weapon_Right;
	GameObject* _enemyGround_Weapon_Left;

	GameObject* _projectileManager;

public:
	ShootingScene();
	~ShootingScene();

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	void SetScene();
	void SetEnemy();
	void TestCore();						//TEST�� �����ص� �˴ϴ�
	void SetProjectile();
};

