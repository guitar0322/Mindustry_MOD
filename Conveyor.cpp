#include "stdafx.h"
#include "Conveyor.h"
#include "PropStat.h"
#include "TileInfo.h"
#include "Transport.h"

Conveyor::Conveyor()
{
	name = L"컨베이어 벨트";

	renderer->Init("conveyor");

	stat->SetHP(50.f);
	stat->SetSize(1);

	collider->SetSize(stat->GetSize() * TILESIZE, stat->GetSize() * TILESIZE);

	transport = new Transport();
	AddComponent(transport);
	transport->Init();

	animator = new Animator();
	AddComponent(animator);
	animator->Init();
	animator->AddClip("conveyor_I");
}

Conveyor::~Conveyor()
{
}
