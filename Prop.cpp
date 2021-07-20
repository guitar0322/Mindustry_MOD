#include "stdafx.h"
#include "Prop.h"
#include "PropStat.h"
#include "TileInfo.h"
Prop::Prop()
{
	renderer = new Renderer();
	AddComponent(renderer);
	renderer->Init(TILESIZE, TILESIZE);

	collider = new BoxCollider();
	AddComponent(collider);
	collider->Init();
	collider->SetSize(TILESIZE, TILESIZE);
	collider->RefreshPartition();

	stat = new PropStat();
	AddComponent(stat);
	stat->Init();
}

Prop::~Prop()
{
}

void Prop::Update()
{
	GameObject::Update();
}

void Prop::Render()
{
	GameObject::Render();
}
