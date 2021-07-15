#pragma once
#include "Component.h"
class PropStat :
	public Component
{
private:
	int _hp;
public:
	virtual void Init();
};

