#pragma once
#include "EnemyControler.h"
class EnemyPlaneControler :
	public EnemyControler
{
public:
	EnemyPlaneControler();
	~EnemyPlaneControler();

	virtual void Init();
};

