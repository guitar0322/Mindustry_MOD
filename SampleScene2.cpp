#include "stdafx.h"
#include "SampleScene2.h"

HRESULT SampleScene2::Init()
{
    Scene::Init();
    CLIPMANAGER->AddClip("scene2_background", "scene2_background.png", 2430, 950);
    SetBackBufferSize(2430, 950);
    background.Init();
    background.renderer->Init("scene2_background");
    background.transform->SetPosition(MAPWIDTH / 2, MAPHEIGHT / 2);
    return S_OK;
}

void SampleScene2::Update()
{
    background.Update();
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		MainCam->transform->MoveX(5.f);
	}
	else if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		MainCam->transform->MoveX(-5.f);
	}
	else if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		MainCam->transform->MoveY(-5.f);
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		MainCam->transform->MoveY(5.f);
	}
}

void SampleScene2::Render()
{
    background.Render();
    MainCam->Render();
}

void SampleScene2::Release()
{
}
