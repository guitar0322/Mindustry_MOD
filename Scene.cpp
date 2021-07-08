#include "stdafx.h"
#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

HRESULT Scene::Init()
{
    if(mainCam == nullptr)
        mainCam = new Cam();
    mainCam->Init();
    CAMERAMANAGER->SetMainCam(mainCam->camera);
    return S_OK;
}


void Scene::Release()
{
    NEW_SAFE_RELEASE(mainCam);
}

void Scene::Update()
{
}

void Scene::Render()
{
}

void Scene::SetBackBufferSize(int width, int height)
{
    D2DRENDERER->CreateNewBackBuffer(width, height);
}

void Scene::ChangeMainCam(Cam* newCam)
{
    NEW_SAFE_RELEASE(mainCam);
    mainCam = newCam;
}
