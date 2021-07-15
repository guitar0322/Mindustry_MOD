#pragma once
#include "Component.h"
class PropStat :
	public Component
{
private:
	int _hp;
	int _size;
public:
	virtual void Init();
	void SetHP(int hp) { _hp = hp; }
	void SetSize(int size) { _size = size; }
	int GetSize() const { return _size; }
};

