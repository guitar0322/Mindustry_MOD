#pragma once
#include <queue>
#include <map>
#include "PropInfo.h"
class PropContainer;
class PropFactory
{
private:
	typedef struct tagPropInfo {
		float buildTime;
		int size;
		int resources;
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
	vector<PROPINFO> _propInfoV[CATEGORY_NUM];
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
	void AddPropElem(queue<int>* propList, int categoryIdx, int propIdx);
	void InitPropInfo();
};

