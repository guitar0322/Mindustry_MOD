#pragma once
#define RESOURCE_NUM 2

static enum RESOURCE {
	COPPER,
	LEAD
};

static string resClipName[RESOURCE_NUM] = { "copper", "lead" };

class GameInfo
{
private:
	int _resourceAmount[RESOURCE_NUM];
public:

public:
	void Init();
	int GetResourceAmount(RESOURCE resourceType);
	void AddResource(RESOURCE resourceType, int amount);
	void UseResource(RESOURCE resourceType, int amount);
	bool IsValidResource(RESOURCE resourceType, int needAmount);
	
};

