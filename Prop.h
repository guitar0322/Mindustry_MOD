#pragma once
#include "GameObject.h"
class PropStat;
class Prop :
    public GameObject
{
public:
    Prop();
    ~Prop();
    Renderer* renderer;
    BoxCollider* collider;
    PropStat* stat;
    virtual void Update();
    virtual void Render();
};

