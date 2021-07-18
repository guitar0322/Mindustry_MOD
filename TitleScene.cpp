#include "stdafx.h"
#include "TitleScene.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

HRESULT TitleScene::Init()
{
	Scene::Init();
	
	titleUIControler = new TitleUIControler();
	titleUIControler->choiceImg = &_choiceImg;
	titleUIControler->choiceImg2 = &_choiceImg2;

	titleUIControler->goBackChoiceImg = &_goBackIdleImg;
	titleUIControler->goBackChoiceImg = &_goBackChoiceImg;
	
	ClipManager();						/* Title Clip Img */
	SetBackBufferSize(1125, 875);
	Render_SetPosition_MouseEvent(); 	/* Render & Setposition */
	SetTitleSceneEnemy();				/* in Title Scene Enemy Fly~ */

	return S_OK;
}

void TitleScene::Update()
{
	MainCam->Update();
	for (int i = 0; i < ENEMY_PLANE_MAX; i++)
	{
		_enemyPlane[i]->Update();
		_enemyPlaneShadow[i]->Update();
	}
	/* Buuton Update */
	_playButton.Update();
	_ediotrButton.Update();
	_settingButton.Update();
	_aboutButton.Update();
	_exitButton.Update();
	_goBackButton.Update();
	_soundButton.Update();

	/* Enemy Update */
	EnemyMove();
}

void TitleScene::Render()
{	
	/*
	*	Render 순서 변경 금지!
	*/

	/* BACKGROUND */
	_backgroundImg.Render();

	/* ICON */
	_choiceImg.Render();
	_playIconImg.Render();
	_editorIconImg.Render();
	_settingIconImg.Render();
	_abuotIconImg.Render();
	_exitIconImg.Render();

	/* Enemy Render */
	for (int i = 0; i < ENEMY_PLANE_MAX; i++)
	{
		_enemyPlane[i]->Render();
		_enemyPlaneShadow[i]->Render();
	}

	/* Menu Board */
	_boardImg.Render();

	/* LOGO */
	_logoImg.Render();

	/* 메뉴를 골랐을 때 배경화면 & 로고 알파값 조절 */
	AlphaManager();

	/* SETTING 상태일 때 이미지 출력 */
	_settingTitleImg.Render();
	_settingMenuBoardImg.Render();
	_goBackIdleImg.Render();
	_goBackChoiceImg.Render();
	_choiceImg2.Render();

	/* Camera */
	MainCam->Render();

	/* Button Render */
	_playButton.Render();
	_ediotrButton.Render();
	_settingButton.Render();
	_aboutButton.Render();
	_exitButton.Render();
	_goBackButton.Render();
	_soundButton.Render();
	
	/* D2D Render */
	D2DRendererManager();
}

void TitleScene::Release()
{
}

void TitleScene::ClipManager()
{
	/* Background Img */
	CLIPMANAGER->AddClip("background", "sprites/title/background.png", 1125, 875);

	/* Logo Img */
	CLIPMANAGER->AddClip("logo", "sprites/title/logo.png", 768, 107);

	/* Icon Img */
	CLIPMANAGER->AddClip("play", "sprites/title/play.png", 30, 30);
	CLIPMANAGER->AddClip("editor", "sprites/title/editor.png", 42, 42);
	CLIPMANAGER->AddClip("settings", "sprites/title/settings.png", 42, 42);
	CLIPMANAGER->AddClip("about", "sprites/title/about.png", 42, 42);
	CLIPMANAGER->AddClip("title_exit", "sprites/title/exit.png", 42, 42);

	/* Menu Board Img */
	CLIPMANAGER->AddClip("board", "sprites/title/board.png", 480, 3000);
	CLIPMANAGER->AddClip("choice", "sprites/title/choice.png", 250, 100);

	/* Setting Img */
	CLIPMANAGER->AddClip("settingtitle", "sprites/title/settingword.png", 957, 30);
	CLIPMANAGER->AddClip("settingmenuboard", "sprites/title/settingmenu.png", 324, 68);
	CLIPMANAGER->AddClip("choice2", "sprites/title/choice2.png", 300, 45);
	CLIPMANAGER->AddClip("gobackidle", "sprites/title/gobackidle.png", 210, 64);
	CLIPMANAGER->AddClip("gobackchoice", "sprites/title/gobackchoice.png", 210, 64);
}

void TitleScene::Render_SetPosition_MouseEvent()
{
	#pragma region Background

	_backgroundImg.renderer->Init("background");
	_backgroundImg.transform->SetPosition(BACKGROUND_WIDTH / 2, BACKGROUND_HEIGHT / 2);
	
	#pragma endregion

	#pragma region Logo
	
	_logoImg.renderer->Init("logo");
	_logoImg.transform->SetPosition(BACKGROUND_WIDTH / 2, BACKGROUND_HEIGHT / 2 - 365);

	#pragma endregion

	#pragma region Play Icon & Button

	_playIconImg.renderer->Init("play");
	_playIconImg.transform->SetPosition(BACKGROUND_WIDTH / 2 - 400, BACKGROUND_HEIGHT / 2 - 200);
	
	_playButton.Init();
	_playButton.uiRenderer->Init(300, 75);
	_playButton.transform->SetPosition(WINSIZEX / 2 - 390, BACKGROUND_HEIGHT / 2 - 200);

	_playButton.uiMouseEvent->RegistCallback(
		std::bind(&TitleUIControler::ActiveChoiceImg, titleUIControler, _playButton.transform, true), EVENT::ENTER);
	_playButton.uiMouseEvent->RegistCallback(
		std::bind(&TitleUIControler::ChaneScene, titleUIControler, "game"), EVENT::CLICK);
	_playButton.uiMouseEvent->RegistCallback(
		std::bind(&TitleUIControler::ActiveChoiceImg, titleUIControler, _playButton.transform, false), EVENT::EXIT);
	
	#pragma endregion

	#pragma region Editor Icon & Button

	_editorIconImg.renderer->Init("editor");
	_editorIconImg.transform->SetPosition(BACKGROUND_WIDTH / 2 - 400, BACKGROUND_HEIGHT / 2 - 100);

	_ediotrButton.Init();
	_ediotrButton.uiRenderer->Init(300, 75);
	_ediotrButton.transform->SetPosition(WINSIZEX / 2 - 390, BACKGROUND_HEIGHT / 2 - 200 + 100 * 1);

	_ediotrButton.uiMouseEvent->RegistCallback(
		std::bind(&TitleUIControler::ActiveChoiceImg, titleUIControler, _ediotrButton.transform, true), EVENT::ENTER);
	_ediotrButton.uiMouseEvent->RegistCallback(
		std::bind(&TitleUIControler::ChaneScene, titleUIControler, "background"), EVENT::CLICK);
	_ediotrButton.uiMouseEvent->RegistCallback(
		std::bind(&TitleUIControler::ActiveChoiceImg, titleUIControler, _ediotrButton.transform, false), EVENT::EXIT);

	#pragma endregion

	#pragma region Setting Icon & Button, Sound Button

	_settingIconImg.renderer->Init("settings");
	_settingIconImg.transform->SetPosition(BACKGROUND_WIDTH / 2 - 400, BACKGROUND_HEIGHT / 2);

	_settingButton.Init();
	_settingButton.uiRenderer->Init(300, 75);
	_settingButton.transform->SetPosition(WINSIZEX / 2 - 390, BACKGROUND_HEIGHT / 2 - 200 + 100 * 2);

	_settingButton.uiMouseEvent->RegistCallback(
		std::bind(&TitleUIControler::ActiveChoiceImg, titleUIControler, _settingButton.transform, true), EVENT::ENTER);
	vector<GameObject*> activeTarget;
	activeTarget.push_back(&_settingTitleImg);
	activeTarget.push_back(&_settingMenuBoardImg);
	activeTarget.push_back(&_soundButton);
	activeTarget.push_back(&_goBackIdleImg);
	_settingButton.uiMouseEvent->RegistCallback(
		std::bind(&TitleUIControler::SetActiveCallback2, titleUIControler, activeTarget, &_inSetting, &_alphaTrigger, true), EVENT::CLICK);
	_settingButton.uiMouseEvent->RegistCallback(
		std::bind(&TitleUIControler::ActiveChoiceImg, titleUIControler, _settingButton.transform, false), EVENT::EXIT);

	_soundButton.Init();
	_soundButton.uiRenderer->Init(350, 60);
	_soundButton.transform->SetPosition(WINSIZEX / 2, BACKGROUND_HEIGHT / 2);

	_soundButton.uiMouseEvent->RegistCallback(
		std::bind(&TitleUIControler::ActiveChoiceImg2, titleUIControler, _soundButton.transform, true), EVENT::ENTER);
	vector<GameObject*> activeTarget4;
	activeTarget4.push_back(&_settingMenuBoardImg);
	activeTarget4.push_back(&_choiceImg2);
	activeTarget4.push_back(&_soundButton);
	_soundButton.uiMouseEvent->RegistCallback(
		std::bind(&TitleUIControler::SetActiveCallback, titleUIControler, activeTarget4, &_inSetting, false), EVENT::CLICK);
	_soundButton.uiMouseEvent->RegistCallback(
		std::bind(&TitleUIControler::ActiveChoiceImg2, titleUIControler, _soundButton.transform, false), EVENT::EXIT);
	
	#pragma endregion

	#pragma region About Icon & Button 

	_abuotIconImg.renderer->Init("about");
	_abuotIconImg.transform->SetPosition(BACKGROUND_WIDTH / 2 - 400, BACKGROUND_HEIGHT / 2 + 100);

	_aboutButton.Init();
	_aboutButton.uiRenderer->Init(300, 75);
	_aboutButton.transform->SetPosition(WINSIZEX / 2 - 390, BACKGROUND_HEIGHT / 2 - 200 + 100 * 3);

	_aboutButton.uiMouseEvent->RegistCallback(
		std::bind(&TitleUIControler::ActiveChoiceImg, titleUIControler, _aboutButton.transform, true), EVENT::ENTER);
	vector<GameObject*> activeTarget2;
	activeTarget2.push_back(&_goBackIdleImg);
	_aboutButton.uiMouseEvent->RegistCallback(
		std::bind(&TitleUIControler::SetActiveCallback2, titleUIControler, activeTarget2, &_inInfo, &_alphaTrigger, true), EVENT::CLICK);
	_aboutButton.uiMouseEvent->RegistCallback(
		std::bind(&TitleUIControler::ActiveChoiceImg, titleUIControler, _aboutButton.transform, false), EVENT::EXIT);

	#pragma endregion

	#pragma region Exit Icon & Button 

	_exitIconImg.renderer->Init("title_exit");
	_exitIconImg.transform->SetPosition(BACKGROUND_WIDTH / 2 - 400, BACKGROUND_HEIGHT / 2 + 200);

	_exitButton.Init();
	_exitButton.uiRenderer->Init(300, 75);
	_exitButton.transform->SetPosition(WINSIZEX / 2 - 390, BACKGROUND_HEIGHT / 2 - 200 + 100 * 4);

	_exitButton.uiMouseEvent->RegistCallback(
		std::bind(&TitleUIControler::ActiveChoiceImg, titleUIControler, _exitButton.transform, true), EVENT::ENTER);
	_exitButton.uiMouseEvent->RegistCallback(
		std::bind(&TitleUIControler::GameExit, titleUIControler), EVENT::CLICK);
	_exitButton.uiMouseEvent->RegistCallback(
		std::bind(&TitleUIControler::ActiveChoiceImg, titleUIControler, _exitButton.transform, false), EVENT::EXIT);

	#pragma endregion

	#pragma region Goback Button

	_goBackIdleImg.renderer->Init("gobackidle");
	_goBackIdleImg.transform->SetPosition(BACKGROUND_WIDTH / 2, BACKGROUND_HEIGHT - 70);
	_goBackIdleImg.SetActive(false);
	_goBackChoiceImg.renderer->Init("gobackchoice");
	_goBackChoiceImg.transform->SetPosition(BACKGROUND_WIDTH / 2, BACKGROUND_HEIGHT - 70);
	_goBackChoiceImg.SetActive(false);

	_goBackButton.Init();
	_goBackButton.uiRenderer->Init(300, 100);
	_goBackButton.transform->SetPosition(BACKGROUND_WIDTH / 2, BACKGROUND_HEIGHT - 70);

	_goBackButton.uiMouseEvent->RegistCallback(
		std::bind(&TitleUIControler::ActiveGoBackImg, titleUIControler, true), EVENT::ENTER);
	vector<GameObject*> activeTarget3;
	activeTarget3.push_back(&_settingTitleImg);
	activeTarget3.push_back(&_settingMenuBoardImg);
	activeTarget3.push_back(&_goBackIdleImg);
	activeTarget3.push_back(&_goBackChoiceImg);
	_goBackButton.uiMouseEvent->RegistCallback(
		std::bind(&TitleUIControler::SetActiveCallback4, titleUIControler, activeTarget3, &_inInfo, &_inSetting, &_alphaTrigger, false), EVENT::CLICK);
	_goBackButton.uiMouseEvent->RegistCallback(
		std::bind(&TitleUIControler::ActiveGoBackImg, titleUIControler, false), EVENT::EXIT);

	#pragma endregion
	
	#pragma region Menu Board & Menu Choice

	_boardImg.renderer->Init("board");
	_boardImg.transform->SetPosition(BACKGROUND_WIDTH / 2 - 323, 0);
	_choiceImg.renderer->Init("choice");
	_choiceImg.SetActive(false);
	_choiceImg2.renderer->Init("choice2");
	_choiceImg2.SetActive(false);

	#pragma endregion

	#pragma region Bool Setting

	_grab = false;
	_inInfo = false;
	_inSetting = false;
	_alphaTrigger = false;
	_choiceSoundSettingButton = false;

	#pragma endregion

	#pragma region inSetting State - Top Setting Word

	_settingTitleImg.renderer->Init("settingtitle");
	_settingTitleImg.transform->SetPosition(BACKGROUND_WIDTH / 2, 20);
	_settingTitleImg.SetActive(false);

	#pragma endregion

	#pragma region inSetting State - Setting Board

	_settingMenuBoardImg.renderer->Init("settingmenuboard");
	_settingMenuBoardImg.transform->SetPosition(BACKGROUND_WIDTH / 2, BACKGROUND_HEIGHT / 2);
	_settingMenuBoardImg.SetActive(false);

	#pragma endregion
}

void TitleScene::AlphaManager()
{
	if (_alphaTrigger)
	{
		_backgroundImg.renderer->SetAlpha(0.5);
		_logoImg.renderer->SetAlpha(0.5);
	}
	else
	{
		_backgroundImg.renderer->SetAlpha(1);
		_logoImg.renderer->SetAlpha(1);
	}
}

void TitleScene::D2DRendererManager()
{
	/* Menu Board Text */
	D2DRENDERER->RenderText(WINSIZEX / 2 - 400, BACKGROUND_HEIGHT / 2 - 220, L"플레이", 25, L"fontello", D2DRenderer::DefaultBrush::White);
	D2DRENDERER->RenderText(WINSIZEX / 2 - 400, BACKGROUND_HEIGHT / 2 - 120, L"편집기", 25, L"fontello", D2DRenderer::DefaultBrush::White);
	D2DRENDERER->RenderText(WINSIZEX / 2 - 390, BACKGROUND_HEIGHT / 2 - 15, L"설정", 25, L"fontello", D2DRenderer::DefaultBrush::White);
	D2DRENDERER->RenderText(WINSIZEX / 2 - 390, BACKGROUND_HEIGHT / 2 + 85, L"정보", 25, L"fontello", D2DRenderer::DefaultBrush::White);
	D2DRENDERER->RenderText(WINSIZEX / 2 - 400, BACKGROUND_HEIGHT / 2 + 185, L"나가기", 25, L"fontello", D2DRenderer::DefaultBrush::White);

	/* SETTING 상태일 때 글자 출력  */
	if (_inSetting)
	{
		D2DRENDERER->RenderText(WINSIZEX / 2 - 20, BACKGROUND_HEIGHT / 2 - 15, L"소리", 20, L"fontello", D2DRenderer::DefaultBrush::White);
	}

	/* SETTING 상태일 때 글자 출력  */
	if (_inInfo)
	{
		// Color INFO (White = 0, Black, Yellow, Red, Blue, Green, Gray, End)
		D2DRENDERER->RenderText(WINSIZEX / 2 - 200, BACKGROUND_HEIGHT / 2 - 220, L"팀 FILO (FIRST IN LAST OUT)", 30, L"fontello", D2DRenderer::DefaultBrush::Red);
		D2DRENDERER->RenderText(WINSIZEX / 2 - 200, BACKGROUND_HEIGHT / 2 - 170, L"제작자 : 이시영, 홍대영, 박광철, 이유림, 조민재", 25, L"fontello", D2DRenderer::DefaultBrush::White);
		D2DRENDERER->RenderText(WINSIZEX / 2 - 200, BACKGROUND_HEIGHT / 2 - 70, L"맡은 역할", 30, L"fontello", D2DRenderer::DefaultBrush::Red);
		D2DRENDERER->RenderText(WINSIZEX / 2 - 200, BACKGROUND_HEIGHT / 2 - 20, L"이시영 : 인트로, 타이틀 UI, 연구, 미니맵, SAVE&LOAD, 코어 DB, 애니메이션 등", 25, L"fontello", D2DRenderer::DefaultBrush::White);
		D2DRENDERER->RenderText(WINSIZEX / 2 - 200, BACKGROUND_HEIGHT / 2 + 30, L"홍대영 : 프레임워크, 건축물, 건축물 UI", 25, L"fontello", D2DRenderer::DefaultBrush::White);
		D2DRENDERER->RenderText(WINSIZEX / 2 - 200, BACKGROUND_HEIGHT / 2 + 80, L"박광철 : 플레이어, 플레이어 UI", 25, L"fontello", D2DRenderer::DefaultBrush::White);
		D2DRENDERER->RenderText(WINSIZEX / 2 - 200, BACKGROUND_HEIGHT / 2 + 130, L"이유림 : 타일맵, 타일맵 UI", 25, L"fontello", D2DRenderer::DefaultBrush::White);
		D2DRENDERER->RenderText(WINSIZEX / 2 - 200, BACKGROUND_HEIGHT / 2 + 180, L"조민재 : 적, 적 총알, 적 AI, 적 UI", 25, L"fontello", D2DRenderer::DefaultBrush::White);
	}
}

void TitleScene::SetTitleSceneEnemy()
{
	_emergencyTime = 0.f;
	_randomSpawnTime = 1.f;

	CLIPMANAGER->AddClip("antumbra", "sprites/antumbra.png", 216, 240);
	CLIPMANAGER->AddClip("antumbra_shadow", "sprites/antumbra-shadow.png", 216, 240);

	for (int i = 0; i < ENEMY_PLANE_MAX; i++)
	{
		/* enemyPlane 생성 */
		_enemyPlane[i] = new GameObject();
		_enemyPlane[i]->AddComponent(new Renderer());
		_enemyPlane[i]->GetComponent<Renderer>()->Init("antumbra");
		_enemyPlane[i]->transform->SetScale(0.2, 0.2);
		_enemyPlane[i]->transform->SetAngle(45.f);
		_enemyPlane[i]->SetActive(false);

		/* enemyPlaneShadow 생성 */
		_enemyPlaneShadow[i] = new ImageObject();
		_enemyPlaneShadow[i]->renderer->Init("antumbra_shadow");
		_enemyPlaneShadow[i]->renderer->SetAlpha(0.6f);
		_enemyPlaneShadow[i]->transform->SetScale(0.2f, 0.2f);
		_enemyPlaneShadow[i]->transform->SetAngle(45.f);
		_enemyPlaneShadow[i]->SetActive(false);

		_enemyPlane[i]->transform->AddChild(_enemyPlaneShadow[i]->transform);
	}
}

void TitleScene::EnemyMove()
{
	_emergencyTime += TIMEMANAGER->getElapsedTime();
	if (_emergencyTime > _randomSpawnTime)
	{
		_emergencyTime = 0;
		for (int i = 0; i < ENEMY_PLANE_MAX; i++)
		{
			if (_enemyPlane[i]->isActive == true) continue;

			float rndX = RND->getFromFloatTo(-400, 400);
			float rndY = BACKGROUND_HEIGHT + rndX; /* rndY에 1차 함수 적용 */

			_enemyPlane[i]->SetActive(true);
			_enemyPlane[i]->transform->SetPosition(rndX, rndY);
			_enemyPlaneShadow[i]->transform->SetPosition(rndX - 40, rndY + 40);
			_enemyPlaneShadow[i]->SetActive(true);
			break;
		}
	}

	for (int i = 0; i < ENEMY_PLANE_MAX; i++)
	{
		if (_enemyPlane[i]->isActive == false) continue;

		/* speed 만큼 이동 */
		float speed = 300.f * TIMEMANAGER->getElapsedTime();
		_enemyPlane[i]->transform->Move(speed, -speed);
		
		/* 맵 밖으로 나갈경우 */
		if (_enemyPlane[i]->transform->GetX() >= BACKGROUND_WIDTH + 40)
		{
			_enemyPlane[i]->SetActive(false);
			_enemyPlaneShadow[i]->SetActive(false);
		}
	}
}
