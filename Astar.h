#pragma once

class GameMap;
class EnemyManager;
class PropContainer;
class Prop;

class Astar
{
private:
	typedef struct tagNode {
		int x;
		int y;
		float g;
		float h;
		float f;
		bool isClose;
		tagNode* parentNode;
		bool operator == (tagNode right)
		{
			return (x == right.x && y == right.y);
		}
	}NODE;

private:
	vector<NODE*> _openList;
	vector<NODE*> _closeList;
	vector<Prop*> _propIdxV;
	NODE* _curNode;
	NODE* _endNode;
	NODE* _startNode;
	GameMap* _gameMap;
	EnemyManager* _enemyManager;
	PropContainer* _propContainer;
	GameObject* _caller;
public:
	vector<pair<int, int>> PathFind(int startX, int startY, int endX, int endY, GameObject* caller);
	void Clear();
	void AddOpenList(NODE* node);
	bool IsExistCloseList(int x, int y);
	int IsExistOpenList(int x, int y);
	bool IsValidNode(int x, int y);
	int GetMinOpenListNode();
	vector<Prop*> GetPropIdxV() { return _propIdxV; }
	float CalcG(int startX, int startY, int endX, int endY);
	void LinkGameMap(GameMap* gameMap) { _gameMap = gameMap; }
	void LinkEnemyManager(EnemyManager* enemyManager) { _enemyManager = enemyManager; }
	void LinkPropContainer(PropContainer* propContainer) { _propContainer = propContainer; }
};

