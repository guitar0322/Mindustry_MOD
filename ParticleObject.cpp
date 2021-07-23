#include "stdafx.h"
#include "ParticleObject.h"

ParticleObject::ParticleObject()
{
	particleSystem = new ParticleSystem();
	AddComponent(particleSystem);
}

ParticleObject::~ParticleObject()
{
}
