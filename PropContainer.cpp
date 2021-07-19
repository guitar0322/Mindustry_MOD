#include "stdafx.h"
#include "PropContainer.h"
#include "Prop.h"
#include "Conveyor.h"
#include "Transport.h"
#include "TileInfo.h"
PropContainer::PropContainer()
{
}

PropContainer::~PropContainer()
{
}

void PropContainer::Init()
{
}

void PropContainer::Release()
{
}

void PropContainer::Update()
{
	for (_propMapIter = _propMap.begin(); _propMapIter != _propMap.end(); _propMapIter++)
	{
		_propMapIter->second->Update();
	}
}

void PropContainer::Render()
{
	for (_propMapIter = _propMap.begin(); _propMapIter != _propMap.end(); _propMapIter++)
	{
		_propMapIter->second->Render();
	}
}

void PropContainer::LoadTileMap()
{
}

void PropContainer::AddProp(int hashKey, Prop* newProp)
{
	int tileX = hashKey % TILENUMX;
	int tileY = hashKey / TILENUMX;
	_propMapIter = _propMap.find(hashKey);
	if (_propMapIter == _propMap.end())
	{
		_propMap.insert(pair<int, Prop*>(hashKey, newProp));
	}
	Conveyor* conveyorCast = dynamic_cast<Conveyor*>(newProp);
	if (conveyorCast != nullptr)
	{
		if (_isFirstConveyor == false)
		{
			_isFirstConveyor = true;
			_firstConveyorAnimator = conveyorCast->animator;
		}
		conveyorCast->transport->SetX(tileX);
		conveyorCast->transport->SetY(tileY);
		conveyorCast->animator->SetClip("conveyor_I", _firstConveyorAnimator->GetCurFrameX());
		conveyorCast->animator->SetFrameTime(_firstConveyorAnimator->GetFrameTime());
	}
}
