#pragma once
#include "Box.h"
class Zone :
    public Box
{
public:
    Zone() { collider->SetIsTrigger(true);};
    ~Zone() {};
};

