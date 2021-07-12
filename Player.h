#pragma once
#include "GameObject.h"

class PlayerControler;
class Renderer;

class Player :
	public GameObject
{
public:
	Player();
	~Player();
	Renderer* renderer;
	PlayerControler* controler;
};

