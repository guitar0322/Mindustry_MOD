#pragma once
#include <queue>
#include <unordered_map>
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
	ImageObject* CreateProp(int categoryIdx, int propIdx);

	ImageObject* CreatePreview(int tileX, int tileY);
	void AddPropElem(unordered_map<int, ImageObject>* propList, int categoryIdx, int propIdx);
	void InitPropInfo();
};

