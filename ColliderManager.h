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
	* �浹üũ ����ȭ, ���� ���ұ��
	* 1.����� ũ�Ⱑ ���ϸ� ����� ũ�⸦ x * y ������ �������� �����Ѵ�.
	* 2.�ڽ��ݶ��̴����� �ڱ��ڽ��� ���� �ε��� ����(x,y)�� ������. �ִ�4��(�ϳ��� �簢���� �ִ� 4�� ������ �������� �ֱ� ����)
	*	4���� ��ģ���� �ƴ� �ε����� -1,-1�� �ʱ�ȭ
	* 3.�浹üũ CheckCollision���� ���� �ε����� ���� �ݶ��̴��� ������� �浹üũ�Ѵ�.
	* 4.ColliderManager���� GetColliderList(int partitionX, int partitionY)
	* 5.���������� BoxCollider�� CheckColliderPartition() ȣ��
	* 6.
	******************************************************************/
};

