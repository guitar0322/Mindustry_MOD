#include "stdafx.h"
#include "Distributor.h"
#include "ResDistribute.h"
#include "PropStat.h"

Distributor::Distributor()
{
	renderer->Init("distributor");

	resDistribute = new ResDistribute();
	AddComponent(resDistribute);
	resDistribute->Init();

	stat->SetHP(50);
	stat->SetSize(1);

	collider->SetSize(stat->GetSize() * 32, stat->GetSize() * 32);
	collider->RefreshPartition();
}

Distributor::~Distributor()
{
}
