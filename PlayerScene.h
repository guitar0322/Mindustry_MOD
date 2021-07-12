#pragma once
#include "Scene.h"

class Player;

class PlayerScene : public Scene
{
private:
	ImageObject backGround;
	Player* player;
	ImageObject* playerCell;
	ImageObject* playerLeft;
	ImageObject* playerRight;

public:
	PlayerScene();
	~PlayerScene();
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();
};

