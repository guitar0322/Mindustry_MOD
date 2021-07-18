#include "stdafx.h"
#include "PropFactory.h"
#include "TileInfo.h"
#include "CopperWall.h"
#include "Duo.h"
#include "Conveyor.h"
#include "PropContainer.h"
#include "GameInfo.h"

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
				CreateProp<Prop>(buildProp.x, buildProp.y);
				break;
			}
			break;
		case RAIL:
			switch (buildProp.propIdx)
			{
			case 0:
				CreateProp<Conveyor>(buildProp.x, buildProp.y);
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
		propContainer->AddProp(tileY * TILENUMX + tileX, newPropCast);
	}
	_previewV.erase(_previewV.begin());
	_propQueue.pop();
	return nullptr;
}

ImageObject* PropFactory::CreatePreview(int tileX, int tileY)
{
	return nullptr;
}

void PropFactory::AddPropElem(vector<ImageObject>& previewV,int categoryIdx, int propIdx)
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
		_propQueue.push(newProp);
		_previewV.push_back(previewV[i]);
	}
}

void PropFactory::InitPropInfo()
{
	_propInfoV[TURRET].push_back({ 0.05f, 1, 0, 10, "duo" , L"듀오"});
	_propInfoV[PRODUCTION].push_back({ 0.05f, 2, 0, 10, "mechanical_drill", L"기계식 드릴" });
	_propInfoV[RAIL].push_back({ 0.05f, 1, 0, 10, "conveyor", L"컨베이어" });
	_propInfoV[DEFENSE].push_back({ 1.f, 1, 0, 35, "copper_wall" ,L"구리 벽"});
}
