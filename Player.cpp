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

	collider = new BoxCollider();
	AddComponent(collider);
	collider->Init();
}
Player::~Player()
{
}
