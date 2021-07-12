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

void ColliderManager::EraseCollider(BoxCollider* targetCollider)
{
	for (int i = 0; i < _colliderV.size(); i++) {
		if (_colliderV[i] == targetCollider) {
			_colliderV.erase(_colliderV.begin() + i);
			break;
		}
	}
}

void ColliderManager::AddCollider(BoxCollider* newCollider)
{
	_colliderV.push_back(newCollider);
}

void ColliderManager::InsertCollider(BoxCollider* newCollider)
{
	int centerX = newCollider->transform->GetX();
	int centerY = newCollider->transform->GetY();
	_colliderMap.insert(pair<BoxCollider*,pair<int, int>>(newCollider, { centerX, centerY }));
}

void ColliderManager::RemoveCollider(BoxCollider* targetCollider)
{
	_colliderMapIter = _colliderMap.find(targetCollider);
	if(_colliderMapIter != _colliderMap.end())
		_colliderMap.erase(_colliderMapIter);
}

vector<BoxCollider*> ColliderManager::GetAroundCollider(BoxCollider* pivotCollider, int offset)
{
	vector<BoxCollider*> result;
	map<BoxCollider* , pair<int, int>>::iterator pivotIter;

	int pivotX = pivotCollider->transform->GetX();
	int pivotY = pivotCollider->transform->GetY();
	_colliderMapIter =
		_colliderMap.find(pivotCollider);

	return result;
}
