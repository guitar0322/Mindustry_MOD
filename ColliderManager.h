#pragma once
#include "singletonBase.h"
#include <map>
#include <vector>
class BoxCollider;

class ColliderManager : public singletonBase<ColliderManager>
{
private:
	map<BoxCollider*, pair<int, int>> _colliderMap;
	map<BoxCollider*, pair<int, int>>::iterator _colliderMapIter;
	vector<BoxCollider*> _colliderV;
public:
	ColliderManager();
	~ColliderManager();
	HRESULT Init();
	void Release();
	void EraseCollider(BoxCollider* targetCollider);
	void AddCollider(BoxCollider* newCollider);
	void InsertCollider(BoxCollider* newCollider);
	void RemoveCollider(BoxCollider* targetCollider);
	vector<BoxCollider*> GetAroundCollider(BoxCollider* pivotCollider, int offset);
	int GetColliderNum() { return _colliderV.size(); }
	vector<BoxCollider*> GetColliderVector() { return _colliderV; }
};

