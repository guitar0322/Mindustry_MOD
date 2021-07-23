#include "stdafx.h"
#include "Production.h"
#include "Transport.h"
#include "Item.h"
#include "ResourceManager.h"
pair<int, int> tileDelta[8] = { {-1, -2}, {0, -2}, {1, -1}, {1, 0}, {0, 1}, {-1, 1}, {-2, 0}, {-2, -1} };
pair<int, int> productPosition[8] = { {-16, -33}, {16, -33}, {33, -16}, {33, 16}, {16, 33}, {-16, 33}, {-33, 16}, {-33,-16} };

void Production::Init()
{
	for (int i = 0; i < 8; i++)
	{
		_linkTransport[i] = nullptr;
	}
	_distributionTime = 0;
	_productTime = 0;
	_resourceTileNum = 0;
	_resourceAmount = 0;
	_transportIdx = 0;
}

void Production::Update()
{
	float elapsTime = TIMEMANAGER->getElapsedTime();
	_distributionTime += TIMEMANAGER->getElapsedTime();
	_productTime += TIMEMANAGER->getElapsedTime();

	if (_distributionTime >= 4.f && _resourceAmount > 0)
	{
		if (_linkTransport[_transportIdx] != nullptr)
		{
			if (_linkTransport[_transportIdx]->GetIsLeck() == false && _linkTransport[_transportIdx]->GetInResource() == nullptr)
			{
				Item* newRes = new Item(_targetResource);
				newRes->Init();
				float posX = transform->GetX() + productPosition[_transportIdx].first;
				float posY = transform->GetY() + productPosition[_transportIdx].second;
				newRes->transform->SetPosition(posX, posY);
				newRes->collider->RefreshPartition();
				_resourceManager->AddResource(newRes);
				_distributionTime = 0;
				_resourceAmount--;
			}
		}
		_transportIdx = (_transportIdx + 1) % 8;
	}

	if (_productTime >= (16.f / (float)_resourceTileNum))
	{
		_resourceAmount++;
		_productTime = 0;
	}
}

void Production::SetTargetResource(RESOURCE resource)
{
	_targetResource = resource;
	_resourceTileNum++;
}

void Production::Link(int tileX, int tileY, Transport* transport)
{
	int drillPivotX = transform->GetX() / TILESIZE;
	int drillPivotY = transform->GetY() / TILESIZE;

	pair<int, int> deltaTile = { tileX - drillPivotX, tileY - drillPivotY };

	for (int i = 0; i < 8; i++)
	{
		if (tileDelta[i] == deltaTile)
		{
			_linkTransport[i] = transport;
			break;
		}
	}
}
