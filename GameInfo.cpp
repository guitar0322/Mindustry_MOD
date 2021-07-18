#include "stdafx.h"
#include "GameInfo.h"

void GameInfo::Init()
{
    for (int i = 0; i < RESOURCE_NUM; i++)
    {
        _resourceAmount[i] = 0;
    }
}

int GameInfo::GetResourceAmount(RESOURCE resourceType)
{
    return _resourceAmount[resourceType];
}

void GameInfo::AddResource(RESOURCE resourceType, int amount)
{
    _resourceAmount[resourceType] += amount;
}

void GameInfo::UseResource(RESOURCE resourceType, int amount)
{
    if (IsValidResource(resourceType, amount) == true)
        _resourceAmount[resourceType] -= amount;
}

bool GameInfo::IsValidResource(RESOURCE resourceType, int needAmount)
{
    return _resourceAmount[resourceType] >= needAmount;
}
