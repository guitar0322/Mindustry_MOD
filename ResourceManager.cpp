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
		//Item* testCopper = new Item(COPPER);
		//testCopper->transform->SetPosition((1 + i)* TILESIZE + 16, 22 * TILESIZE + 16);
		//testCopper->collider->RefreshPartition();
		//testCopper->SetLinkPropContainer(propContainer);
		//AddResource(testCopper);
	}
}

void ResourceManager::Update()
{
	for (int i = 0; i < _resV.size(); i++) {
		if (_resV[i]->isActive == false)
		{
			NEW_SAFE_RELEASE(_resV[i]);
			SAFE_DELETE(_resV[i]);
			_resV.erase(_resV.begin() + i);
		}
		_resV[i]->Update();
	}
}

void ResourceManager::Render()
{
	for (int i = 0; i < _resV.size(); i++) {
		_resV[i]->Render();
	}
}

void ResourceManager::AddResource(Item* item)
{
	item->SetLinkPropContainer(propContainer);
	wstring name = L"item";
	name.append(to_wstring(_resV.size()));
	item->name = name;
	_resV.push_back(item);
}

void ResourceManager::AddResource(int resource, float x, float y)
{
	Item* newItem = new Item((RESOURCE)resource);
	newItem->Init();
	newItem->transform->SetX(x);
	newItem->transform->SetY(y);
	newItem->collider->RefreshPartition();
	newItem->SetLinkPropContainer(propContainer);
	_resV.push_back(newItem);
}

void ResourceManager::RemoveResource(Item* item)
{
	for (int i = 0; i < _resV.size(); i++)
	{
		if (_resV[i] == item)
		{
			item->SetActive(false);
			NEW_SAFE_RELEASE(item);
			SAFE_DELETE(item);
			_resV.erase(_resV.begin() + i);
		}
	}
}
