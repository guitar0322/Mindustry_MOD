#pragma once

class GameMap;

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
	NODE* _curNode;
	NODE* _endNode;
	NODE* _startNode;
	GameMap* _gameMap;
public:
	vector<pair<int, int>> PathFind(int startX, int startY, int endX, int endY);
	void Clear();
	void AddOpenList(NODE* node);
	bool IsExistCloseList(int x, int y);
	int IsExistOpenList(int x, int y);
	bool IsValidNode(NODE node);
	int GetMinOpenListNode();
	float CalcG(int startX, int startY, int endX, int endY);
	void LinkGameMap(GameMap* gameMap) { _gameMap = gameMap; }
};

