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


	animator = new Animator();
	AddComponent(animator);
	animator->Init();
	animator->AddClip("conveyor_I");
	animator->AddClip("conveyor_L");
	animator->AddClip("conveyor_L2");
	animator->AddClip("conveyor_T");
	animator->AddClip("conveyor_T2");
	animator->AddClip("conveyor_T3");
	animator->AddClip("conveyor_cross");

	transport = new Transport();
	AddComponent(transport);
	transport->Init();

	this->tag = TAGMANAGER->GetTag("prop");
}

Conveyor::~Conveyor()
{
}
