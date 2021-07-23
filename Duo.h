#pragma once
#include "Prop.h"
class Turret;
class Duo :
    public Prop
{
public:
    Turret* turret;
    ImageObject* base;
    Duo();
    ~Duo();

    virtual void Update();
    virtual void Render();
};

