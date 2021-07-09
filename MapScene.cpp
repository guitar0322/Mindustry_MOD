#include "stdafx.h"
#include "MapScene.h"
#include "MapTool.h"
HRESULT MapScene::Init()
{
	Scene::Init();

	CLIPMANAGER->AddClip("background", "scene1_background.png", 1024, 560);
	SetBackBufferSize(1024, 560);
	MainCam->SetScreenStart(132, 0);
	MainCam->SetScreenSize(568, WINSIZEY);
	MainCam->SetRenderSize(568, WINSIZEY);
	MainCam->transform->SetX(568 / 2);
	_background.Init();
	_background.renderer->Init("background");
	_background.transform->SetPosition(MAPWIDTH / 2, MAPHEIGHT / 2);

	_mapTool.AddComponent(new MapTool());
	_mapTool.GetComponent<MapTool>()->Init();
	return S_OK;
}

void MapScene::Update()
{
	_background.Update();
	_mapTool.Update();
}

void MapScene::Render()
{
	_background.Render();
	_mapTool.Render();
	MainCam->Render();
}

void MapScene::Release()
{
}
