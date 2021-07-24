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
	bool _isErase;			//Ÿ�� ����� ����
	bool _isDraw;			//���� ��� ����
	bool _isFill;			//����Ʈ�� ��� ����

	int _selectTile;		//Ÿ�� �ε���
	int _selectTool;		//������� �ε���

public:
	//undo �ؽ�
	unordered_map<int, tagTile> _undoHash;
	unordered_map<int, tagTile>::iterator _undoHashIter;

	//Ÿ�� ����
	tagTile tileInfo[TILENUMX * TILENUMY];

	//Ÿ�ϼ� 
	UIBase tileUI[TILESETX * TILESETY];

	//��������
	UIBase toolUI[3 * 3];
	string toolName[TILESETX * TILESETY];

	//��ü �� ����
	ImageObject tile[TILENUMX * TILENUMY];
	ImageObject resourcesTile[TILENUMX * TILENUMY];
	string tileName[TILESETX * TILESETY];

	//����Ʈ�� ä��� Ȯ�ο� ��Ʈ �� ��ǥ��
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

	//Ÿ�� �̹��� ����
	void SetTileImage();
	void SetTileName();

	//�� �̹��� ����
	void SetToolImage();
	void SetToolName(int selectNum);

	void Save();
	void Load();
	void Undo();
	
	bool RectinTile();		//ä���
	bool MouseInTile();		//����

};

