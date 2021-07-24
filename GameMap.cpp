#include "stdafx.h"
#include "GameMap.h"

GameMap::GameMap()
{
}

GameMap::~GameMap()
{
}

HRESULT GameMap::Init()
{
	SetTileImage();
	SetTileName();
	//맵 셋팅
	for (int i = 0; i < TILENUMY; ++i)
	{
		for (int j = 0; j < TILENUMX; ++j)
		{
			_tile[i * TILENUMX + j].transform->SetPosition(16 + TILESIZE * j, 16 + TILESIZE * i);
			_tile[i * TILENUMX + j].renderer->Init("water");
			_tile[i * TILENUMX + j].renderer->RenderStatic();
			_tile[i * TILENUMX + j].renderer->SetStatic(true);

			_resourcesTile[i * TILENUMX + j].transform->SetPosition(16 + TILESIZE * j, 16 + TILESIZE * i);
			_resourcesTile[i * TILENUMX + j].renderer->RenderStatic();
			_resourcesTile[i * TILENUMX + j].renderer->SetStatic(true);

			_tileInfo[i * TILENUMX + j].environment = ENV_WATER;
			_tileInfo[i * TILENUMX + j].resources = RES_NONE;
		}
	}
	Load();
	return S_OK;
}

void GameMap::Update()
{

}

void GameMap::Render()
{
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
			_tile[i * TILENUMX + j].Render();
			if (_tileInfo[i * TILENUMX + j].resources != RES_NONE)
			_resourcesTile[i * TILENUMX + j].Render();
		}
	}
}

void GameMap::Load()
{
	vector<string> loadData = TXTDATAMANAGER->txtLoad("tile_info.txt");
	StaticBuffer->BeginDraw();
	for (int i = 0; i < loadData.size(); i += 2) {
		int env = atoi(loadData[i].c_str());
		int res = atoi(loadData[i + 1].c_str());
		_tileInfo[i / 2].environment = (ENVIRONMENT)env;
		_tileInfo[i / 2].resources = (RESOURCES)res;
		_tile[i / 2].renderer->Init(_tileName[env]);
		_tile[i / 2].renderer->RenderStatic();

		_resourcesTile[i / 2].renderer->Init(_tileName[res + 23]);
		if(_tileInfo[i / 2].resources != RES_NONE)
			_resourcesTile[i / 2].renderer->RenderStatic();
	}
	StaticBuffer->EndDraw();
}

void GameMap::SetTileImage()
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

void GameMap::SetTileName()
{
	int idx = 0;
	_tileName[idx++] = "water";
	_tileName[idx++] = "deep_water";
	_tileName[idx++] = "sand1";
	_tileName[idx++] = "sand2";
	_tileName[idx++] = "sand3";			//4
	_tileName[idx++] = "darksand_water";
	_tileName[idx++] = "dirt1";
	_tileName[idx++] = "dirt2";
	_tileName[idx++] = "dirt3";
	_tileName[idx++] = "stone1";			//9
	_tileName[idx++] = "stone2";
	_tileName[idx++] = "stone3";
	_tileName[idx++] = "basalt1";
	_tileName[idx++] = "basalt2";
	_tileName[idx++] = "basalt3";		//14
	_tileName[idx++] = "snow1";
	_tileName[idx++] = "snow2";
	_tileName[idx++] = "snow3";
	_tileName[idx++] = "ice1";
	_tileName[idx++] = "ice2";			//19
	_tileName[idx++] = "ice3";
	_tileName[idx++] = "ice_wall1";
	_tileName[idx++] = "ice_wall2";
	_tileName[idx++] = "copper1";
	_tileName[idx++] = "copper3";		//24
	_tileName[idx++] = "copper3";
	_tileName[idx++] = "lead1";
	_tileName[idx++] = "lead2";
	_tileName[idx++] = "lead3";
	_tileName[idx++] = "scrap1";			//29
	_tileName[idx++] = "scrap2";
	_tileName[idx++] = "scrap3";
	_tileName[idx++] = "enemy_spawn";
	_tileName[idx++] = "space";			//33
	_tileName[idx++] = "space";			//33
	_tileName[idx++] = "space";			//33

	//switch (selectNum)
	//{
	//case 0:
	//	_tileName[selectNum] = "water";
	//	break;
	//case 1:
	//	_tileName[selectNum] = "deep_water";
	//	break;
	//case 2:
	//	_tileName[selectNum] = "sand1";
	//	break;
	//case 3:
	//	_tileName[selectNum] = "sand2";
	//	break;
	//case 4:
	//	_tileName[selectNum] = "sand3";
	//	break;
	//case 5:
	//	_tileName[selectNum] = "darksand_water";
	//	break;
	//case 6:
	//	_tileName[selectNum] = "dirt1";
	//	break;
	//case 7:
	//	_tileName[selectNum] = "dirt2";
	//	break;
	//case 8:
	//	_tileName[selectNum] = "dirt3";
	//	break;
	//case 9:
	//	_tileName[selectNum] = "stone1";
	//	break;
	//case 10:
	//	_tileName[selectNum] = "stone2";
	//	break;
	//case 11:
	//	_tileName[selectNum] = "stone3";
	//	break;
	//case 12:
	//	_tileName[selectNum] = "basalt1";
	//	break;
	//case 13:
	//	_tileName[selectNum] = "basalt2";
	//	break;
	//case 14:
	//	_tileName[selectNum] = "basalt3";
	//	break;
	//case 15:
	//	_tileName[selectNum] = "snow1";
	//	break;
	//case 16:
	//	_tileName[selectNum] = "snow2";
	//	break;
	//case 17:
	//	_tileName[selectNum] = "snow3";
	//	break;
	//case 18:
	//	_tileName[selectNum] = "copper1";
	//	break;
	//case 19:
	//	_tileName[selectNum] = "copper3";
	//	break;
	//case 20:
	//	_tileName[selectNum] = "copper3";
	//	break;
	//case 21:
	//	_tileName[selectNum] = "lead1";
	//	break;
	//case 22:
	//	_tileName[selectNum] = "lead2";
	//	break;
	//case 23:
	//	_tileName[selectNum] = "lead3";
	//	break;
	//case 24:
	//	_tileName[selectNum] = "scrap1";
	//	break;
	//case 25:
	//	_tileName[selectNum] = "scrap2";
	//	break;
	//case 26:
	//	_tileName[selectNum] = "scrap3";
	//	break;
	//case 27:
	//	_tileName[selectNum] = "enemy_spawn";
	//	break;
	//case 28:
	//	_tileName[selectNum] = "space";
	//	break;
	//}
}
