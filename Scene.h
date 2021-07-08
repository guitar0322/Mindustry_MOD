#pragma once
#include "Cam.h"
//class Cam;
class Scene
{
public:
	Scene();
	~Scene();
	Cam* mainCam;

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	void SetBackBufferSize(int width, int height);
	void ChangeMainCam(Cam* newCam);
};

