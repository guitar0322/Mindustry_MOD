#include "stdafx.h"
#include "Drill.h"
#include "PropStat.h"
#include "TileInfo.h"
#include "Production.h"

Drill::Drill()
{
	name = L"기계식 드릴";

	renderer->Init("drill_body");

	stat->SetSize(2);
	stat->SetHP(100);

	collider->SetSize(stat->GetSize() * TILESIZE, stat->GetSize() * TILESIZE);

	rotator = new ImageObject();
	rotator->Init();
	rotator->renderer->Init("drill_rotator");
	
	top = new ImageObject();
	top->Init();
	top->renderer->Init("drill_top");

	production = new Production();
	AddComponent(production);
	production->Init();

	this->tag = TAGMANAGER->GetTag("prop");
	this->transform->AddChild(rotator);
	this->transform->AddChild(top);
}

Drill::~Drill()
{
}

void Drill::Update()
{
	Prop::Update();
	rotator->transform->Rotate(0.5f);
}

void Drill::Render()
{
	Prop::Render();
	rotator->Render();
	top->Render();
}
