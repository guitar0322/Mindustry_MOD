#pragma once
#include "GameObject.h"
class ParticleObject :
    public GameObject
{
public:
    ParticleSystem* particleSystem;
    ParticleObject();
    ~ParticleObject();
};

