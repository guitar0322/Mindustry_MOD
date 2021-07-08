#pragma once
#include "singletonBase.h"
#include <map>
#include <vector>
class BoxCollider;

class ColliderManager : public singletonBase<ColliderManager>
{
private:
	map<pair<int,int>, BoxCollider*> _colliderMap;
	map<pair<int,int>, BoxCollider*>::iterator _colliderMapIter;
public:
	vector<BoxCollider*> colliderList;
	ColliderManager();
	~ColliderManager();
	HRESULT Init();
	void Release();
	void EraseCollider(BoxCollider* targetCollider);
	void AddCollider(BoxCollider* newCollider);
	void InsertCollider(BoxCollider* newCollider);
	void RemoveCollider(BoxCollider* targetCollider);
	vector<BoxCollider*> GetAroundCollider(BoxCollider* pivotCollider, int offset);
};

