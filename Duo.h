#pragma once
#include "Prop.h"
class Turret;
class Duo :
    public Prop
{
public:
    Turret* turret;
    Duo();
    ~Duo();
};

