#include "stdafx.h"
#include "ResDistribute.h"
#include "Item.h"
#include "Transport.h"
#include "Conveyor.h"
#include "ResourceManager.h"
#include "Duo.h"
#include "Turret.h"
#include "Distributor.h"
int distributePos[4][2] = { {33 , 0},{0 , 33},{-33 , 0},{0 , -33} };

ResDistribute::ResDistribute()
{
}

ResDistribute::~ResDistribute()
{
}

void ResDistribute::Update()
{
	if (_resQue.empty() == true) return;
	_distributeTime += TIMEMANAGER->getElapsedTime();
	if (_distributeTime >= 1.f)
	{
		_distributeDir = (_distributeDir + 1) % 4;

		if (linkProp[_distributeDir] == nullptr) return;

		Conveyor* linkConveyor = dynamic_cast<Conveyor*>(linkProp[_distributeDir]);
		if (linkConveyor != nullptr && linkConveyor->transport->GetIsLeck() == false && linkConveyor->transport->GetInResource() == nullptr)
		{
			float posX = transform->GetX() + distributePos[_distributeDir][0];
			float posY = transform->GetY() + distributePos[_distributeDir][1];
			_resourceManager->AddResource(_resQue.front(), posX, posY);
			_resQue.pop();
			_distributeTime = 0;
		}
		Duo* linkDuo = dynamic_cast<Duo*>(linkProp[_distributeDir]);
		if (linkDuo != nullptr && linkDuo->turret->GetIsMax() == false)
		{
			linkDuo->turret->AddBullet();
			_resQue.pop();
			_distributeTime = 0;
		}
		Distributor* linkDistributor = dynamic_cast<Distributor*>(linkProp[_distributeDir]);
		if (linkDistributor != nullptr)
		{
			linkDistributor->resDistribute->AddResource(_resQue.front());
			_resQue.pop();
			_distributeTime = 0;
		}
	}
}

void ResDistribute::OnTriggerEnter(GameObject* gameObject)
{
	if (gameObject->tag != TAGMANAGER->GetTag("resource"))
		return;

	Item* item = (Item*)gameObject;
	item->SetActive(false);
	_resQue.push(item->GetTargetResource());
}

void ResDistribute::AddResource(int resourceType)
{
	_resQue.push(resourceType);
}

void ResDistribute::Link(PROPDIR dir, Prop* linkProp)
{
	this->linkProp[dir] = linkProp;
}
