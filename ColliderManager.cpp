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
	colliderList.clear();
}

void ColliderManager::EraseCollider(BoxCollider* targetCollider)
{
	for (int i = 0; i < colliderList.size(); i++) {
		if (colliderList[i] == targetCollider) {
			colliderList.erase(colliderList.begin() + i);
			break;
		}
	}
}

void ColliderManager::AddCollider(BoxCollider* newCollider)
{
	colliderList.push_back(newCollider);
}

void ColliderManager::InsertCollider(BoxCollider* newCollider)
{
	int centerX = newCollider->transform->GetX();
	int centerY = newCollider->transform->GetY();
	_colliderMap.insert(pair<pair<int, int>, BoxCollider*>({ centerX, centerY }, newCollider));
}

void ColliderManager::RemoveCollider(BoxCollider* targetCollider)
{
	int centerX = targetCollider->transform->GetX();
	int centerY = targetCollider->transform->GetY();
	_colliderMapIter = _colliderMap.find({ centerX, centerY });
	if(_colliderMapIter != _colliderMap.end())
		_colliderMap.erase(_colliderMapIter);
}

vector<BoxCollider*> ColliderManager::GetAroundCollider(BoxCollider* pivotCollider, int offset)
{
	vector<BoxCollider*> result;
	int left = (int)pivotCollider->GetRc().left;
	int top = (int)pivotCollider->GetRc().top;
	int right = (int)pivotCollider->GetRc().right;
	int bottom = (int)pivotCollider->GetRc().bottom;

	for (int i = left - offset; i < right + offset; i++)
	{
		for (int j = top - offset; j < bottom + offset; j++)
		{
			_colliderMapIter = _colliderMap.find({ i,j });
			if (_colliderMapIter != _colliderMap.end())
			{
				result.push_back(_colliderMapIter->second);
			}
		}
	}
	return result;
}
