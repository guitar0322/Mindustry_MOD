#include "stdafx.h"
#include "CoreComponent.h"
#include "Item.h"
#include "ResourceManager.h"
#include "GameInfo.h"

void CoreComponent::Init()
{
}

void CoreComponent::OnTriggerEnter(GameObject* gameObject)
{
	if (gameObject->tag == TAGMANAGER->GetTag("resource"))
	{
		Item* resource = (Item*)gameObject;
		_gameInfo->AddResource(resource->GetTargetResource(), 1);
		resource->SetActive(false);
	}
}
