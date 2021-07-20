#include "stdafx.h"
#include "ColliderManager.h"
#include "BoxCollider.h"
ColliderManager::ColliderManager()
{
}

ColliderManager::~ColliderManager()
{
}

HRESULT ColliderManager::Init()
{
	return S_OK;
}

void ColliderManager::Release()
{
	_colliderV.clear();
}

void ColliderManager::Render()
{
	for (int i = 0; i < _partitionNumX; i++)
	{
		D2DRENDERER->DrawLineBack(Vector2(_partitionWidth * i, 0.f), Vector2(_partitionWidth * i, _partitionHeight * _partitionNumY), D2D1::ColorF::Green, 1.f);
	}
	for (int i = 0; i < _partitionNumY; i++)
	{
		D2DRENDERER->DrawLineBack(Vector2(0.f, _partitionHeight * i), Vector2(_partitionWidth * _partitionNumX, _partitionHeight * i), D2D1::ColorF::Green, 1.f);
	}
}

void ColliderManager::EraseCollider(BoxCollider* targetCollider)
{
	vector<pair<int, int>> partitionIdx = targetCollider->GetPartitionIdx();
	for (int i = 0; i < partitionIdx.size(); i++)
	{
		_colliderVMapIter = _colliderVMap.find(partitionIdx[i].second * _partitionNumX + partitionIdx[i].first);
		if (_colliderVMapIter == _colliderVMap.end())
			throw "collider manager error";
		for (int j = 0; j < _colliderVMapIter->second.size(); j++)
		{
			if (_colliderVMapIter->second[j] == targetCollider)
			{
				_colliderVMapIter->second.erase(_colliderVMapIter->second.begin() + j);
			}
		}
	}
}

void ColliderManager::AddCollider(BoxCollider* newCollider)
{
	vector<pair<int, int>> partitionIdx = newCollider->GetPartitionIdx();
	for (int i = 0; i < partitionIdx.size(); i++)
	{
		_colliderVMapIter = _colliderVMap.find(partitionIdx[i].second * _partitionNumX + partitionIdx[i].first);
		_colliderVMapIter->second.push_back(newCollider);
	}
	return;
}

void ColliderManager::AddCollider(vector<pair<int, int>> partitionIdx, BoxCollider* newCollider)
{
	for (int i = 0; i < partitionIdx.size(); i++)
	{
		_colliderVMapIter = _colliderVMap.find(partitionIdx[i].second * _partitionNumX + partitionIdx[i].first);
		_colliderVMapIter->second.push_back(newCollider);
	}
	return;
}

void ColliderManager::PartitionArea(int numX, int numY)
{
	_partitionWidth = MAPWIDTH / numX;
	_partitionHeight = MAPHEIGHT / numY;
	_partitionNumX = numX;
	_partitionNumY = numY;
	_colliderVMap.clear();

	for (int i = 0; i < _partitionNumX; i++)
	{
		for (int j = 0; j < _partitionNumY; j++)
		{
			_colliderVMap.insert(pair<int, vector<BoxCollider*>>(i * numX + j, vector<BoxCollider*>()));
		}
	}
}

vector<pair<int, int>> ColliderManager::GetIntersectPartition(Rect colliderRc)
{
	vector<pair<int, int>> result;

	int leftIdx = colliderRc.left / (MAPWIDTH / _partitionNumX);
	int topIdx = colliderRc.top / (MAPHEIGHT / _partitionNumY);
	int rightIdx = colliderRc.right / (MAPWIDTH / _partitionNumX);
	int bottomIdx = colliderRc.bottom / (MAPHEIGHT / _partitionNumY);

	if (leftIdx	< 0) 
		leftIdx	= 0;
	if (leftIdx	> _partitionNumX - 1) 
		leftIdx = _partitionNumX - 1;

	if (topIdx < 0) 
		topIdx = 0;
	if (topIdx > _partitionNumY - 1) 
		topIdx = _partitionNumY - 1;

	if (rightIdx < 0) 
		rightIdx = 0;
	if (rightIdx > _partitionNumX - 1) 
		rightIdx = _partitionNumX - 1;

	if (bottomIdx < 0)
		bottomIdx = 0;
	if (bottomIdx > _partitionNumY - 1)
		bottomIdx = _partitionNumY - 1;

	result.push_back({ leftIdx, topIdx });
	if (leftIdx != rightIdx && topIdx != bottomIdx)
	{
		result.push_back({ rightIdx, bottomIdx });
	}
	if (topIdx != bottomIdx)
	{
		result.push_back({ leftIdx, bottomIdx });
	}
	if (leftIdx != rightIdx)
	{
		result.push_back({ rightIdx, topIdx });
	}

	return result;
}

vector<pair<int, int>> ColliderManager::ChangeColliderIdx(BoxCollider* collider)
{
	vector<pair<int, int>> preIdx = collider->GetPartitionIdx();
	vector<pair<int, int>> curIdx = GetIntersectPartition(collider->GetRc());

	if (preIdx.size() != curIdx.size())
	{
		EraseCollider(collider);
		AddCollider(curIdx, collider);
	}
	else
	{
		for (int i = 0; i < preIdx.size(); i++)
		{
			if (preIdx[i] != curIdx[i])
			{
				EraseCollider(collider);
				AddCollider(curIdx, collider);
				break;
			}
		}
	}
	return curIdx;
}

vector<vector<BoxCollider*>> ColliderManager::GetPartitionColliderV(vector<pair<int, int>> partitionIdx)
{
	vector<vector<BoxCollider*>> result;
	for (int i = 0; i < partitionIdx.size(); i++)
	{
		_colliderVMapIter = _colliderVMap.find(partitionIdx[i].second * _partitionNumX + partitionIdx[i].first);
		result.push_back(_colliderVMapIter->second);
	}
	return result;
}
