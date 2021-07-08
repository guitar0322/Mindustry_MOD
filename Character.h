#pragma once
#include "GameObject.h"
class Character :
    public GameObject
{
public:
    Character();
    ~Character();
    Renderer* renderer;
    BoxCollider* collider;
    Animator* animator;
    ZOrder* zOrder;
};


