#include "stdafx.h"
#include "Player.h"
#include "PlayerControler.h"
Player::Player()
{
	renderer = new Renderer();
	AddComponent(renderer);

	controler = new PlayerControler();
	AddComponent(controler);
	controler->Init();

}
Player::~Player()
{
}
