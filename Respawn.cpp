#include "stdafx.h"
#include "Respawn.h"
#include "PlayerControler.h"
void Respawn::Update()
{
	if (_playerControler->GetPlayerDead() == true)
	{
		_respawnTime += TIMEMANAGER->getElapsedTime();
		if(_respawnTime >= 2.f)
		{ 
			_playerControler->Respawn();
			_respawnTime = 0;
		}
	}
}
