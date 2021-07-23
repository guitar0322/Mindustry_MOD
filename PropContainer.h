#pragma once
#include <map>
#include "PropInfo.h"
class Prop;
class GameInfo;

class PropContainer
{
private:
	map<int, Prop*> _propMap;
	map<int, Prop*>::iterator _propMapIter;
public:
	GameInfo* gameInfo;
	PropContainer();
	~PropContainer();
	void Init();
	void Release();
	void Update();
	void Render();
	void AddProp(int hashKey, Prop* newProp, PROPDIR dir);
	Prop* GetPropMap(int hashKey);
	void DeleteProp(int tileX, int tileY);
	vector<Prop*> GetAllProp();
};

