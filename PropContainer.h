#pragma once
#include <map>
class Prop;

class PropContainer
{
private:
	map<wstring, vector<Prop*>> _propVectorMap;
	map<wstring, vector<Prop*>>::iterator _propVectorMapIter;
public:
	PropContainer();
	~PropContainer();
	void Init();
	void Release();
	void Update();
	void Render();
	void LoadTileMap();
	void AddProp(wstring propName, Prop* newProp);
};

