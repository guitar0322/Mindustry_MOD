#include "stdafx.h"
#include "IntroScene.h"

/* SHUNG 21.07.12 */

IntroScene::IntroScene()
{
}

IntroScene::~IntroScene()
{
}

HRESULT IntroScene::Init()
{
    /* Scene Init 및 BuffseSize 조정 */
    Scene::Init();
    SetBackBufferSize(1920, 1050);

    /* currentCount 초기화 및 카메라 세팅 */
    currentCount = 0;
    MainCam->SetRenderSize(1920, 1050);
    MainCam->transform->SetX(1920 / 2);
    MainCam->transform->SetY(1050 / 2);

    /* 반복문을 이용하여 파일을 불러온다. */
    for (int i = 0; i < 80; i++)
    {
        char fileName[128];
        char clipName[32];
        sprintf_s(clipName, "introimg%d", i + 1);
        sprintf_s(fileName, "sprites/intro/%d.png", i + 1);
        CLIPMANAGER->AddClip(clipName, fileName, 1920, 1050);
    }

    /* 초기 이미지 세팅 및 위치 수정 */
    introImg.renderer->Init("introimg1");
    introImg.transform->SetPosition(1920 / 2, 1050 / 2);

    /* Thread 생성 */
	CreateThread(NULL, NULL, threadFunction, this, NULL, NULL);
    return S_OK;
}

void IntroScene::Update()
{
    /* Tilte Scene 전환 */
    if (currentCount == LOADINGMAX)
    {
        SCENEMANAGER->LoadScene("title");
    }
}

void IntroScene::Render()
{
    introImg.Render();
    MainCam->Render();
}

void IntroScene::Release()
{
}

DWORD threadFunction(LPVOID lpParameter)
{
    IntroScene* IntroLoadingHelper = (IntroScene*)lpParameter;

    while (IntroLoadingHelper->currentCount != LOADINGMAX)
    {
        char clipName[32];

        /* 속도는 조절 예정 */
        Sleep(50);
        
        IntroLoadingHelper->currentCount++;
        sprintf_s(clipName, "introimg%d", IntroLoadingHelper->currentCount);
        IntroLoadingHelper->introImg.renderer->Init(clipName);
    }
    return 0;
}