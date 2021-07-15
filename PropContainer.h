#pragma once
class PropContainer
{
private:
	typedef ImageObject TILE;
	vector<TILE*> _tileV;
	vector<TILE*> _tilePreview;
public:
	PropContainer();
	~PropContainer();
	void Init();
	void Release();
	void Update();
	void Render();
	void LoadTileMap();
};

