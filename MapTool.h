#pragma once
#include "Component.h"
#include "TileInfo.h"
#include <string>
#include <map>
#include <unordered_map>

using namespace std;
class MapTool :
	public Component
{
private:
	int _tileIdx;
public:
	
	//undo 해쉬
	unordered_map<int, tagTile> _undoHash;
	unordered_map<int, tagTile>::iterator _undoHashIter;

	//resources 해쉬
	unordered_map<int, ImageObject> _resourcesHash;
	unordered_map<int, ImageObject>::iterator _resourcesHashIter;

	//타일 정보
	tagTile tileInfo[TILENUMX * TILENUMY];

	//현재 타일
	tagCurrentTile currentTile;

	//DWORD attribute[TILEX * TILEY];	//타일속성

	//타일셋 
	UIBase tileUI[TILESETX * TILESETY];

	//도구모음
	UIBase toolUI[3 * 3];
	string toolName[TILESETX * TILESETY];

	//전체 맵 셋팅
	ImageObject tile[TILENUMX * TILENUMY];
	ImageObject resourcesTile[TILENUMX * TILENUMY];

	string tileName[TILESETX * TILESETY];


	int selectTile;
	int selectTool;
	bool isErase;
	bool isDraw;

	virtual void Init();
	virtual void Update();
	virtual void Render();

	void Setup();

	void SetTileImage();
	void SetTileName(int selectNum);

	void SetToolImage();
	void SetToolName(int selectNum);

	void Save();
	void Load();
	void Undo();


	//tagTile* getTile() { return tile; }
	bool MouseInTile();
	void SetFileName(string fileName);
};

