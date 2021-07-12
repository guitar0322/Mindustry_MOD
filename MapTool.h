#pragma once
#include "Component.h"
#include "TileInfo.h"
#include <string>
class MapTool :
	public Component
{

public:
	tagTile tile[TILENUMX * TILENUMY];
	/*tagTileSet tileSet[TILESETX * TILESETY];*/
	tagCurrentTile currentTile;
	string tileName[TILESETX * TILESETY];
	//DWORD attribute[TILEX * TILEY];	//타일속성
	UIBase tileUI[TILESETX * TILESETY];
	ImageObject _tile[TILENUMX * TILENUMY];
	int selectTile;
	virtual void Init();
	virtual void Update();
	virtual void Render();

	void Setup();
	void SetMap();

	void SetTileImage();


	tagTile* getTile() { return tile; }
	bool MouseInTile();
};

