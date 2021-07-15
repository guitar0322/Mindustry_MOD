#include "stdafx.h"
#include "PropFactory.h"
#include "TileInfo.h"
#include "Prop.h"
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
	_buildTime += TIMEMANAGER->getElapsedTime();
	if (_buildTime >= _propInfoV[_propQueue.front().catagory][_propQueue.front().propIdx].buildTime)
	{
		ELEMPROP buildProp = _propQueue.front();
		switch (buildProp.catagory)
		{
		case TURRET:
			switch (buildProp.propIdx)
			{
			case 0:
				CreateProp<Prop>(buildProp.catagory, buildProp.propIdx);
				break;
			}
			break;
		case PRODUCTION:
			switch (buildProp.propIdx)
			{
			case 0:
				CreateProp<Prop>(buildProp.catagory, buildProp.propIdx);
				break;
			}
			break;
		case RAIL:
			switch (buildProp.propIdx)
			{
			case 0:
				CreateProp<Prop>(buildProp.catagory, buildProp.propIdx);
				break;
			}
			break;
		case DEFENSE:
			switch (buildProp.propIdx)
			{
			case 0:
				CreateProp<Prop>(buildProp.catagory, buildProp.propIdx);
				break;
			}
			break;
		}
	}
}

void PropFactory::Render()
{
}

void PropFactory::Release()
{
}

template<typename T>
ImageObject* PropFactory::CreateProp(int categoryIdx, int propIdx)
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
		newProp.x = mapIter->first % TILENUMX;
		newProp.y = mapIter->first / TILENUMX;
		newProp.catagory = categoryIdx;
		newProp.propIdx = propIdx;
		_propQueue.push(newProp);
	}
}

void PropFactory::InitPropInfo()
{
	_propInfoV[TURRET].push_back({ 0.3f, 1, 10, "duo" , L"듀오"});
	_propInfoV[PRODUCTION].push_back({ 0.1f, 2, 10, "mechanical_drill", L"기계식 드릴" });
	_propInfoV[RAIL].push_back({ 0.1f, 1, 10, "conveyor", L"컨베이어" });
	_propInfoV[DEFENSE].push_back({ 0.3f, 1, 10, "copper_wall" ,L"구리 벽"});
}
