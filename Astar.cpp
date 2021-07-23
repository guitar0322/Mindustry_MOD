#include "stdafx.h"
#include "Astar.h"
#include "TileInfo.h"
#include "EnemyManager.h"
#include "EnemyObject.h"
#include "GameMap.h"
#include "PropContainer.h"
#include "EnemyPlane.h"
vector<pair<int, int>> Astar::PathFind(int startX, int startY, int endX, int endY, GameObject* caller)
{
    Clear();
    _caller = caller;
    _startNode = new NODE();
    _startNode->x = startX;
    _startNode->y = startY;
    _startNode->parentNode = nullptr;
    _endNode = new NODE();
    _endNode->x = endX;
    _endNode->y = endY;
    _endNode->parentNode = nullptr;

    vector<pair<int, int>> result;
    _openList.push_back(_startNode);
    while (_openList.empty() == false)
    {
        NODE *curNode;
        int minIdx = GetMinOpenListNode();
        curNode = _openList[minIdx];
        _openList.erase(_openList.begin() + minIdx);
        if (curNode->x == _endNode->x && curNode->y == _endNode->y)
        {
            while (curNode->parentNode != nullptr)
            {
                result.push_back({ curNode->x, curNode->y });
                curNode = curNode->parentNode;
            }
            return result;
        }

        _closeList.push_back(curNode);
        AddOpenList(curNode);
    }

    return result;
}

void Astar::Clear()
{
    for (int i = 0; i < _openList.size(); i++)
    {
        SAFE_DELETE(_openList[i]);
    }
    for (int i = 0; i < _closeList.size(); i++)
    {
        SAFE_DELETE(_closeList[i]);
    }
    _propIdxV.clear();
    _openList.clear();
    _closeList.clear();
}

void Astar::AddOpenList(NODE* node)
{
    int startX = node->x - 1;
    int startY = node->y - 1;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {

            int curX = startX + i;
            int curY = startY + j;
            if (IsValidNode(curX, curY) == false) continue;
            if (curX < 0 || curX == 50 || curY < 0 || curY == 50) continue;
            if (IsExistCloseList(curX , curY) == true) continue;

            float h = Math::Abs(_endNode->x - curX) + Math::Abs(_endNode->y - curY);
            float g = node->g + CalcG(node->x, node->y, curX, curY);
            float f = h + g;
            int openListIdx = IsExistOpenList(curX, curY);
            if (openListIdx != -1)
            {
                if (_openList[openListIdx]->f > f)
                {
                    _openList[openListIdx]->f = f;
                    _openList[openListIdx]->g = g;
                    _openList[openListIdx]->h = h;
                    _openList[openListIdx]->parentNode = node;
                }
            }
            else
            {
                NODE* newNode = new NODE();
                newNode->x = curX;
                newNode->y = curY;
                newNode->g = g;
                newNode->h = h;
                newNode->f = f;
                newNode->parentNode = node;
                _openList.push_back(newNode);
            }
        }
    }
}

bool Astar::IsExistCloseList(int x, int y)
{
    for (int i = 0; i < _closeList.size(); i++)
    {
        if (_closeList[i]->x == x && _closeList[i]->y == y)
        {
            return true;
        }
    }
    return false;
}

int Astar::IsExistOpenList(int x, int y)
{
    for (int i = 0; i < _openList.size(); i++)
    {
        if (_openList[i]->x == x && _openList[i]->y == y)
        {
            return i;
        }
    }
    return -1;
}

bool Astar::IsValidNode(int x, int y)
{
    vector<EnemyObject*> curWaveEnemy = _enemyManager->GetCurWaveEnemy();
    for (int i = 0; i < curWaveEnemy.size(); i++)
    {
        if (curWaveEnemy[i]->isActive == false) continue;
        if (curWaveEnemy[i] == _caller) continue;
        if (dynamic_cast<EnemyPlane*>(curWaveEnemy[i]) != nullptr) continue;

        Transform* tr = curWaveEnemy[i]->transform;
        BoxCollider* col = curWaveEnemy[i]->GetComponent<BoxCollider>();
        BoxCollider* callerCol = _caller->GetComponent<BoxCollider>();
        Rect colRc = RectMakeCenter(Vector2(tr->position), Vector2(col->GetRc().GetWidth() + callerCol->GetRc().GetWidth(), col->GetRc().GetHeight() + callerCol->GetRc().GetHeight()));
        Vector2 tilePoint = Vector2(x * TILESIZE + 16, y * TILESIZE + 16);
        if (Vector2InRect(&colRc, &tilePoint) == true)
        {
            return false;
        }

    }
    //애너미가 있는곳도 경로에서 제외시켜야한다
    //현재 애너미 웨이브를 받아온다
    //애너미의 충돌 박스가 차지하고 있는 타일들을 구한다.
    //자기자신은 제외시킨다.
    //호출자 포인터를 가지고 있어야한다
    //
    Prop* prop = _propContainer->GetPropMap(y * TILENUMX + x);
    if (prop != nullptr)
    {
        _propIdxV.push_back(prop);
        return false;
    }

    return true;
}

int Astar::GetMinOpenListNode()
{
    int idx = -1;
    float f = 5000;
    for (int i = 0; i < _openList.size(); i++)
    {
        if (f > _openList[i]->f)
        {
            idx = i;
            f = _openList[i]->f;
        }
    }
    return idx;
}

float Astar::CalcG(int startX, int startY, int endX, int endY)
{
    int deltaX = startX - endX;
    int deltaY = startY - endY;
    float result = sqrt(deltaX * deltaX + deltaY * deltaY);
    return result;
}
