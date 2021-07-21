#pragma once
#include "Component.h"

class CameraControler :
    public Component
{
private:
	Transform* _playerTr;
	float _speed;
	float _speedX;
	float _speedY;
	float _angle;
public:
	CameraControler();
	~CameraControler();
	virtual void Init();
	virtual void Update();
	void SetPlayerTr(Transform* playerTr) { _playerTr = playerTr; }
};