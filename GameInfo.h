#pragma once
#define RESOURCE_NUM 3

/* ��ö(SCRAP) �߰� -�ÿ�- */
static enum RESOURCE {
	COPPER,
	LEAD,
	SCRAP
};

static string resClipName[RESOURCE_NUM] = { "copper", "lead", "scrap" };

class GameInfo
{
private:
	int _resourceAmount[RESOURCE_NUM];
public:

public:
	void Init();
	int GetResourceAmount(RESOURCE resourceType);
	void SetResourceAmount(RESOURCE resourceType, int amount);
	void AddResource(RESOURCE resourceType, int amount);
	void UseResource(RESOURCE resourceType, int amount);
	bool IsValidResource(RESOURCE resourceType, int needAmount);
	
};

