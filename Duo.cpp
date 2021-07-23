#include "stdafx.h"
#include "Duo.h"
#include "Turret.h"
#include "PropStat.h"
#include "TileInfo.h"

Duo::Duo()
{
	name = L"µà¿À";

	//renderer->Init("duo_body");
	renderer->Init("duo_top");

	turret_Head = new ImageObject();
	turret_Head->Init();
	turret_Head->renderer->Init("duo_top");

	turret_Body = new ImageObject();
	turret_Body->Init();
	turret_Body->renderer->Init("duo_body");

	stat->SetSize(2);
	stat->SetHP(50);

	collider->SetSize(stat->GetSize() * TILESIZE, stat->GetSize() * TILESIZE);

	turret = new Turret();
	AddComponent(turret);
	turret->Init(0.5f, 300.f, 10.f, 300.f, 16.f);
}

Duo::~Duo()
{
}
