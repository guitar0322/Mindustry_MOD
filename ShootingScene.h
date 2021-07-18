#pragma once
#include "Scene.h"

class ShootingScene :
	public Scene
{
private:
	ImageObject _shootingScene;
	GameObject* _enemyControler;

	AnimObject* _testCore;					//TEST용입니다 삭제해도 됩니다
	
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
	void TestCore();						//TEST용 삭제해도 됩니당
	void SetProjectile();
	void SetEnemyManager();
};

