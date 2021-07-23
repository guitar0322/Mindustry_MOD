#pragma once

class PropContainer;
class PropFactory;
class Player;
class EnemyManager;
class GameInfo;
class ResourceManager;
class GameMap;

/*******************************************************************
* 저장해야 할 목록
* 1.현재자원+
* 2.현재건물+
* 3.현재웨이브+
* 4.광석위치+
* 5.맵+
* 6.플레이어위치+
* 7.애너미위치+
* 8.웨이브남은시간+
* 
*******************************************************************/
class DataManager
{
private:
	PropContainer* _propContainer;
	PropFactory* _propFactory;
	Player* _player;
	EnemyManager* _enemyManager;
	GameInfo* _gameInfo;
	ResourceManager* _resourceManager;
	GameMap* _gameMap;
	vector<pair<int,int>> _drillTileVector;
public:
	void SaveData();
	void LoadData();

	void LinkPropContainer(PropContainer* propContainer) { _propContainer = propContainer; }
	void LinkPropFactory(PropFactory* propFactory) { _propFactory = propFactory; }
	void LinkPlayer(Player* player) { _player = player; }
	void LinkEnemeyManager(EnemyManager* enemyManager) { _enemyManager = enemyManager; }
	void LinkGameInfo(GameInfo* gameInfo) { _gameInfo = gameInfo; }
	void LinkResourceManager(ResourceManager* resourceManager) { _resourceManager = resourceManager; }
	void LinkGameMap(GameMap* gameMap) { _gameMap = gameMap; }

	void SavePropData();
	void SaveItemData();
	void SavePlayerData();
	void SaveEnemyData();

	void LoadPropData();
	void LoadItemData();
	void LoadPlayerData();
	void LoadEnemyData();
};

