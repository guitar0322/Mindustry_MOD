#pragma once
#include "Scene.h"

class Player;

class PlayerScene : public Scene
{
private:
	ImageObject _backGround;
	//BoxCollider* _copperZone;
	Player* _player;
	UIBase _mineUI;
	long _mineCount;
public:
	PlayerScene();
	~PlayerScene();


	virtual HRESULT Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();
	float GetMineCount() const { return _mineCount; }
};

