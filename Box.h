#pragma once
#include "GameObject.h"
class Box :
    public GameObject
{
public:
    Box();
    ~Box();
    BoxCollider* collider;
};

