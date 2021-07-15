#pragma once
#include "TileInfo.h"

class GameMap
{
private:
	//∏ 
	ImageObject _tile[TILENUMX * TILENUMY];
	ImageObject _resourcesTile[TILENUMX * TILENUMY];
	string _tileName[TILESETX * TILESETY];

	//≈∏¿œ ¡§∫∏
	tagTile _tileInfo[TILENUMX * TILENUMY];

public:
	GameMap();
	~GameMap();

	HRESULT Init();
	void Update();
	void Render();
	void Load();

	void SetTileImage();
	void SetTileName(int selectNum);


};

