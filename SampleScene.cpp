#include "stdafx.h"
#include "SampleScene.h"

HRESULT SampleScene::Init()
{
	/* 필수 */
    Scene::Init();

	//CLIPMANAGER->AddClip("bomb", "bomb.png", 240, 80, 3, 1, 0.12f);
	//CLIPMANAGER->AddClip("trapobject", "trapObject.png", 64, 128);
	CLIPMANAGER->AddClip("title_scene_background", "resource/title/title_background.png", 1125, 875);
	//CLIPMANAGER->AddClip("title_scene_logo", "resource/title/title_logo.png", 768, 107);
	//CLIPMANAGER->AddClip("title_scene_logo", "resource/img/title/title_play_button.png", 14, 14);
	//CLIPMANAGER->AddClip("title_scene_logo", "resource/img/title/title_terrain_button.png", 12, 12);
	//CLIPMANAGER->AddClip("title_scene_logo", "resource/img/title/title_settings_button.png", 10, 10);
	//CLIPMANAGER->AddClip("title_scene_logo", "resource/img/title/title_exit_button.png", 14, 14);

	/* 필수 */
	SetBackBufferSize(1125, 875);

	//testAnimObj.Init();
	//testAnimObj.renderer->Init("bomb");
	//testAnimObj.animator->AddClip(CLIPMANAGER->FindClip("bomb"));
	//testAnimObj.animator->SetClip("bomb");
	//testAnimObj.transform->SetScale(2.f, 2.f);
	//testAnimObj.transform->SetAngle(45.f);
	//testAnimObj.AddComponent(new BoxCollider());
	//testAnimObj.GetComponent<BoxCollider>()->Init();
	//testAnimObj.GetComponent<BoxCollider>()->SetSize(30.f, 30.f);

	//testAnimObj2.Init();
	//testAnimObj2.transform->SetPosition(100, 100);
	//testAnimObj2.renderer->Init("bomb");
	//testAnimObj2.animator->AddClip(CLIPMANAGER->FindClip("bomb"));
	//testAnimObj2.animator->SetClip("bomb");
	//testAnimObj2.transform->SetScale(1.f, 1.f);
	//testAnimObj2.transform->SetAngle(270.f);

	//testUIObj.Init();
	//testUIObj.uiRenderer->Init("trapobject");
	//testUIObj.transform->SetPosition(100, 100);

	_background.Init();
	_background.renderer->Init("title_scene_background");
	_background.transform->SetPosition(MAPWIDTH / 2, MAPHEIGHT / 2);

	_logo.Init();
	_logo.renderer->Init("title_scene_logo");
	_logo.transform->SetPosition(MAPWIDTH / 2 - 100, 100);

	//_sceneChangeTime = 0;
    return S_OK;
}

void SampleScene::Update()
{
	_background.Update();
	_logo.Update();

	//testAnimObj.Update();
	//testAnimObj2.Update();
	//testUIObj.Update();
	//if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	//{
	//	//MainCam->transform->MoveX(5.f);
	//	testAnimObj.transform->MoveX(5.f);
	//}
	//else if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	//{
	//	//MainCam->transform->MoveX(-5.f);
	//	testAnimObj.transform->MoveX(-5.f);
	//}
	//else if (KEYMANAGER->isStayKeyDown(VK_UP))
	//{
	//	//MainCam->transform->MoveY(-5.f);
	//	testAnimObj.transform->MoveY(-5.f);
	//}
	//else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	//{
	//	//MainCam->transform->MoveY(5.f);
	//	testAnimObj.transform->MoveY(5.f);
	//}
	//_sceneChangeTime += TIMEMANAGER->getElapsedTime();
	//if (_sceneChangeTime >= 5.f)
	//{
	//	//SCENEMANAGER->LoadScene("sample2");
	//}
}

void SampleScene::Render()
{
    {
		//Rect rect;
		//rect = RectMakePivot(Vector2(WINSIZEX + 500, WINSIZEY / 2),
		//	Vector2(50, 50), Pivot::Center);

		//D2DRenderer::GetInstance()->DrawRectangle
		//(
		//	rect,
		//	D2DRenderer::DefaultBrush::Red,
		//	1.f
		//);
		_background.Render();
		//testAnimObj.Render();
		//testAnimObj2.Render();
		MainCam->Render();
		D2DRENDERER->RenderText(250, 400, L"다람쥐 헌 쳇바퀴에 타고파", 50);
		//D2DRENDERER->RenderText(700, 400, L"테스트 텍스트", 20, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_CENTER,
		//	L"BMHANNAPro");
		D2DRENDERER->RenderTextField(400, 400, L"다람쥐 헌 쳇바퀴에 타고파", D2D1::ColorF::Black, 50, 500, 200, 
			1.f,
			DWRITE_TEXT_ALIGNMENT_LEADING, L"배달의민족 한나체 Pro");
		//testUIObj.Render();
		_logo.Render();
    }
}

void SampleScene::Release()
{
}
