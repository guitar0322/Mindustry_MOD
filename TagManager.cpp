#include "stdafx.h"
#include "TagManager.h"

TagManager::TagManager()
{
	lastIdx = 0;
	AddTag("default");
}

TagManager::~TagManager()
{
}

HRESULT TagManager::init()
{
	AddTag("player");
	AddTag("enemy");
	AddTag("ground");
	AddTag("item");
	return S_OK;
}

void TagManager::release()
{
}
