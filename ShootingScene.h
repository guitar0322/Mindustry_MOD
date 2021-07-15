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

	EnemyGround* _enemyGround;
	GameObject* _projectileManager;
	GameObject* _enemyManager;

public:
	ShootingScene();
	~ShootingScene();

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	void SetScene();
	void TestCore();						//TEST�� �����ص� �˴ϴ�
	void SetProjectile();
	void SetEnemyManager();
};

