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
	bool _isErase;			//타일 지우기 여부
	bool _isDraw;			//연필 사용 여부
	bool _isFill;			//페인트통 사용 여부

	int _selectTile;		//타일 인덱스
	int _selectTool;		//도구모움 인덱스

public:
	//undo 해쉬
	unordered_map<int, tagTile> _undoHash;
	unordered_map<int, tagTile>::iterator _undoHashIter;

	//타일 정보
	tagTile tileInfo[TILENUMX * TILENUMY];

	//타일셋 
	UIBase tileUI[TILESETX * TILESETY];

	//도구모음
	UIBase toolUI[3 * 3];
	string toolName[TILESETX * TILESETY];

	//전체 맵 셋팅
	ImageObject tile[TILENUMX * TILENUMY];
	ImageObject resourcesTile[TILENUMX * TILENUMY];
	string tileName[TILESETX * TILESETY];

	//페인트통 채우기 확인용 렉트 및 좌표값
	Rect dragRc;
	int dragRcWidth, dragRcHeight;
	int startX, startY;
	int endX, endY;
	float startMouseWorldX, startMouseWorldY;
	float endMouseWorldX, endMouseWorldY;

	virtual void Init();
	virtual void Update();
	virtual void Render();

	void Setup();

	//타일 이미지 관련
	void SetTileImage();
	void SetTileName(int selectNum);

	//툴 이미지 관련
	void SetToolImage();
	void SetToolName(int selectNum);

	void Save();
	void Load();
	void Undo();
	
	bool RectinTile();		//채우기
	bool MouseInTile();		//연필

	void SetFileName(string fileName);
};

