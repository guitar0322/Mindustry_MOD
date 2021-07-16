#pragma once
#include "Scene.h"
class MapScene :
	public Scene
{
private:
	ImageObject _background;
	GameObject _mapTool;
public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

};

