#include "stdafx.h"
#include "ResourceManager.h"
#include "Item.h"
#include "GameInfo.h"
#include "TileInfo.h"
ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::Init()
{
	for (int i = 0; i < 30; i++)
	{
		Item* testCopper = new Item(COPPER);
		testCopper->transform->SetPosition((1 + i)* TILESIZE + 16, 22 * TILESIZE + 16);
		testCopper->collider->RefreshPartition();
		testCopper->SetLinkPropContainer(propContainer);
		AddResource(testCopper);
	}
}

void ResourceManager::Update()
{
	for (int i = 0; i < _resV.size(); i++) {
		_resV[i]->Update();
	}
}

void ResourceManager::Render()
{
	for (int i = 0; i < _resV.size(); i++) {
		_resV[i]->Render();
	}
}
