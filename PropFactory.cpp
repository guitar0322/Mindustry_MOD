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
#include "EnemyManager.h"
#include "GameMap.h"
#include "Production.h"
#include "Turret.h"
#include "ProjectileManager.h"
#include "PlayerControler.h"
#include "Distributor.h"
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
	Building();
	Delete();
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
		newPropCast->GetComponent<BoxCollider>()->CheckCollision();
	}
	ContainProp(tileY * TILENUMX + tileX, newPropCast, PROPDIR(0));
	return nullptr;
}

void PropFactory::Building()
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
	if (_gameInfo->IsValidResource((RESOURCE)_propInfoV[_propQueue.front().catagory][_propQueue.front().propIdx].resource,
		_propInfoV[_propQueue.front().catagory][_propQueue.front().propIdx].resourceAmount) == false)
		return;

	/*********************************************************
	* �Ǽ� ���൵�� ���� �̸����� ���İ� ���ϰ� �ϱ�
	* 1.buildTime�� ���� ���� �Ǽ� ���� �����(percent, 1.f�� �ִ�)�� ���Ѵ�.
	* 2.percent = _buildTime / �ִ� �Ǽ��ð� / 100
	* 3.setalpha(�ʱ���İ� + (1.f - �ʱ���İ�) * percent)
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
				CreateTurret(buildProp.x, buildProp.y);
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
			case 1:
				CreateProp<Distributor>(buildProp.x, buildProp.y);
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

void PropFactory::Delete()
{
	if (_deleteQueue.empty() == true)
	{
		isDelete = false;
		return;
	}
	else {
		isDelete = true;
	}

	_deleteTime += TIMEMANAGER->getElapsedTime();
	if (_deleteTime >= 0.2f)
	{
		propContainer->DeleteProp(_deleteQueue.front().x, _deleteQueue.front().y);
		_deleteQueue.pop();
		if (_deleteQueue.empty() == false)
		{
			_playerControler->SetConstructLaser(_deleteQueue.front().x, _deleteQueue.front().y, _deleteQueue.front().isDrill ? 2 : 1);
		}
		_deleteTime = 0;
	}
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
	if (isBuilding == true)
	{
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
}

void PropFactory::CreateTurret(int tileX, int tileY)
{
	Duo* newDuo = new Duo();
	newDuo->transform->SetPosition(tileX * TILESIZE + 16, tileY * TILESIZE + 16);
	newDuo->base->transform->SetPosition(tileX * TILESIZE + 16, tileY * TILESIZE + 16);
	newDuo->collider->RefreshPartition();
	newDuo->turret->LinkProjectileManager(_projectileManager);
	newDuo->turret->LinkEnemyManager(_enemyManager);
	ContainProp(tileY * TILENUMX + tileX, newDuo, RIGHT);
}

void PropFactory::ContainProp(int hashKey, Prop* newProp, PROPDIR dir)
{
	propContainer->AddProp(hashKey, newProp, dir);
	if (isBuilding == true)
	{
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
}

void PropFactory::LoadConveyor(int tileX, int tileY, PROPDIR dir)
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
	newConveyor->transport->SetX(tileX);
	newConveyor->transport->SetY(tileY);
	newConveyor->transport->SetOutDir(dir);
	newConveyor->transport->SetShape(0);
	newConveyor->transport->SetFirstAnimator(_firstConveyorAnimator);
	newConveyor->animator->SetClip("conveyor_I", _firstConveyorAnimator->GetCurFrameX());
	newConveyor->animator->SetFrameTime(_firstConveyorAnimator->GetFrameTime());
	propContainer->AddProp(tileY * TILENUMX + tileX, newConveyor, dir);
}

void PropFactory::LoadDrill(int tileX, int tileY)
{
}

void PropFactory::LoadTurret(int tileX, int tileY)
{
}

void PropFactory::LoadCopperWall(int tileX, int tileY)
{
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

void PropFactory::AddDeleteQue(int startX, int startY, int endX, int endY)
{
	for (int i = startY; i < endY + 1; i++)
	{
		for (int j = startX; j < endX + 1; j++)
		{
			Prop* deleteProp = propContainer->GetPropMap(i * TILENUMX + j);
			bool isDrill;
			if (dynamic_cast<Drill*>(deleteProp) != nullptr)
				isDrill = true;
			else
				isDrill = false;
			if (deleteProp != nullptr)
			{
				_deleteQueue.push({ j, i , isDrill });
			}
		}
	}
	if(_deleteQueue.empty() == false)
		_playerControler->SetConstructLaser(_deleteQueue.front().x, _deleteQueue.front().y, _deleteQueue.front().isDrill ? 2 : 1);
}

void PropFactory::InitPropInfo()
{
	_propInfoV[TURRET].push_back({ 0.15f, 1, 0, 10, "duo" , L"���"});
	_propInfoV[PRODUCTION].push_back({ 1.f, 2, 0, 10, "mechanical_drill", L"���� �帱" });
	_propInfoV[RAIL].push_back({ 0.15f, 1, 0, 10, "conveyor", L"�����̾�" });
	_propInfoV[RAIL].push_back({ 0.15f, 1, 0, 10, "distributor", L"�й��" });
	_propInfoV[DEFENSE].push_back({ 0.1f, 1, 0, 1, "copper_wall" ,L"���� ��"});
}
