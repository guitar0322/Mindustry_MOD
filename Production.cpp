#include "stdafx.h"
#include "Production.h"

pair<int, int> tileDelta[8] = { {-1, -2}, {0, -2}, {1, -1}, {1, 0}, {0, 1}, {-1, 1}, {-2, 0}, {-2, -1} };

void Production::Init()
{
}

void Production::Update()
{

}

void Production::Link(int tileX, int tileY)
{
	int drillPivotX = transform->GetX() / TILESIZE;
	int drillPivotY = transform->GetY() / TILESIZE;

	pair<int, int> deltaTile = { tileX - drillPivotX, tileY - drillPivotY };

	for (int i = 0; i < 8; i++)
	{
		if (tileDelta[i] == deltaTile)
		{
			_linkInfo[i].isConnect = true;
		}
	}


}
