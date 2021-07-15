#include "stdafx.h"
#include "PropContainer.h"
#include "Prop.h"
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
	for (_propVectorMapIter = _propVectorMap.begin(); _propVectorMapIter != _propVectorMap.end(); _propVectorMapIter++)
	{
		for (int i = 0; i < _propVectorMapIter->second.size(); i++)
		{
			_propVectorMapIter->second[i]->Update();
		}
	}
}

void PropContainer::Render()
{
	for (_propVectorMapIter = _propVectorMap.begin(); _propVectorMapIter != _propVectorMap.end(); _propVectorMapIter++)
	{
		for (int i = 0; i < _propVectorMapIter->second.size(); i++)
		{
			_propVectorMapIter->second[i]->Render();
		}
	}
}

void PropContainer::LoadTileMap()
{
}

void PropContainer::AddProp(wstring propName, Prop* newProp)
{
	_propVectorMapIter = _propVectorMap.find(propName);
	if (_propVectorMapIter == _propVectorMap.end())
	{
		vector<Prop*> newPropVector;
		newPropVector.push_back(newProp);
		_propVectorMap.insert(pair<wstring, vector<Prop*>>(propName, newPropVector));
	}
	else
	{
		_propVectorMapIter->second.push_back(newProp);
	}
}
