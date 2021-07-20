#pragma once
#include "Prop.h"

class Production;

class Drill :
    public Prop
{
public:
    Drill();
    ~Drill();
    ImageObject* rotator;
    ImageObject* top;
    Production* production;
    virtual void Update();
    virtual void Render();
};

