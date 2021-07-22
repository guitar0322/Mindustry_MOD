#include "stdafx.h"
#include "Astar.h"
#include "TileInfo.h"
#include <algorithm>

vector<pair<int, int>> Astar::PathFind(int startX, int startY, int endX, int endY)
{
    Clear();
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
            if (curX < 0 || curX == 50 || curY < 0 || curY == 50)
                continue;
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

bool Astar::IsValidNode(NODE node)
{
    return false;
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
