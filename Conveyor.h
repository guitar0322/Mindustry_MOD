#pragma once
#include "Prop.h"
class Transport;

class Conveyor :
    public Prop
{
public:
    Transport* transport;
    Animator* animator;
    Conveyor();
    ~Conveyor();
};

