#pragma once

class PropContainer;
class PropFactory;
class Player;
class EnemyManager;
class GameInfo;
class ResourceManager;
class GameMap;

/*******************************************************************
* �����ؾ� �� ���
* 1.�����ڿ�+
* 2.����ǹ�+
* 3.������̺�+
* 4.������ġ+
* 5.��+
* 6.�÷��̾���ġ+
* 7.�ֳʹ���ġ+
* 8.���̺곲���ð�+
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

