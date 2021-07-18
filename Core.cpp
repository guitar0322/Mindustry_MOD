#include "stdafx.h"
#include "Core.h"
#include "PropStat.h"
#include "TileInfo.h"

Core::Core()
{
}

Core::~Core()
{
}

void Core::Init()
{
	name = L"ÄÚ¾î";

	renderer->Init("core");

	stat->SetSize(3);
	stat->SetHP(30);

	collider->SetSize(stat->GetSize() * TILESIZE, stat->GetSize() * TILESIZE);
}
