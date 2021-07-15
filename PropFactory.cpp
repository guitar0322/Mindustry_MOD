#include "stdafx.h"
#include "PropFactory.h"
#include "TileInfo.h"
PropFactory::PropFactory()
{
}

PropFactory::~PropFactory()
{
}

void PropFactory::Init()
{
	InitPropInfo();
}

void PropFactory::Update()
{
}

void PropFactory::Render()
{
}

void PropFactory::Release()
{
}

ImageObject* PropFactory::CreateProp(int tileX, int tileY)
{
	return nullptr;
}

ImageObject* PropFactory::CreatePreview(int tileX, int tileY)
{
	return nullptr;
}

void PropFactory::AddPropElem(unordered_map<int, ImageObject>* propList,int categoryIdx, int propIdx)
{
	int tileX, tileY;
	unordered_map<int, ImageObject>::iterator mapIter;
	for (mapIter = (*propList).begin(); mapIter != (*propList).end(); mapIter++)
	{
		ELEMPROP newProp;
		tileX = mapIter->first % TILENUMX;
		tileY = mapIter->first / TILENUMX;
	}
}

void PropFactory::InitPropInfo()
{
	_propInfoV[TURRET].push_back({ 0.3f, 1, 10, "duo" });
	_propInfoV[PRODUCTION].push_back({ 0.1f, 2, 10, "mechanical_drill" });
	_propInfoV[RAIL].push_back({ 0.1f, 1, 10, "conveyor" });
	_propInfoV[DEFENSE].push_back({ 0.3f, 1, 10, "copper_wall" });
}
