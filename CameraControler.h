#pragma once
#include "Component.h"

class Player;
class CameraControler :
	public Component
{
private:
	float _speedX;
	float _speedY;
	float _speed;
	float _accel;
	float _angle;
	float _deltaX;
	float _deltaY;

	bool _playerReSpawn;
	Player* _player;

public:
	CameraControler();
	~CameraControler();
	
	virtual void Init();
	virtual void Update();
	void PlayerRespawn();

	void SetPlayer(Player* player) { _player = player; }
};

