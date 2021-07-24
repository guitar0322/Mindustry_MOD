#include "stdafx.h"
#include "Duo.h"
#include "Turret.h"
#include "PropStat.h"
#include "TileInfo.h"

Duo::Duo()
{
	name = L"µà¿À";

	renderer->Init("duo_head");

	base = new ImageObject();
	base->Init();
	base->renderer->Init("duo_base");

	stat->SetSize(2);
	stat->SetHP(25);

	collider->SetSize(stat->GetSize() * TILESIZE, stat->GetSize() * TILESIZE);

	turret = new Turret();
	AddComponent(turret);
	turret->Init(0.5f, 500.f, 32.f);
	this->tag = TAGMANAGER->GetTag("prop");
}

Duo::~Duo()
{
}

void Duo::Update()
{
	Prop::Update();
}

void Duo::Render()
{
	base->Render();
	Prop::Render();
}
