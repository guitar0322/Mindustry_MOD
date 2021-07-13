#pragma once
#include "EnemyControler.h"

class EnemyGroundControler :
	public EnemyControler
{
private:
	GameObject* _testCore;
	Transform* _testCoreTransform;

public:
	EnemyGroundControler();
	~EnemyGroundControler();

	virtual void Init();
	virtual void Update();
};

