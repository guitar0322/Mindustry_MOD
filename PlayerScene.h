#pragma once
#include "Scene.h"
#include "ProjectileManager.h"

class Player;

class PlayerScene : public Scene
{
private:
	ImageObject backGround;
	Player* player;
	ImageObject* playerCell;
	ImageObject* playerLeft;
	ImageObject* playerRight;
	GameObject* _projectileManager;

public:
	PlayerScene();
	~PlayerScene();
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();
};

