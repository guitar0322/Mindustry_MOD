#pragma once
#include "Scene.h"

class ShootingScene :
	public Scene
{
private:
	ImageObject _shootingScene;
	GameObject* _enemyControler;

	AnimObject* _testCore;					//TEST���Դϴ� �����ص� �˴ϴ�
	
	GameObject* _projectileManager;
	GameObject* _enemyManager;

	AnimationClip* _enemyDaggerWalk;

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

