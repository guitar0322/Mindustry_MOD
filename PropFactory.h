#pragma once
#include <queue>
#include <map>
#include "PropInfo.h"
class PropContainer;
class GameInfo;

class PropFactory
{
private:
	typedef struct tagPropInfo {
		float buildTime;
		int size;
		int resource;
		int resourceAmount;
		string clipName;
		wstring propName;
	}PROPINFO;

	typedef struct tagQueueProp {
		int x;
		int y;
		int catagory;
		int propIdx;
	}ELEMPROP;
private:
	float _buildTime;
	queue<ELEMPROP> _propQueue;
	vector<ImageObject> _previewV;
	vector<PROPINFO> _propInfoV[CATEGORY_NUM];
	GameInfo* _gameInfo;
public:
	PropFactory();
	~PropFactory();
	PropContainer* propContainer;
	void Init();
	void Update();
	void Render();
	void Release();

	template<typename T>
	ImageObject* CreateProp(int tileX, int tileY);

	ImageObject* CreatePreview(int tileX, int tileY);
	void AddPropElem(vector<ImageObject>& previewV, int categoryIdx, int propIdx);
	void InitPropInfo();
	void LinkGameInfo(GameInfo* gameInfo) { _gameInfo = gameInfo; }
};

