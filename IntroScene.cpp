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
    /* Scene Init �� BuffseSize ���� */
    Scene::Init();
    SetBackBufferSize(1920, 1050);

    /* currentCount �ʱ�ȭ �� ī�޶� ���� */
    currentCount = 0;
    MainCam->SetRenderSize(1920, 1050);
    MainCam->transform->SetX(1920 / 2);
    MainCam->transform->SetY(1050 / 2);

    /* �ݺ����� �̿��Ͽ� ������ �ҷ��´�. */
    for (int i = 0; i < 80; i++)
    {
        char fileName[128];
        char clipName[32];
        sprintf_s(clipName, "introimg%d", i + 1);
        sprintf_s(fileName, "sprites/intro/%d.png", i + 1);
        CLIPMANAGER->AddClip(clipName, fileName, 1920, 1050);
    }

    /* �ʱ� �̹��� ���� �� ��ġ ���� */
    introImg.renderer->Init("introimg1");
    introImg.transform->SetPosition(1920 / 2, 1050 / 2);

    /* Thread ���� */
	CreateThread(NULL, NULL, threadFunction, this, NULL, NULL);
    return S_OK;
}

void IntroScene::Update()
{
    /* Tilte Scene ��ȯ */
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

        /* �ӵ��� ���� ���� */
        Sleep(50);
        
        IntroLoadingHelper->currentCount++;
        sprintf_s(clipName, "introimg%d", IntroLoadingHelper->currentCount);
        IntroLoadingHelper->introImg.renderer->Init(clipName);
    }
    return 0;
}