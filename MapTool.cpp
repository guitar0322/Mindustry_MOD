#include "stdafx.h"
#include "MapTool.h"

void MapTool::Init()
{
	SetTileImage();
	SetToolImage();
	Setup();

	isErase = false;
	isDraw = true;


	for (int i = 0; i < TILESETY; ++i)
	{
		for (int j = 0; j < TILESETX; ++j)
		{
			tileUI[i* TILESETX + j].Init();
			tileUI[i* TILESETX + j].uiRenderer->Init("water");
			tileUI[i * TILESETX + j].uiMouseEvent->enable = false;
			tileUI[i* TILESETX + j].transform->SetPosition(WINSIZEX - 40*j -50, 100 + 40*i);
			
			//각 타일에 이미지 부여
			SetTileName(i* TILESETX + j);
		}
	}


	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			toolUI[i* 3 + j].Init();
			toolUI[i* 3 + j].uiRenderer->Init("save");
			toolUI[i * 3 + j].uiMouseEvent->enable = false;
			toolUI[i* 3 + j].transform->SetPosition(60 * j + 50, 50 + 60 * i);

			//각 도구에 이미지 부여
			SetToolName(i* 3 + j);
		}
	}
}

void MapTool::Update()
{

	/* =====UI 구현=====*/

	//타일셋
	for (int i = 0; i < TILESETY; ++i)
	{
		for (int j = 0; j < TILESETX; ++j)
		{
			tileUI[i* TILESETX + j].Update();
		}
	}

	//도구모음
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			toolUI[i* 3 + j].Update();
		}
	}


	/* =====맵 구현=====*/
	int tileStart = MainCam->GetCameraStartX() / TILESIZE - 2;
	if (tileStart < 0)
		tileStart = 0;
	int tileEnd = (MainCam->GetCameraStartX() + MainCam->GetRenderWidth()) / TILESIZE + 2;
	if (tileEnd > TILENUMX - 1)
		tileEnd = TILENUMX - 1;

	for (int i = tileStart; i < tileEnd; ++i)
	{
		for (int j = tileStart; j < tileEnd; ++j)
		{
			tile[i * TILENUMX + j].Update();
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_ptMouse.x >= MainCam->GetScreenStart().first && _ptMouse.x <= MainCam->GetScreenStart().first + MainCam->GetScreenWidth())
			_undoHash.clear();
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		//타일셋 클릭 시
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

		//도구모음 클릭 시
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				if (Vector2InRect(&toolUI[i * 3 + j].uiRenderer->GetRc(), &_ptMouse))
				{
					isErase = false;
					isDraw = true;
					selectTool = i * 3 + j;
					switch (selectTool) {
					case 0:
						Save();
						break;
					case 1:
						Load();
						break;
					case 3:
						Undo();
						break;
					case 5:
						isDraw = true;
						break;
					case 6:
						isErase = true;
						isDraw = false;
						break;

					}

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

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			toolUI[i* 3 + j].Render();
		}
	}

	int tileStart = MainCam->GetCameraStartX() / TILESIZE - 2;
	if (tileStart < 0)
		tileStart = 0;
	int tileEnd = (MainCam->GetCameraStartX() + MainCam->GetRenderWidth()) / TILESIZE + 2;
	if (tileEnd > TILENUMX - 1)
		tileEnd = TILENUMX - 1;
	cout << tileEnd << endl;
	for (int i = tileStart; i < tileEnd; ++i)
	{
		for (int j = tileStart; j < tileEnd; ++j)
		{
			tile[i * TILENUMX + j].Render();
			if (tileInfo[i * TILENUMX + j].resources != RES_NONE)
				resourcesTile[i * TILENUMX + j].Render();
		}
	}

}

void MapTool::Setup()
{
	//맵 셋팅
	for (int i = 0; i < TILENUMY; ++i)
	{
		for (int j = 0; j < TILENUMX; ++j)
		{
			tile[i * TILENUMX + j].transform->SetPosition(16 + TILESIZE * j, 16 + TILESIZE * i);
			tile[i * TILENUMX + j].renderer->Init("water");

			resourcesTile[i * TILENUMX + j].transform->SetPosition(16 + TILESIZE * j, 16 + TILESIZE * i);

			tileInfo[i * TILENUMX + j].environment = ENV_WATER;
			tileInfo[i * TILENUMX + j].resources = RES_NONE;
		}
	}
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

void MapTool::SetToolImage()
{
	CLIPMANAGER->AddClip("save", "icons/save.png", 32, 32);
	CLIPMANAGER->AddClip("load", "icons/load.png", 32, 32);
	CLIPMANAGER->AddClip("pick", "icons/pick.png", 32, 32);
	CLIPMANAGER->AddClip("undo", "icons/undo.png", 32, 32);
	CLIPMANAGER->AddClip("fill", "icons/fill.png", 32, 32);
	CLIPMANAGER->AddClip("pencil", "icons/pencil.png", 32, 32);
	CLIPMANAGER->AddClip("eraser", "icons/eraser.png", 32, 32);
	CLIPMANAGER->AddClip("exit", "icons/exit.png", 32, 32);

}

void MapTool::SetToolName(int selectNum)
{
	switch (selectNum)
	{
	case 0:
		toolName[selectNum] = "save";
	break;
	case 1:
		toolUI[selectNum].uiRenderer->Init("load");
		toolName[selectNum] = "load";
	break;
	case 2:
		toolUI[selectNum].uiRenderer->Init("pick");
		toolName[selectNum] = "pick";
	break;
	case 3:
		toolUI[selectNum].uiRenderer->Init("undo");
		toolName[selectNum] = "undo";
	break;
	case 4:
		toolUI[selectNum].uiRenderer->Init("fill");
		toolName[selectNum] = "fill";
	break;
	case 5:
		toolUI[selectNum].uiRenderer->Init("pencil");
		toolName[selectNum] = "pencil";
	break;
	case 6:
		toolUI[selectNum].uiRenderer->Init("eraser");
		toolName[selectNum] = "eraser";
	break;
	case 7:
		toolUI[selectNum].uiRenderer->Init("exit");
		toolName[selectNum] = "exit";
	break;

	}


}

void MapTool::Save()
{
	vector<string> saveData;

	for (int i = 0; i < TILENUMY; ++i)
	{
		for (int j = 0; j < TILENUMX; ++j)
		{
			saveData.push_back(to_string(tileInfo[i * TILENUMX + j].environment));
			saveData.push_back(to_string(tileInfo[i * TILENUMX + j].resources));
		}
	}
	TXTDATAMANAGER->txtSave("tile_info.txt", saveData);
}

void MapTool::Load()
{
	vector<string> loadData = TXTDATAMANAGER->txtLoad("tile_info.txt");
	for (int i = 0; i < loadData.size(); i += 2) {
		int env = atoi(loadData[i].c_str());
		int res = atoi(loadData[i + 1].c_str());
		tileInfo[i / 2].environment = (ENVIRONMENT)env;
		tileInfo[i / 2].resources = (RESOURCES)res;
		tile[i / 2].renderer->Init(tileName[env]);
	}
}

void MapTool::Undo()
{
	for (_undoHashIter = _undoHash.begin(); _undoHashIter != _undoHash.end(); _undoHashIter++)
	{
		int tileX = _undoHashIter->first % TILENUMX;
		int tileY = _undoHashIter->first / TILENUMX;
		tagTile preTile = _undoHashIter->second;
		tileInfo[tileY * TILENUMX + tileX].environment = preTile.environment;
		tileInfo[tileY * TILENUMX + tileX].resources = preTile.resources;
		tileInfo[tileY * TILENUMX + tileX].object = preTile.object;
		tile[tileY * TILENUMX + tileX].renderer->Init(tileName[preTile.environment]);
	}
}


bool MapTool::MouseInTile()
{

	if (_ptMouse.x <= MainCam->GetScreenStart().first || _ptMouse.x >= MainCam->GetScreenStart().first + MainCam->GetScreenWidth())
		return false;
	float mouseWorldX = ScreenToWorld(_ptMouse).x;
	float mouseWorldY = ScreenToWorld(_ptMouse).y;
	int tileX = mouseWorldX / TILESIZE;
	int tileY = mouseWorldY / TILESIZE;

	//undo Iter
	_undoHashIter = _undoHash.find(tileY * TILENUMX + tileX);

	if (_undoHashIter != _undoHash.end())
	{
		return false;
	}
	else
	{
		_undoHash.insert(pair<int, tagTile>(tileY * TILENUMX + tileX, tileInfo[tileY * TILENUMX + tileX]));
	}

	//resources Iter
	_resourcesHashIter = _resourcesHash.find(tileY * TILENUMX + tileX);

	if (_resourcesHashIter != _resourcesHash.end())
	{
		return false;
	}
	else
	{
		_resourcesHash.insert(pair<int, ImageObject>(tileY * TILENUMX + tileX, resourcesTile[tileY * TILENUMX + tileX]));
	}

	if (isErase)
	{
		tileInfo[tileY * TILENUMX + tileX].resources = (RESOURCES)9;
		tileInfo[tileY * TILENUMX + tileX].environment = (ENVIRONMENT)0;
		tile[tileY * TILENUMX + tileX].renderer->Init("water");
	}
	else
	{
		if (selectTile >= 18 && selectTile <= 26)
		{
			tileInfo[tileY * TILENUMX + tileX].resources = (RESOURCES)(selectTile - 18);
			resourcesTile[tileY * TILENUMX + tileX].renderer->Init(tileName[selectTile]);
		}
		else
		{
			tileInfo[tileY * TILENUMX + tileX].environment = (ENVIRONMENT)selectTile;
			tile[tileY * TILENUMX + tileX].renderer->Init(tileName[selectTile]);
		}
	}

	return true;
}

void MapTool::SetFileName(string fileName)
{
}
