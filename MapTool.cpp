#include "stdafx.h"
#include "MapTool.h"

void MapTool::Init()
{
	SetTileImage();
	Setup();

	for (int i = 0; i < TILESETY; ++i)
	{
		for (int j = 0; j < TILESETX; ++j)
		{
			tileUI[i* TILESETX + j].Init();
			tileUI[i* TILESETX + j].uiRenderer->Init("water");
			tileUI[i* TILESETX + j].transform->SetPosition(WINSIZEX - 40*j -50, 100 + 40*i);
			
		}
		
	}
	tileUI[1].uiRenderer->Init("sand");
	tileName[0] = "water";
	tileName[1] = "sand";
}

void MapTool::Update()
{
	for (int i = 0; i < TILESETY; ++i)
	{
		for (int j = 0; j < TILESETX; ++j)
		{
			tileUI[i* TILESETX + j].Update();
		}
	}

	for (int i = 0; i < TILENUMY; ++i)
	{
		for (int j = 0; j < TILENUMX; ++j)
		{
			_tile[i * TILENUMX + j].Update();
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		for (int i = 0; i < TILESETY; ++i)
		{
			for (int j = 0; j < TILESETX; ++j)
			{
				if (Vector2InRect(&tileUI[i * TILESETX + j].uiRenderer->GetRc(), &_ptMouse))
				{
					selectTile = i * TILESETX + j;
					break;
				}

			}
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		MouseInTile();
	}
}

void MapTool::Render()
{
	for (int i = 0; i < TILESETY; ++i)
	{
		for (int j = 0; j < TILESETX; ++j)
		{
			tileUI[i* TILESETX + j].Render();
		}
	}

	for (int i = 0; i < TILENUMY; ++i)
	{
		for (int j = 0; j < TILENUMX; ++j)
		{
			_tile[i * TILENUMX + j].Render();
		}
	}
}

void MapTool::Setup()
{

	////¸Ê ¼ÂÆÃ
	//for (int i = 0; i < TILEY; ++i)
	//{
	//	for (int j = 0; j < TILEX; ++i)
	//	{
	//		//SetRect(&_tile[i * TILEX + j].rc, j * TILESIZE, i * TILESIZE,
	//		//	j * TILESIZE + TILESIZE, i * TILESIZE + TILESIZE);
	//		tile[i * TILEX + j].rc = RectMakePivot(Vector2(j * TILESIZE, i * TILESIZE),
	//			Vector2(TILESIZE, TILESIZE), Pivot::LeftTop);
	//	}
	//}

	for (int i = 0; i < TILENUMY; ++i)
	{
		for (int j = 0; j < TILENUMX; ++j)
		{
			_tile[i * TILENUMX + j].transform->SetPosition(16 + TILESIZE * j, 16 + TILESIZE * i);
			_tile[i * TILENUMX + j].renderer->Init("water");
		}
	}
}

void MapTool::SetMap()
{

	//for (int i = 0; i < TILESETX * TILESETY; ++i)
	//{
	//	if (Vector2InRect(&_tileSet[i].rcTile, &_ptMouse))
	//	{
	//		_currentTile.x = _tileSet[i].TileX;
	//		_currentTile.y = _tileSet[i].TileY;
	//	}
	//}
	//


}

void MapTool::SetTileImage()
{
	CLIPMANAGER->AddClip("water", "sprites/blocks/environment/water.png", 32, 32);
	CLIPMANAGER->AddClip("sand", "sprites/blocks/environment/sand1.png", 32, 32);


}

bool MapTool::MouseInTile()
{
	for (int i = 0; i < TILENUMY; ++i)
	{
		for (int j = 0; j < TILENUMX; ++j)
		{
			if (_ptMouse.x >= MainCam->GetScreenStart().first && _ptMouse.x <= MainCam->GetScreenStart().first + MainCam->GetScreenWidth())
			{
				float worldX = ScreenToWorld(_ptMouse).x;
				float worldY = ScreenToWorld(_ptMouse).y;

				if (Vector2InRect(&_tile[i * TILENUMX + j].renderer->GetRc(), &Vector2(worldX, worldY)))
				{
					_tile[i * TILENUMX + j].renderer->Init(tileName[selectTile]);
					return true;
				}
			}
		}
	}
	return false;
}
