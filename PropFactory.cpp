#include "stdafx.h"
#include "PropFactory.h"
#include "TileInfo.h"
#include "CopperWall.h"
#include "Duo.h"
#include "PropContainer.h"
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
	if (_propQueue.empty() == true)
		return;
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
				CreateProp<Duo>(buildProp.x, buildProp.y);
				break;
			}
			break;
		case PRODUCTION:
			switch (buildProp.propIdx)
			{
			case 0:
				CreateProp<Prop>(buildProp.x, buildProp.y);
				break;
			}
			break;
		case RAIL:
			switch (buildProp.propIdx)
			{
			case 0:
				CreateProp<Prop>(buildProp.x, buildProp.y);
				break;
			}
			break;
		case DEFENSE:
			switch (buildProp.propIdx)
			{
			case 0:
				CreateProp<CopperWall>(buildProp.x, buildProp.y);
				break;
			}
			break;
		}
		_buildTime = 0;
	}
}

void PropFactory::Render()
{
}

void PropFactory::Release()
{
}

template<typename T>
ImageObject* PropFactory::CreateProp(int tileX, int tileY)
{
	T* newProp = new T();
	Prop* newPropCast = dynamic_cast<Prop*>(newProp);
	if (newPropCast != nullptr)
	{
		newPropCast->transform->SetPosition(tileX * TILESIZE + TILESIZE / 2, tileY * TILESIZE + TILESIZE / 2);
		propContainer->AddProp(newPropCast->name, newPropCast);
	}
	_propQueue.pop();
	return nullptr;
}

ImageObject* PropFactory::CreatePreview(int tileX, int tileY)
{
	return nullptr;
}

void PropFactory::AddPropElem(queue<int>* propList,int categoryIdx, int propIdx)
{
	int tileX, tileY;
	int size = (*propList).size();
	for (int i = 0; i < size; i++)
	{
		ELEMPROP newProp;
		newProp.x = (*propList).front() % TILENUMX;
		newProp.y = (*propList).front() / TILENUMX;
		newProp.catagory = categoryIdx;
		newProp.propIdx = propIdx;
		_propQueue.push(newProp);
		(*propList).pop();
	}
}

void PropFactory::InitPropInfo()
{
	_propInfoV[TURRET].push_back({ 0.05f, 1, 10, "duo" , L"듀오"});
	_propInfoV[PRODUCTION].push_back({ 0.05f, 2, 10, "mechanical_drill", L"기계식 드릴" });
	_propInfoV[RAIL].push_back({ 0.05f, 1, 10, "conveyor", L"컨베이어" });
	_propInfoV[DEFENSE].push_back({ 0.05f, 1, 10, "copper_wall" ,L"구리 벽"});
}
