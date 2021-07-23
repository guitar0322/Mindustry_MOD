#pragma once
#include "Prop.h"

class ResourceManager;
class CoreComponent;

class Core :
	public Prop
{
public:
	CoreComponent* coreComponent;
	Core();
	~Core();
	
	virtual void Init();
};

