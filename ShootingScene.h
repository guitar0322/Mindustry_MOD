#pragma once
#include "Scene.h"
#include "EnemyPlane.h"
#include "AnimObject.h"
#include "EnemyObject.h"
#include "EnemyPlaneControler.h"

class ShootingScene :
	public Scene
{
private:
	ImageObject _shootingScene;
	GameObject* _enemyControler;
	EnemyObject* _enemyObject;

	AnimObject* _testCore;					//TEST���Դϴ� �����ص� �˴ϴ�
	
	EnemyPlane* _enemyPlane;
	EnemyPlaneControler* _enemyPlaneControler;

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
};

