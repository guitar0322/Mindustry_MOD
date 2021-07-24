#include "stdafx.h"
#include "PropContainer.h"
#include "Prop.h"
#include "Conveyor.h"
#include "Transport.h"
#include "TileInfo.h"
#include "Drill.h"
#include "Production.h"
#include "Distributor.h"
#include "ResDistribute.h"
#include "Duo.h"
int conveyorDir[4][2] = { {1,0}, {0,1}, {-1,0}, {0,-1} };

PropContainer::PropContainer()
{
}

PropContainer::~PropContainer()
{
}

void PropContainer::Init()
{
	SOUNDMANAGER->addSound("complete", "sounds/place.ogg", true, false);
	SOUNDMANAGER->addSound("delete", "sounds/pew.ogg", true, false);
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

void PropContainer::AddProp(int hashKey, Prop* newProp, PROPDIR dir)
{
	SOUNDMANAGER->play("complete", 10.0f);
	int tileX = hashKey % TILENUMX;
	int tileY = hashKey / TILENUMX;
	_propMapIter = _propMap.find(hashKey);
	if (_propMapIter == _propMap.end())
	{
		_propMap.insert(pair<int, Prop*>(hashKey, newProp));
	}
	Duo* duoCast = dynamic_cast<Duo*>(newProp);
	if (duoCast != nullptr)
	{
		for (int i = 0; i < 4; i++)
		{
			int nextX = tileX + conveyorDir[i][0];
			int nextY = tileY + conveyorDir[i][1];
			int nextHashKey = nextY * TILENUMX + nextX;
			Prop* prop = GetPropMap(nextHashKey);
			Distributor* nearDistributor = dynamic_cast<Distributor*>(prop);
			if (nearDistributor != nullptr)
			{
				nearDistributor->resDistribute->Link(PROPDIR((i + 2) % 4), duoCast);
			}
		}
	}
	Conveyor* conveyorCast = dynamic_cast<Conveyor*>(newProp);
	if (conveyorCast != nullptr)
	{
		for (int i = 0; i < 4; i++)
		{
			int nextX = tileX + conveyorDir[i][0];
			int nextY = tileY + conveyorDir[i][1];
			int nextHashKey = nextY * TILENUMX + nextX;
			Prop* prop = GetPropMap(nextHashKey);
			Conveyor* nearConveyor = dynamic_cast<Conveyor*>(prop);
			Drill* nearDrill = dynamic_cast<Drill*>(prop);
			Distributor* nearDistributor = dynamic_cast<Distributor*>(prop);
			if (nearConveyor != nullptr)
			{
				if (i == conveyorCast->transport->GetOutDir())
				{
					//(i + 2) % 4 = 반대방향
					nearConveyor->transport->LinkConveyor(PROPDIR((i + 2) % 4));
				}
				else if (nearConveyor->transport->GetOutDir() == (i + 2) % 4)
				{
					conveyorCast->transport->LinkConveyor(PROPDIR(i));
				}
			}
			if (nearDrill != nullptr)
			{
				conveyorCast->transport->LinkConveyor(PROPDIR(i));
				nearDrill->production->Link(tileX, tileY, conveyorCast->transport);
			}
			if (nearDistributor != nullptr && i != conveyorCast->transport->GetOutDir())
			{
				conveyorCast->transport->LinkConveyor(PROPDIR(i));
				nearDistributor->resDistribute->Link(PROPDIR((i + 2) % 4), conveyorCast);
			}
		}
	}

	Drill* drillCast = dynamic_cast<Drill*>(newProp);
	if (drillCast != nullptr)
	{
		for (int i = 0; i < 4; i++)
		{
			int nextX = tileX + conveyorDir[i][0];
			int nextY = tileY + conveyorDir[i][1];
			int nextHashKey = nextY * TILENUMX + nextX;
			Prop* prop = GetPropMap(nextHashKey);
			Conveyor* nearConveyor = dynamic_cast<Conveyor*>(prop);
			if (nearConveyor != nullptr)
			{
				nearConveyor->transport->LinkConveyor(PROPDIR((i + 2) % 4));
				drillCast->production->Link(nextX, nextY, nearConveyor->transport);
			}
		}
	}

	Distributor* distributorCast = dynamic_cast<Distributor*>(newProp);
	if (distributorCast != nullptr)
	{
		distributorCast->resDistribute->LinkResourceManager(_resourceManager);
		for (int i = 0; i < 4; i++)
		{
			int nextX = tileX + conveyorDir[i][0];
			int nextY = tileY + conveyorDir[i][1];
			int nextHashKey = nextY * TILENUMX + nextX;
			Prop* prop = GetPropMap(nextHashKey);
			Conveyor* nearConveyor = dynamic_cast<Conveyor*>(prop);
			Duo* nearDuo = dynamic_cast<Duo*>(prop);
			Distributor* nearDistributor = dynamic_cast<Distributor*>(prop);
			if (nearConveyor != nullptr)
			{
				if (nearConveyor->transport->GetOutDir() != (i + 2) % 4)
				{
					nearConveyor->transport->LinkConveyor(PROPDIR((i + 2) % 4));
					distributorCast->resDistribute->Link(PROPDIR(i), nearConveyor);
				}
			}
			if (nearDuo != nullptr)
			{
				distributorCast->resDistribute->Link(PROPDIR(i), nearDuo);
			}
			if (nearDistributor != nullptr)
			{
				nearDistributor->resDistribute->Link(PROPDIR((i + 2) % 4), distributorCast);
			}
		}
	}
}

Prop* PropContainer::GetPropMap(int hashKey)
{
	_propMapIter = _propMap.find(hashKey);
	if (_propMapIter != _propMap.end())
		return _propMapIter->second;

	return nullptr;
}

void PropContainer::DeleteProp(int tileX, int tileY)
{
	Prop* targetProp = GetPropMap(tileY * TILENUMX + tileX);
	if (targetProp != nullptr)
	{
		SOUNDMANAGER->play("delete", 10.0f);
		_propMap.erase(tileY * TILENUMX + tileX);
		SAFE_DELETE(targetProp);
	}
}

vector<Prop*> PropContainer::GetAllProp()
{
	vector<Prop*> result;
	for (_propMapIter = _propMap.begin(); _propMapIter != _propMap.end(); _propMapIter++)
	{
		result.push_back(_propMapIter->second);
	}
	return result;
}
