#include "stdafx.h"
#include "MapTool.h"

void MapTool::Init()
{
	SetTileImage();
	SetToolImage();
	Setup();

	_isErase = false;
	_isDraw = true;
	_isFill = false;

	SetTileName();

	for (int i = 0; i < TILESETY; ++i)
	{
		for (int j = 0; j < TILESETX; ++j)
		{
			tileUI[i* TILESETX + j].Init();
			tileUI[i * TILESETX + j].uiRenderer->Init(tileName[i * TILESETX + j]);
			tileUI[i * TILESETX + j].uiMouseEvent->enable = false;
			tileUI[i* TILESETX + j].transform->SetPosition(WINSIZEX - 40*j - 70, 100 + 40*i);
			
			//각 타일에 이미지 부여
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
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		MainCam->transform->MoveY(-5.f);
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		MainCam->transform->MoveX(-5.f);
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		MainCam->transform->MoveY(5.f);
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		MainCam->transform->MoveX(5.f);
	}

	//if (MainCam->transform->GetX() <= MainCam->GetRenderWidth() / 2)
	//	MainCam->transform->SetX(MainCam->GetRenderWidth() / 2);
	//if (MainCam->transform->GetX() >= MAPWIDTH - MainCam->GetRenderWidth() / 2)
	//	MainCam->transform->SetX(MAPWIDTH - MainCam->GetRenderWidth() / 2);

	//if (MainCam->transform->GetY() <= MainCam->GetRenderHeight() / 2)
	//	MainCam->transform->SetY(MainCam->GetRenderHeight() / 2);
	//if (MainCam->transform->GetY() >= MAPHEIGHT - MainCam->GetRenderHeight() / 2)
	//	MainCam->transform->SetY(MAPHEIGHT - MainCam->GetRenderHeight() / 2);

	MainCam->Update();

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
	int tileStartX = MainCam->GetCameraStartX() / TILESIZE - 2;
	if (tileStartX < 0)
		tileStartX = 0;
	int tileEndX = (MainCam->GetCameraStartX() + MainCam->GetRenderWidth()) / TILESIZE + 2;
	if (tileEndX > TILENUMX - 1)
		tileEndX = TILENUMX - 1;

	int tileStartY = MainCam->GetCameraStartY() / TILESIZE - 2;
	if (tileStartY < 0)
		tileStartY = 0;
	int tileEndY = (MainCam->GetCameraStartY() + MainCam->GetRenderHeight()) / TILESIZE + 2;
	if (tileEndY > TILENUMX - 1)
		tileEndY = TILENUMX - 1;

	for (int i = tileStartY; i < tileEndY; ++i)
	{
		for (int j = tileStartX; j < tileEndX; ++j)
		{
			tile[i * TILENUMX + j].Update();
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_ptMouse.x >= MainCam->GetScreenStart().first && _ptMouse.x <= MainCam->GetScreenStart().first + MainCam->GetScreenWidth())
		{
			_undoHash.clear();

			if (_isFill)
			{
				startMouseWorldX = ScreenToWorld(_ptMouse).x;
				startMouseWorldY = ScreenToWorld(_ptMouse).y;
				startX = startMouseWorldX / TILESIZE;
				startY = startMouseWorldY / TILESIZE;
			}
		}
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
					_selectTile = i * TILESETX + j;
					break;
				}
			}
		}

		if (_isFill)
		{
			if (_ptMouse.x >= MainCam->GetScreenStart().first && _ptMouse.x <= MainCam->GetScreenStart().first + MainCam->GetScreenWidth())
			{
				RectinTile();
				dragRc = Rect();
			}
		}
		
		//도구모음 클릭 시
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				if (Vector2InRect(&toolUI[i * 3 + j].uiRenderer->GetRc(), &_ptMouse))
				{
					_isErase = false;
					_isDraw = true;
					_isFill = false;
					_selectTool = i * 3 + j;
					switch (_selectTool) {
					case 0:
						Save();
						break;
					case 1:
						Load();
						break;
					case 3:
						Undo();
						break;
					case 4:
						_isDraw = false;
						_isFill = true;
						break;
					case 5:
						_isDraw = true;
						break;
					case 6:
						_isErase = true;
						_isDraw = false;
						_isFill = false;
						break;
					case 7:
						SCENEMANAGER->LoadScene("title");
					break;
					}

					break;
				}
			}
		}

	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{

		if (_isFill == true)
		{
			if (_ptMouse.x >= MainCam->GetScreenStart().first && _ptMouse.x <= MainCam->GetScreenStart().first + MainCam->GetScreenWidth())
			{
				endMouseWorldX = ScreenToWorld(_ptMouse).x;
				endMouseWorldY = ScreenToWorld(_ptMouse).y;
				endX = endMouseWorldX / TILESIZE + 1;
				endY = endMouseWorldY / TILESIZE + 1;
				dragRcWidth = endX - startX;
				dragRcHeight = endY - startY;
				dragRc = RectMakePivot(Vector2(startX * TILESIZE, startY * TILESIZE), Vector2(dragRcWidth * TILESIZE, dragRcHeight * TILESIZE), Pivot::LeftTop);
			}
		}
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

	int tileStartX = MainCam->GetCameraStartX() / TILESIZE - 2;
	if (tileStartX < 0)
		tileStartX = 0;
	int tileEndX = (MainCam->GetCameraStartX() + MainCam->GetRenderWidth()) / TILESIZE + 2;
	if (tileEndX > TILENUMX - 1)
		tileEndX = TILENUMX - 1;

	int tileStartY = MainCam->GetCameraStartY() / TILESIZE - 2;
	if (tileStartY < 0)
		tileStartY = 0;
	int tileEndY = (MainCam->GetCameraStartY() + MainCam->GetRenderHeight()) / TILESIZE + 2;
	if (tileEndY > TILENUMX - 1)
		tileEndY = TILENUMX - 1;
	for (int i = tileStartY; i < tileEndY; ++i)
	{
		for (int j = tileStartX; j < tileEndX; ++j)
		{
			tile[i * TILENUMX + j].Render();
			if (tileInfo[i * TILENUMX + j].resources != RES_NONE)
				resourcesTile[i * TILENUMX + j].Render();
		}
	}

	if(_isFill) 
		D2DRENDERER->DrawRectangle(dragRc, D2DRenderer::DefaultBrush::Red);
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
	//얼음
	CLIPMANAGER->AddClip("ice1", "sprites/blocks/environment/ice1.png", 32, 32);
	CLIPMANAGER->AddClip("ice2", "sprites/blocks/environment/ice2.png", 32, 32);
	CLIPMANAGER->AddClip("ice3", "sprites/blocks/environment/ice3.png", 32, 32);

	//얼음벽
	CLIPMANAGER->AddClip("ice_wall1", "sprites/blocks/environment/ice-wall1.png", 32, 32);
	CLIPMANAGER->AddClip("ice_wall2", "sprites/blocks/environment/ice-wall2.png", 32, 32);

	//스페이스
	CLIPMANAGER->AddClip("space", "sprites/blocks/environment/space.png", 32, 32);

	/*WALL*/




	/*======자원======*/
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



}

void MapTool::SetTileName()
{
	int idx = 0;
	tileName[idx++] = "water";
	tileName[idx++] = "deep_water";
	tileName[idx++] = "sand1";
	tileName[idx++] = "sand2";
	tileName[idx++] = "sand3";			//4
	tileName[idx++] = "darksand_water";
	tileName[idx++] = "dirt1";
	tileName[idx++] = "dirt2";
	tileName[idx++] = "dirt3";
	tileName[idx++] = "stone1";			//9
	tileName[idx++] = "stone2";
	tileName[idx++] = "stone3";
	tileName[idx++] = "basalt1";
	tileName[idx++] = "basalt2";
	tileName[idx++] = "basalt3";		//14
	tileName[idx++] = "snow1";
	tileName[idx++] = "snow2";
	tileName[idx++] = "snow3";
	tileName[idx++] = "ice1";
	tileName[idx++] = "ice2";			//19
	tileName[idx++] = "ice3";
	tileName[idx++] = "ice_wall1";
	tileName[idx++] = "ice_wall2";
	tileName[idx++] = "space";			
	tileName[idx++] = "space";			//24
	tileName[idx++] = "space";			
	tileName[idx++] = "copper1";		//26
	tileName[idx++] = "copper3";		
	tileName[idx++] = "copper3";
	tileName[idx++] = "lead1";
	tileName[idx++] = "lead2";
	tileName[idx++] = "lead3";			//31
	tileName[idx++] = "scrap1";			
	tileName[idx++] = "scrap2";
	tileName[idx++] = "scrap3";			//34
	tileName[idx++] = "enemy_spawn";



	//switch (selectNum)
	//{
	//case 0:
	//	tileName[selectNum] = "water";
	//break;
	//case 1:
	//	tileUI[selectNum].uiRenderer->Init("deep_water");
	//	tileName[selectNum] = "deep_water";
	//break;
	//case 2:
	//	tileUI[selectNum].uiRenderer->Init("sand1");
	//	tileName[selectNum] = "sand1";
	//break;
	//case 3:
	//	tileUI[selectNum].uiRenderer->Init("sand2");
	//	tileName[selectNum] = "sand2";
	//break;
	//case 4:
	//	tileUI[selectNum].uiRenderer->Init("sand3");
	//	tileName[selectNum] = "sand3";
	//break;
	//case 5:
	//	tileUI[selectNum].uiRenderer->Init("darksand_water");
	//	tileName[selectNum] = "darksand_water";
	//break;
	//case 6:
	//	tileUI[selectNum].uiRenderer->Init("dirt1");
	//	tileName[selectNum] = "dirt1";
	//break;
	//case 7:
	//	tileUI[selectNum].uiRenderer->Init("dirt2");
	//	tileName[selectNum] = "dirt2";
	//break;
	//case 8:
	//	tileUI[selectNum].uiRenderer->Init("dirt3");
	//	tileName[selectNum] = "dirt3";
	//break;
	//case 9:
	//	tileUI[selectNum].uiRenderer->Init("stone1");
	//	tileName[selectNum] = "stone1";
	//break;
	//case 10:
	//	tileUI[selectNum].uiRenderer->Init("stone2");
	//	tileName[selectNum] = "stone2";
	//break;
	//case 11:
	//	tileUI[selectNum].uiRenderer->Init("stone3");
	//	tileName[selectNum] = "stone3";
	//break;
	//case 12:
	//	tileUI[selectNum].uiRenderer->Init("basalt1");
	//	tileName[selectNum] = "basalt1";
	//break;
	//case 13:
	//	tileUI[selectNum].uiRenderer->Init("basalt2");
	//	tileName[selectNum] = "basalt2";
	//break;
	//case 14:
	//	tileUI[selectNum].uiRenderer->Init("basalt3");
	//	tileName[selectNum] = "basalt3"; 
	//break;
	//case 15:
	//	tileUI[selectNum].uiRenderer->Init("snow1");
	//	tileName[selectNum] = "snow1"; 
	//break;
	//case 16:
	//	tileUI[selectNum].uiRenderer->Init("snow2");
	//	tileName[selectNum] = "snow2";
	//break;
	//case 17:
	//	tileUI[selectNum].uiRenderer->Init("snow3");
	//	tileName[selectNum] = "snow3";
	//break;
	//case 18:
	//	tileUI[selectNum].uiRenderer->Init("copper1");
	//	tileName[selectNum] = "copper1";
	//break;
	//case 19:
	//	tileUI[selectNum].uiRenderer->Init("copper2");
	//	tileName[selectNum] = "copper3";
	//break;
	//case 20:
	//	tileUI[selectNum].uiRenderer->Init("copper3");
	//	tileName[selectNum] = "copper3";
	//break;
	//case 21:
	//	tileUI[selectNum].uiRenderer->Init("lead1");
	//	tileName[selectNum] = "lead1";
	//break;
	//case 22:
	//	tileUI[selectNum].uiRenderer->Init("lead2");
	//	tileName[selectNum] = "lead2";
	//break;
	//case 23:
	//	tileUI[selectNum].uiRenderer->Init("lead3");
	//	tileName[selectNum] = "lead3";
	//break;
	//case 24:
	//	tileUI[selectNum].uiRenderer->Init("scrap1");
	//	tileName[selectNum] = "scrap1";

	//break;
	//case 25:
	//	tileUI[selectNum].uiRenderer->Init("scrap3");
	//	tileName[selectNum] = "scrap2";
	//break;
	//case 26:
	//	tileUI[selectNum].uiRenderer->Init("scrap3");
	//	tileName[selectNum] = "scrap3";
	//break;
	//case 27:
	//	tileUI[selectNum].uiRenderer->Init("enemy_spawn");
	//	tileName[selectNum] = "enemy_spawn";
	//break;
	//case 28:
	//	tileUI[selectNum].uiRenderer->Init("space");
	//	tileName[selectNum] = "space";
	//break;
	//}

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
		resourcesTile[i / 2].renderer->Init(tileName[res+23]);
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

bool MapTool::RectinTile()
{
	if (_isFill == false) return false;

	if (_ptMouse.x <= MainCam->GetScreenStart().first || _ptMouse.x >= MainCam->GetScreenStart().first + MainCam->GetScreenWidth())
		return false;


	
	for (int i = startY; i < endY; i++)
	{
		for (int j = startX; j < endX; j++)
		{
			_undoHash.insert(pair<int, tagTile>(i * TILENUMX + j, tileInfo[i * TILENUMX + j]));

			if (_selectTile >= 26 && _selectTile <= 34)
			{
				tileInfo[i * TILENUMX + j].resources = (RESOURCES)(_selectTile - 26);
				resourcesTile[i * TILENUMX + j].renderer->Init(tileName[_selectTile]);
			}
			else
			{
				tileInfo[i * TILENUMX + j].environment = (ENVIRONMENT)_selectTile;
				tile[i * TILENUMX + j].renderer->Init(tileName[_selectTile]);
			}
		}
	}

	return true;
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

	if (_isErase)
	{
		tileInfo[tileY * TILENUMX + tileX].resources = (RESOURCES)9;
		tileInfo[tileY * TILENUMX + tileX].environment = (ENVIRONMENT)0;
		tile[tileY * TILENUMX + tileX].renderer->Init("water");
	}
	else
	{
		if (_isDraw)
		{
			if (_selectTile >= 26 && _selectTile <= 34)
			{
				tileInfo[tileY * TILENUMX + tileX].resources = (RESOURCES)(_selectTile - 26);
				resourcesTile[tileY * TILENUMX + tileX].renderer->Init(tileName[_selectTile]);
			}
			else
			{
				tileInfo[tileY * TILENUMX + tileX].environment = (ENVIRONMENT)_selectTile;
				tile[tileY * TILENUMX + tileX].renderer->Init(tileName[_selectTile]);
			}
		}
		
	}

	return true;
}

void MapTool::SetFileName(string fileName)
{
}
