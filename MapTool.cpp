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
			
			SetTileName(i* TILESETX + j);
		}
	}
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

	////맵 셋팅
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
	/*======환경======*/
	//물
	CLIPMANAGER->AddClip("water", "sprites/blocks/environment/water.png", 32, 32);
	CLIPMANAGER->AddClip("deep_water", "sprites/blocks/environment/deepwater.png", 32, 32);
	//모래
	CLIPMANAGER->AddClip("sand1", "sprites/blocks/environment/sand1.png", 32, 32);
	CLIPMANAGER->AddClip("sand2", "sprites/blocks/environment/sand2.png", 32, 32);
	CLIPMANAGER->AddClip("sand3", "sprites/blocks/environment/sand3.png", 32, 32);
	CLIPMANAGER->AddClip("darksand_water", "sprites/blocks/environment/darksand-water.png", 32, 32);

	//흙
	CLIPMANAGER->AddClip("dirt1", "sprites/blocks/environment/dirt1.png", 32, 32);
	CLIPMANAGER->AddClip("dirt2", "sprites/blocks/environment/dirt2.png", 32, 32);
	CLIPMANAGER->AddClip("dirt3", "sprites/blocks/environment/dirt3.png", 32, 32);

	//돌
	CLIPMANAGER->AddClip("stone1", "sprites/blocks/environment/stone1.png", 32, 32);
	CLIPMANAGER->AddClip("stone2", "sprites/blocks/environment/stone2.png", 32, 32);
	CLIPMANAGER->AddClip("stone3", "sprites/blocks/environment/stone3.png", 32, 32);
	//현무암
	CLIPMANAGER->AddClip("basalt1", "sprites/blocks/environment/basalt1.png", 32, 32);
	CLIPMANAGER->AddClip("basalt2", "sprites/blocks/environment/basalt2.png", 32, 32);
	CLIPMANAGER->AddClip("basalt3", "sprites/blocks/environment/basalt3.png", 32, 32);
	//눈
	CLIPMANAGER->AddClip("snow1", "sprites/blocks/environment/snow1.png", 32, 32);
	CLIPMANAGER->AddClip("snow2", "sprites/blocks/environment/snow2.png", 32, 32);
	CLIPMANAGER->AddClip("snow3", "sprites/blocks/environment/snow3.png", 32, 32);


	/*======환경======*/
	//구리
	CLIPMANAGER->AddClip("copper1", "sprites/blocks/environment/copper1.png", 32, 32);
	CLIPMANAGER->AddClip("copper2", "sprites/blocks/environment/copper2.png", 32, 32);
	CLIPMANAGER->AddClip("copper3", "sprites/blocks/environment/copper3.png", 32, 32);
	//납
	CLIPMANAGER->AddClip("lead1", "sprites/blocks/environment/lead1.png", 32, 32);
	CLIPMANAGER->AddClip("lead2", "sprites/blocks/environment/lead2.png", 32, 32);
	CLIPMANAGER->AddClip("lead3", "sprites/blocks/environment/lead3.png", 32, 32);
	//조각
	CLIPMANAGER->AddClip("scrap1", "sprites/blocks/environment/scrap1.png", 32, 32);
	CLIPMANAGER->AddClip("scrap2", "sprites/blocks/environment/scrap2.png", 32, 32);
	CLIPMANAGER->AddClip("scrap3", "sprites/blocks/environment/scrap3.png", 32, 32);
	
	/*======오브젝트======*/
	//에너미 스팟
	CLIPMANAGER->AddClip("enemy_spawn", "sprites/blocks/environment/spawn.png", 32, 32);
	//코어

	//배터리
	CLIPMANAGER->AddClip("battery", "sprites/blocks/power/battery.png", 32, 32);

}

void MapTool::SetTileName(int selectNum)
{
	switch (selectNum)
	{
	case 0:
		tileName[selectNum] = "water";
		break;
	case 1:
		tileUI[selectNum].uiRenderer->Init("deep_water");
		tileName[selectNum] = "deep_water";
		break;
	case 2:
		tileUI[selectNum].uiRenderer->Init("sand1");
		tileName[selectNum] = "sand1";
	break;
	case 3:
		tileUI[selectNum].uiRenderer->Init("sand2");
		tileName[selectNum] = "sand2";
	break;
	case 4:
		tileUI[selectNum].uiRenderer->Init("sand3");
		tileName[selectNum] = "sand3";
	break;
	case 5:
		tileUI[selectNum].uiRenderer->Init("darksand_water");
		tileName[selectNum] = "darksand_water";
	break;
	case 6:
		tileUI[selectNum].uiRenderer->Init("dirt1");
		tileName[selectNum] = "dirt1";
	break;
	case 7:
		tileUI[selectNum].uiRenderer->Init("dirt2");
		tileName[selectNum] = "dirt2";
	break;
	case 8:
		tileUI[selectNum].uiRenderer->Init("dirt3");
		tileName[selectNum] = "dirt3";
	break;
	case 9:
		tileUI[selectNum].uiRenderer->Init("stone1");
		tileName[selectNum] = "stone1";
	break;
	case 10:
		tileUI[selectNum].uiRenderer->Init("stone2");
		tileName[selectNum] = "stone2";
	break;
	case 11:
		tileUI[selectNum].uiRenderer->Init("stone3");
		tileName[selectNum] = "stone3";
	break;
	case 12:
		tileUI[selectNum].uiRenderer->Init("basalt1");
		tileName[selectNum] = "basalt1";
	break;
	case 13:
		tileUI[selectNum].uiRenderer->Init("basalt2");
		tileName[selectNum] = "basalt2";
	break;
	case 14:
		tileUI[selectNum].uiRenderer->Init("basalt3");
		tileName[selectNum] = "basalt3"; 
	break;
	case 15:
		tileUI[selectNum].uiRenderer->Init("snow1");
		tileName[selectNum] = "snow1"; 
	break;
	case 16:
		tileUI[selectNum].uiRenderer->Init("snow2");
		tileName[selectNum] = "snow2";
	break;
	case 17:
		tileUI[selectNum].uiRenderer->Init("snow3");
		tileName[selectNum] = "snow3";
	break;
	case 18:
		tileUI[selectNum].uiRenderer->Init("copper1");
		tileName[selectNum] = "copper1";
	break;
	case 19:
		tileUI[selectNum].uiRenderer->Init("copper2");
		tileName[selectNum] = "copper3";
	break;
	case 20:
		tileUI[selectNum].uiRenderer->Init("copper3");
		tileName[selectNum] = "copper3";
	break;
	case 21:
		tileUI[selectNum].uiRenderer->Init("lead1");
		tileName[selectNum] = "lead1";
	break;
	case 22:
		tileUI[selectNum].uiRenderer->Init("lead2");
		tileName[selectNum] = "lead2";
	break;
	case 23:
		tileUI[selectNum].uiRenderer->Init("lead3");
		tileName[selectNum] = "lead3";
	break;
	case 24:
		tileUI[selectNum].uiRenderer->Init("scrap1");
		tileName[selectNum] = "scrap1";
	break;
	case 25:
		tileUI[selectNum].uiRenderer->Init("scrap3");
		tileName[selectNum] = "scrap2";
		break;
	case 26:
		tileUI[selectNum].uiRenderer->Init("scrap3");
		tileName[selectNum] = "scrap3";
		break;
	case 27:
		tileUI[selectNum].uiRenderer->Init("enemy_spawn");
		tileName[selectNum] = "enemy_spawn";
		break;
	case 28:
		tileUI[selectNum].uiRenderer->Init("battery");
		tileName[selectNum] = "battery";
		break;
	}

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
