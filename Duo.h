#pragma once
#include "Prop.h"
class Turret;
class Duo :
    public Prop
{
public:
    Turret* turret;
	ImageObject* turret_Head;
	ImageObject* turret_Body;
    Duo();
    ~Duo();

};

