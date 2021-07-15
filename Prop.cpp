#include "stdafx.h"
#include "Prop.h"
#include "PropStat.h"
Prop::Prop()
{
	renderer = new Renderer();
	AddComponent(renderer);

	collider = new BoxCollider();
	AddComponent(collider);
	collider->Init();

	stat = new PropStat();
	AddComponent(stat);
	stat->Init();
}

Prop::~Prop()
{
}
