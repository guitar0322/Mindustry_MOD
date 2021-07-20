#pragma once
#include "singletonBase.h"
#include <map>
#include <vector>

class BoxCollider;

class ColliderManager : public singletonBase<ColliderManager>
{
private:
	vector<BoxCollider*> _colliderV;
	vector<BoxCollider*>::iterator _colliderVIter;
	map<int, vector<BoxCollider*>> _colliderVMap;
	map<int, vector<BoxCollider*>>::iterator _colliderVMapIter;
	float _partitionWidth;
	float _partitionHeight;
	int _partitionNumX;
	int _partitionNumY;
public:
	ColliderManager();
	~ColliderManager();
	HRESULT Init();
	void Release();
	void Render();
	void EraseCollider(BoxCollider* targetCollider);
	void AddCollider(BoxCollider* newCollider);
	void AddCollider(vector<pair<int, int>> partitionIdx, BoxCollider* newCollider);
	int GetColliderNum() { return _colliderV.size(); }
	vector<BoxCollider*> GetColliderVector() { return _colliderV; }
	void PartitionArea(int numX, int numY);
	vector<pair<int,int>> GetIntersectPartition(Rect colliderRc);
	vector<pair<int, int>> ChangeColliderIdx(BoxCollider* collider);
	vector<vector<BoxCollider*>> GetPartitionColliderV(vector<pair<int, int>> partitionIdx);
	/*****************************************************************
	* 충돌체크 최적화, 공간 분할기법
	* 1.백버퍼 크기가 변하면 백버퍼 크기를 x * y 개수의 공간으로 분할한다.
	* 2.박스콜라이더에는 자기자신이 속한 인덱스 벡터(x,y)를 가진다. 최대4개(하나의 사각형은 최대 4개 공간에 겹쳐질수 있기 때문)
	*	4개중 겹친곳이 아닌 인덱스는 -1,-1로 초기화
	* 3.충돌체크 CheckCollision에서 같은 인덱스에 속한 콜라이더만 대상으로 충돌체크한다.
	* 4.ColliderManager에는 GetColliderList(int partitionX, int partitionY)
	* 5.움직였을때 BoxCollider의 CheckColliderPartition() 호출
	* 6.
	******************************************************************/
};

