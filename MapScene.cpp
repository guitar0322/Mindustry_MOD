#include "stdafx.h"
#include "MapScene.h"
#include "MapTool.h"
HRESULT MapScene::Init()
{
	Scene::Init();

	CLIPMANAGER->AddClip("background", "scene1_background.png", 1024, 560);
	SetBackBufferSize(1600, 1600);
	MainCam->SetScreenStart(240, 0);
	MainCam->SetScreenSize(WINSIZEY, WINSIZEY);
	MainCam->SetRenderSize(1600, 1600);
	MainCam->transform->SetPosition(1600 / 2, 1600 / 2);

	SOUNDMANAGER->addSound("editorbgm", "music/editor.mp3", true, true);
	SOUNDMANAGER->play("editorbgm", 10.0f);

	_background.Init();
	_background.renderer->Init("background");
	_background.transform->SetPosition(MAPWIDTH / 2, MAPHEIGHT / 2);

	char str[128];
	/*string inputFileName;*/

	/*scanf()
	sprintf_s(str, "%c.map")*/


	_mapTool.AddComponent(new MapTool());
	_mapTool.GetComponent<MapTool>()->Init();

	return S_OK;
}

void MapScene::Update()
{
	//_background.Update();
	_mapTool.Update();
}

void MapScene::Render()
{
	//_background.Render();
	_mapTool.Render();
	MainCam->Render();
}

void MapScene::Release()
{
}
