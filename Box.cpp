#include "stdafx.h"
#include "Box.h"

Box::Box()
{
	collider = new BoxCollider();
	AddComponent(collider);
	collider->Init();
}

Box::~Box()
{
}
