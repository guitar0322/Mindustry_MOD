#pragma once
#include <map>
class Prop;
class GameInfo;

class PropContainer
{
private:
	map<int, Prop*> _propMap;
	map<int, Prop*>::iterator _propMapIter;
	Animator* _firstConveyorAnimator;
	bool _isFirstConveyor;
public:
	GameInfo* gameInfo;
	PropContainer();
	~PropContainer();
	void Init();
	void Release();
	void Update();
	void Render();
	void LoadTileMap();
	void AddProp(int hashKey, Prop* newProp);
};

