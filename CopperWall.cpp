#include "stdafx.h"
#include "CopperWall.h"
#include "PropStat.h"
#include "TileInfo.h"
CopperWall::CopperWall()
{
	name = L"±¸¸® º®";

	renderer->Init("copper_wall");

	stat->SetSize(1);
	stat->SetHP(100);

	collider->SetSize(stat->GetSize() * TILESIZE, stat->GetSize() * TILESIZE);
	this->tag = TAGMANAGER->GetTag("prop");

}

CopperWall::~CopperWall()
{
}
