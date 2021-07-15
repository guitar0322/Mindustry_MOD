#include "stdafx.h"
#include "Duo.h"
#include "Turret.h"
#include "PropStat.h"
#include "TileInfo.h"

Duo::Duo()
{
	name = L"µà¿À";

	renderer->Init("duo");

	stat->SetSize(1);
	stat->SetHP(50);

	collider->SetSize(stat->GetSize() * TILESIZE, stat->GetSize() * TILESIZE);

	turret = new Turret();
	AddComponent(turret);
	turret->Init(0.5f, 300.f, 10.f, 300.f, 16.f);
}

Duo::~Duo()
{
}
