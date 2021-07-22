#include "stdafx.h"
#include "PropFactory.h"
#include "TileInfo.h"
#include "CopperWall.h"
#include "Duo.h"
#include "Conveyor.h"
#include "Transport.h"
#include "PropContainer.h"
#include "GameInfo.h"
#include "Prop.h"
#include "Drill.h"
#include "GameMap.h"
#include "Production.h"
#include "PlayerControler.h"

PropFactory::PropFactory()
{
}

PropFactory::~PropFactory()
{
}

void PropFactory::Init()
{
	InitPropInfo();
	isProduction = false;
}

void PropFactory::Update()
{
	while (_previewV.empty() == false && Math::FloatEqual(_previewV[0].renderer->GetAlpha(), 0.4f) == true)
	{
		_previewV.erase(_previewV.begin());
		_propQueue.pop();
	}
	if (_propQueue.empty() == true)
	{
		isBuilding = false;
		return;
	}
	else {
		isBuilding = true;
	}
	if(_gameInfo->IsValidResource((RESOURCE)_propInfoV[_propQueue.front().catagory][_propQueue.front().propIdx].resource, 
		_propInfoV[_propQueue.front().catagory][_propQueue.front().propIdx].resourceAmount) == false)
		return;

	/*********************************************************
	* 건설 진행도에 따라 미리보기 알파값 진하게 하기
	* 1.buildTime을 통해 현재 건설 진행 백분율(percent, 1.f이 최대)을 구한다.
	* 2.percent = _buildTime / 최대 건설시간 / 100
	* 3.setalpha(초기알파값 + (1.f - 초기알파값) * percent)
	*********************************************************/
	_buildTime += TIMEMANAGER->getElapsedTime();
	
	float percent = _buildTime / _propInfoV[_propQueue.front().catagory][_propQueue.front().propIdx].buildTime;
	_previewV[0].renderer->SetAlpha(0.5f + (0.5f) * percent);

	//플레이어컨트롤로 좌표 받아오기	



	if (_buildTime >= _propInfoV[_propQueue.front().catagory][_propQueue.front().propIdx].buildTime)
	{
		_gameInfo->UseResource((RESOURCE)_propInfoV[_propQueue.front().catagory][_propQueue.front().propIdx].resource,
			_propInfoV[_propQueue.front().catagory][_propQueue.front().propIdx].resourceAmount);

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
				CreateDrill(buildProp.x, buildProp.y);
				break;
			}
			break;
		case RAIL:
			switch (buildProp.propIdx)
			{
			case 0:
				CreateConveyor(buildProp.x, buildProp.y, buildProp.dir);
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
	for (int i = 0; i < _previewV.size(); i++)
	{
		_previewV[i].Update();
	}
}

void PropFactory::Render()
{
	for (int i = 0; i < _previewV.size(); i++)
	{
		_previewV[i].Render();
	}
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
		newPropCast->GetComponent<BoxCollider>()->RefreshPartition();
	}
	ContainProp(tileY * TILENUMX + tileX, newPropCast, PROPDIR(0));
	return nullptr;
}

void PropFactory::CreateConveyor(int tileX, int tileY, PROPDIR dir)
{
	Conveyor* newConveyor = new Conveyor();
	if (_isFirstConveyor == false)
	{
		_isFirstConveyor = true;
		_firstConveyorAnimator = newConveyor->animator;
	}
	newConveyor->transform->SetPosition(tileX * TILESIZE + TILESIZE / 2, tileY * TILESIZE + TILESIZE / 2);
	newConveyor->transform->SetAngle(dir * 90);
	newConveyor->collider->RefreshPartition();
	newConveyor->collider->CheckCollision();
	newConveyor->transport->SetX(tileX);
	newConveyor->transport->SetY(tileY);
	newConveyor->transport->SetOutDir(dir);
	newConveyor->transport->SetShape(0);
	newConveyor->transport->SetFirstAnimator(_firstConveyorAnimator);
	newConveyor->animator->SetClip("conveyor_I", _firstConveyorAnimator->GetCurFrameX());
	newConveyor->animator->SetFrameTime(_firstConveyorAnimator->GetFrameTime());
	ContainProp(tileY * TILENUMX + tileX, newConveyor, dir);
}

void PropFactory::CreateDrill(int tileX, int tileY)
{
	Drill* newDrill = new Drill();
	newDrill->transform->SetPosition(tileX * TILESIZE, tileY * TILESIZE);
	newDrill->collider->RefreshPartition();
	newDrill->rotator->transform->SetPosition(tileX * TILESIZE, tileY * TILESIZE);
	newDrill->top->transform->SetPosition(tileX * TILESIZE, tileY * TILESIZE);
	newDrill->production->LinkResourceManager(_resourceManager);
	vector<int> drillTileV;
	drillTileV.push_back(tileY * TILENUMX + tileX);
	drillTileV.push_back((tileY-1) * TILENUMX + tileX);
	drillTileV.push_back(tileY * TILENUMX + tileX - 1);
	drillTileV.push_back((tileY - 1) * TILENUMX + tileX - 1);
	for (int i = 0; i < 4; i++)
	{
		tagTile tileInfo = _gameMap->GetTileInfo(drillTileV[i]);
		if (tileInfo.resources >= RES_COPPER1 && tileInfo.resources <= RES_COPPER3)
			newDrill->production->SetTargetResource(COPPER);
		else if(tileInfo.resources >= RES_LEAD1 && tileInfo.resources <= RES_LEAD3)
			newDrill->production->SetTargetResource(LEAD);
		propContainer->AddProp(drillTileV[i], newDrill, RIGHT);
	}
	_previewV.erase(_previewV.begin());
	_propQueue.pop();
	if (_propQueue.empty() == false)
	{
		if (_propQueue.front().catagory == PRODUCTION)
		{
			_playerControler->SetConstructLaser(_propQueue.front().x, _propQueue.front().y, 2);
		}
		else
		{
			_playerControler->SetConstructLaser(_propQueue.front().x, _propQueue.front().y, 1);
		}
	}
}

void PropFactory::ContainProp(int hashKey, Prop* newProp, PROPDIR dir)
{
	propContainer->AddProp(hashKey, newProp, dir);
	_previewV.erase(_previewV.begin());
	_propQueue.pop();
	if (_propQueue.empty() == false)
	{
		if (_propQueue.front().catagory == PRODUCTION)
		{
			_playerControler->SetConstructLaser(_propQueue.front().x, _propQueue.front().y, 2);
		}
		else
		{
			_playerControler->SetConstructLaser(_propQueue.front().x, _propQueue.front().y, 1);
		}
	}
}

ImageObject* PropFactory::CreatePreview(int tileX, int tileY)
{
	return nullptr;
}

void PropFactory::AddPropElem(vector<ImageObject>& previewV,int categoryIdx, int propIdx, PROPDIR dir)
{
	int tileX, tileY;
	int size = previewV.size();
	for (int i = 0; i < size; i++)
	{
		ELEMPROP newProp;
		newProp.x = (previewV[i].transform->GetX() / TILESIZE);
		newProp.y = (previewV[i].transform->GetY() / TILESIZE);
		newProp.catagory = categoryIdx;
		newProp.propIdx = propIdx;
		newProp.dir = dir;
		_propQueue.push(newProp);
		_previewV.push_back(previewV[i]);
	}
	if (_propQueue.front().catagory == PRODUCTION)
	{
		_playerControler->SetConstructLaser(_propQueue.front().x, _propQueue.front().y, 2);
	}
	else
	{
		_playerControler->SetConstructLaser(_propQueue.front().x, _propQueue.front().y, 1);
	}
}

void PropFactory::InitPropInfo()
{
	_propInfoV[TURRET].push_back({ 0.05f, 1, 0, 10, "duo" , L"듀오"});
	_propInfoV[PRODUCTION].push_back({ 0.5f, 2, 0, 10, "mechanical_drill", L"기계식 드릴" });
	_propInfoV[RAIL].push_back({ 0.05f, 1, 0, 10, "conveyor", L"컨베이어" });
	_propInfoV[DEFENSE].push_back({ 1.f, 1, 0, 35, "copper_wall" ,L"구리 벽"});
}
