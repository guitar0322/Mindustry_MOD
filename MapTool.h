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
	
	//undo �ؽ�
	unordered_map<int, tagTile> _undoHash;
	unordered_map<int, tagTile>::iterator _undoHashIter;

	//resources �ؽ�
	unordered_map<int, ImageObject> _resourcesHash;
	unordered_map<int, ImageObject>::iterator _resourcesHashIter;

	//Ÿ�� ����
	tagTile tileInfo[TILENUMX * TILENUMY];

	//���� Ÿ��
	tagCurrentTile currentTile;

	//DWORD attribute[TILEX * TILEY];	//Ÿ�ϼӼ�

	//Ÿ�ϼ� 
	UIBase tileUI[TILESETX * TILESETY];

	//��������
	UIBase toolUI[3 * 3];
	string toolName[TILESETX * TILESETY];

	//��ü �� ����
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

