#pragma once
class PlayerControler;

class Respawn
{
private:
	float _respawnTime;
	PlayerControler* _playerControler;
public:
	void Update();
	void LinkPlayer(PlayerControler* playerControler) { _playerControler = playerControler; }
};

