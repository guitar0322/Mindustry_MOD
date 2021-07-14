#pragma once
#include <queue>
#include <unordered_map>
#include "PropInfo.h"

class PropFactory
{
private:
	typedef struct tagPropInfo {
		float buildTime;
		int size;
		string clipName;
	}PROPINFO;

	typedef struct tagQueueProp {
		int x;
		int y;
		GameObject* prop;
	}ELEMPROP;
private:
	queue<ELEMPROP> _propQueue;
	vector<PROPINFO> _propInfoV[CATEGORY_NUM];
public:
	PropFactory();
	~PropFactory();
	void Init();
	void Update();
	void Render();
	void Release();
	ImageObject* CreateProp(int tileX, int tileY);
	ImageObject* CreatePreview(int tileX, int tileY);
	void AddPropElem(unordered_map<int, ImageObject>* propList, int categoryIdx, int propIdx);
	void InitPropInfo();
};

