#pragma once
#include "Box.h"
class Zone :
    public Box
{
public:
    Zone() { collider->isTrigger = true; };
    ~Zone() {};
};

