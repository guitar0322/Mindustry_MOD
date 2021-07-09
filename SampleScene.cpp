#include "stdafx.h"
#include "SampleScene.h"
#include "TriggerTest.h"
HRESULT SampleScene::Init()
{
    Scene::Init();
	CLIPMANAGER->AddClip("bomb", "bomb.png", 240, 80, 3, 1, 0.12f);
	CLIPMANAGER->AddClip("trapobject", "trapObject.png", 64, 128);
	CLIPMANAGER->AddClip("background", "scene1_background.png", 1024, 560);
	_stayTime = 0;
	SetBackBufferSize(1024, 560);
	testAnimObj.Init();
	testAnimObj.renderer->Init("bomb");
	testAnimObj.animator->AddClip(CLIPMANAGER->FindClip("bomb"));
	testAnimObj.animator->SetClip("bomb");
	testAnimObj.transform->SetScale(2.f, 2.f);
	testAnimObj.transform->SetAngle(45.f);
	testAnimObj.AddComponent(new BoxCollider());
	testAnimObj.GetComponent<BoxCollider>()->Init();
	testAnimObj.GetComponent<BoxCollider>()->SetSize(30.f, 30.f);
	testAnimObj.AddComponent(new TriggerTest());
	testAnimObj.GetComponent<TriggerTest>()->Init();
	testAnimObj.GetComponent<TriggerTest>()->testObject = &testUIObj;

	testAnimObj2.Init();
	testAnimObj2.transform->SetPosition(100, 100);
	testAnimObj2.renderer->Init("bomb");
	testAnimObj2.animator->AddClip(CLIPMANAGER->FindClip("bomb"));
	testAnimObj2.animator->SetClip("bomb");
	testAnimObj2.transform->SetScale(1.f, 1.f);
	testAnimObj2.transform->SetAngle(270.f);
	testAnimObj2.AddComponent(new BoxCollider());
	testAnimObj2.GetComponent<BoxCollider>()->Init();
	testAnimObj2.GetComponent<BoxCollider>()->SetSize(30.f, 30.f);

	testUIObj.Init();
	testUIObj.uiRenderer->Init("trapobject");
	testUIObj.transform->SetPosition(100, 100);
	testUIObj.SetActive(false);

	background.Init();
	background.renderer->Init("background");
	background.transform->SetPosition(MAPWIDTH / 2, MAPHEIGHT / 2);

	_sceneChangeTime = 0;
    return S_OK;
}

void SampleScene::Update()
{
	testInt++;
	background.Update();
	testAnimObj.Update();
	testAnimObj2.Update();
	testUIObj.Update();
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		//MainCam->transform->MoveX(5.f);
		testAnimObj.transform->MoveX(5.f);
	}
	else if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		//MainCam->transform->MoveX(-5.f);
		testAnimObj.transform->MoveX(-5.f);
	}
	else if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		//MainCam->transform->MoveY(-5.f);
		testAnimObj.transform->MoveY(-5.f);
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		//MainCam->transform->MoveY(5.f);
		testAnimObj.transform->MoveY(5.f);
	}
	_sceneChangeTime += TIMEMANAGER->getElapsedTime();
	if (_sceneChangeTime >= 5.f)
	{
		//SCENEMANAGER->LoadScene("sample2");
	}
}

void SampleScene::Render()
{
    {
		Rect rect;
		rect = RectMakePivot(Vector2(WINSIZEX + 500, WINSIZEY / 2),
			Vector2(50, 50), Pivot::Center);

		D2DRenderer::GetInstance()->DrawRectangle
		(
			rect,
			D2DRenderer::DefaultBrush::Red,
			1.f
		);
		background.Render();
		testAnimObj.Render();
		testAnimObj2.Render();
		MainCam->Render();
		char debug[128];
		sprintf_s(debug, "%d", testInt);
		std::wstring wstr(debug, &debug[128]);
		D2DRENDERER->RenderText(10, 10, wstr, 20);
		D2DRENDERER->RenderText(250, 400, L"�ٶ��� �� �¹����� Ÿ����", 50);
		//D2DRENDERER->RenderText(700, 400, L"�׽�Ʈ �ؽ�Ʈ", 20, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_CENTER,
		//	L"BMHANNAPro");
		D2DRENDERER->RenderTextField(400, 400, L"�ٶ��� �� �¹����� Ÿ����", D2D1::ColorF::Black, 50, 500, 200, 
			1.f,
			DWRITE_TEXT_ALIGNMENT_LEADING, L"����ǹ��� �ѳ�ü Pro");
		testUIObj.Render();
    }
}

void SampleScene::Release()
{
}