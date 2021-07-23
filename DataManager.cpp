#include "stdafx.h"
#include "DataManager.h"
#include "GameInfo.h"
#include "GameMap.h"
#include "PropContainer.h"
#include "PropFactory.h"
#include "EnemyManager.h"
#include "Player.h"
#include "ResourceManager.h"
#include "Duo.h"
#include "Drill.h"
#include "Conveyor.h"
#include "CopperWall.h"
#include "TileInfo.h"
#include "Item.h"
#include "PlayerControler.h"
#include "EnemyObject.h"
void DataManager::SaveData()
{
	char filename[32] = "resource_data.txt";
	vector<string> resourceData;
	resourceData.push_back(to_string(_gameInfo->GetResourceAmount(COPPER)));
	resourceData.push_back(to_string(_gameInfo->GetResourceAmount(LEAD)));
	resourceData.push_back(to_string(_gameInfo->GetResourceAmount(SCRAP)));

	TXTDATAMANAGER->txtSave(filename, resourceData);

	SavePropData();
	SaveItemData();
	SavePlayerData();
	SaveEnemyData();
}

void DataManager::LoadData()
{
	char resourceFileName[32] = "resource_data.txt";

	int resourceIdx = 0;
	vector<string> resourceData = TXTDATAMANAGER->txtLoad(resourceFileName);
	for (int i = 0; i < resourceData.size(); i++)
	{
		string loadStr = resourceData[i];
		_gameInfo->SetResourceAmount((RESOURCE)resourceIdx, stoi(loadStr));
		resourceIdx++;
	}
	_gameMap->Load();
	LoadPropData();
	LoadItemData();
	LoadPlayerData();
	LoadEnemyData();
}

void DataManager::SavePropData()
{
	char filename[32] = "prop_data.txt";
	vector<string> propData;
	vector<Prop*> propV = _propContainer->GetAllProp();
	for (int i = 0; i < propV.size(); i++)
	{
		int propClass;
		if (dynamic_cast<Duo*>(propV[i]) != nullptr)
		{
			propClass = 0;
		}
		if (dynamic_cast<Drill*>(propV[i]) != nullptr)
		{
			propClass = 1;
		}
		if (dynamic_cast<Conveyor*>(propV[i]) != nullptr)
		{
			propClass = 2;
		}
		if (dynamic_cast<CopperWall*>(propV[i]) != nullptr)
		{
			propClass = 3;
		}

		int tileX = propV[i]->transform->GetX() / TILESIZE;
		int tileY = propV[i]->transform->GetY() / TILESIZE;
		int angle = propV[i]->transform->GetAngle();

		propData.push_back(to_string(propClass));
		propData.push_back(to_string(tileX));
		propData.push_back(to_string(tileY));
		propData.push_back(to_string(angle));
		//°Ç¹° Á¤º¸ 
		//1.°Ç¹°Á¾·ù
		//2.xÁÂÇ¥
		//3.yÁÂÇ¥
		//4.¾Þ±Û
	}
	TXTDATAMANAGER->txtSave(filename, propData);
}

void DataManager::SaveItemData()
{
	char filename[32] = "item_data.txt";
	vector<string> itemData;
	vector<Item*> itemV = _resourceManager->GetAllItem();
	for (int i = 0; i < itemV.size(); i++)
	{
		int targetResource = itemV[i]->GetTargetResource();
		float x = itemV[i]->transform->GetX();
		float y = itemV[i]->transform->GetY();

		itemData.push_back(to_string(targetResource));
		itemData.push_back(to_string(x));
		itemData.push_back(to_string(y));
	}

	TXTDATAMANAGER->txtSave(filename, itemData);
}

void DataManager::SavePlayerData()
{
	char filename[32] = "player_data.txt";
	vector<string> playerData;

	float x = _player->transform->GetX();
	float y = _player->transform->GetY();
	int hp = _player->controler->GetHp();

	playerData.push_back(to_string(x));
	playerData.push_back(to_string(y));
	playerData.push_back(to_string(hp));

	TXTDATAMANAGER->txtSave(filename, playerData);
}

void DataManager::SaveEnemyData()
{
	char filename[32] = "enemy_data.txt";
	vector<string> enemyData;

	enemyData.push_back(to_string(_enemyManager->GetCurWave()));
	enemyData.push_back(to_string(_enemyManager->GetTimeMinute()));
	enemyData.push_back(to_string(_enemyManager->GetTimeSecond()));

	vector<int> wave = _enemyManager->GetWave(_enemyManager->GetCurWave());
	for (int i = 0; i < wave.size(); i++)
	{
		EnemyObject* enemy = _enemyManager->GetEnemy(wave[i]);
		if (enemy->isActive == false) continue;
		int idx = wave[i];
		float x = enemy->transform->GetX();
		float y = enemy->transform->GetY();
		enemyData.push_back(to_string(idx));
		enemyData.push_back(to_string(x));
		enemyData.push_back(to_string(y));
	}

	TXTDATAMANAGER->txtSave(filename, enemyData);
}

void DataManager::LoadPropData()
{
	char filename[32] = "prop_data.txt";

	vector<string> propData = TXTDATAMANAGER->txtLoad(filename);
	for (int i = 0; i < propData.size(); i += 4)
	{
		int propClass = stoi(propData[i]);
		int tileX = stoi(propData[i + 1]);
		int tileY = stoi(propData[i + 2]);
		int angle = stoi(propData[i + 3]);

		switch (propClass)
		{
		case 0:
			_propFactory->CreateTurret(tileX, tileY);
			break;
		case 1:
			_drillTileVector.push_back({ tileX, tileY });
			_propFactory->CreateDrill(tileX, tileY);
			break;
		case 2:
			_propFactory->CreateConveyor(tileX, tileY, (PROPDIR)(angle / 90));
			break;
		case 3:
			_propFactory->CreateProp<CopperWall>(tileX, tileY);
			break;
		}
	}
}

void DataManager::LoadItemData()
{
	char filename[32] = "item_data.txt";

	vector<string> itemData = TXTDATAMANAGER->txtLoad(filename);
	for (int i = 0; i < itemData.size(); i += 3)
	{
		int targetResource = stoi(itemData[i]);
		float x = stof(itemData[i + 1]);
		float y = stof(itemData[i + 2]);
		_resourceManager->AddResource(targetResource, x, y);
	}
}

void DataManager::LoadPlayerData()
{
	char filename[32] = "player_data.txt";
	vector<string> playerData = TXTDATAMANAGER->txtLoad(filename);

	_player->transform->SetPosition(Vector2(stof(playerData[0]), stof(playerData[1])));
	_player->transform->GetChild(3)->SetPosition(Vector2(stof(playerData[0]), stof(playerData[1])));
	_player->controler->SetHp(stoi(playerData[2]));
}

void DataManager::LoadEnemyData()
{
	char filename[32] = "enemy_data.txt";

	vector<string> enemyData = TXTDATAMANAGER->txtLoad(filename);
	_enemyManager->SetCurWave(stoi(enemyData[0]));
	_enemyManager->SetTimeMinute(stoi(enemyData[1]));
	_enemyManager->SetTimeSecond(stoi(enemyData[2]));

	for (int i = 3; i < enemyData.size(); i += 3)
	{
		int idx = stoi(enemyData[i]);
		EnemyObject* enemy = _enemyManager->GetEnemy(idx);
		enemy->transform->SetPosition(stof(enemyData[i + 1]), stof(enemyData[i + 2]));
		enemy->SetActive(true);
	}
}
