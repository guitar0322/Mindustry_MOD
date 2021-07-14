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
	
	/* Title Clip Img */
	ClipManager();

	SetBackBufferSize(1125, 875);

	/* Render & Setposition */
	RenderAndPositionManager();

	/* Rect Make */
	MakeRect();

	/* in Title Scene Enemy Fly~ */
	SetTitleSceneEnemy();

	return S_OK;
}

void TitleScene::Update()
{
	/* Menu Board RECT 충돌처리 */
	for (int i = 0; i < 5; i++)
	{
		if (Vector2InRect(&_menuRect[i], &_ptMouse))
		{
			/* SHUNG 21.07.13 */
			if (i == 0 && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				SCENEMANAGER->LoadScene("game");
			}
			else if (i == 1 && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				SCENEMANAGER->LoadScene("background");
			}
			else if (i == 2 && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (_grab) continue;

				_grab = true;
				_inSetting = true;
				_alphaTrigger = true;
			}
			else if (i == 3 && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (_grab) continue;

				_grab = true;
				_inInfo = true;
				_alphaTrigger = true;
			}
			else if (i == 4 && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				PostQuitMessage(0);
				break;
			}
			_choiceImg.SetActive(true);
			_choiceImg.transform->SetPosition(GetCenter(_menuRect[i]));
			break;
		}
		else
		{
			_choiceImg.SetActive(false);
		}
	}

	/* SETTING 에서 소리문구 구역에 마우스 충돌이 있을 경우 */
	if (Vector2InRect(&_settingRect, &_ptMouse))
	{
		_choiceSoundSettingButton = true;
	}		
	else
	{
		_choiceSoundSettingButton = false;
	}

	/* SETTING 에서 뒤로가기 구역에 마우스 충돌이 있을 경우 */
	if (Vector2InRect(&_goBackRect, &_ptMouse))
	{
		_choiceGoBackButton = true;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_grab = false;
			_inInfo = false;
			_inSetting = false;
			_alphaTrigger = false;
		}
	}
	else
	{
		_choiceGoBackButton = false;
	}

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
	_playButtonImg.Render();
	_editorButtonImg.Render();
	_settingButtonImg.Render();
	_abuotButtonImg.Render();
	_exitButtonImg.Render();

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
	if (_inSetting)
	{
		_settingTitleImg.Render();
		_settingMenuBoardImg.Render();
		_goBackIdleImg.Render();
	}

	/* Intro 상태일 때 이미지 출력 */
	if (_inInfo)
	{
		_goBackIdleImg.Render();
	}

	if (_inSetting)
	{
		_goBackIdleImg.Render();
	}

	/* SETTING 상태와 [소리] 근처에 마우스가 있을 경우 */
	if (_inSetting && _choiceSoundSettingButton)
	{
		_settingMenuChoiceImg.Render();
	}

	/* SETTING 혹은 Info 상태에서 [뒤로가기] 근처에 마우스가 있을 경우 */
	if ((_inSetting && _choiceGoBackButton) || (_inInfo && _choiceGoBackButton))
	{
		_goBackChoiceImg.Render();
	}

	/* CAMERA */
	MainCam->Render();

	/* D2D Render */
	D2DRendererManager();
}

void TitleScene::Release()
{
}

void TitleScene::ClipManager()
{
	/* BACKGROUND */
	CLIPMANAGER->AddClip("background", "sprites/title/background.png", 1125, 875);

	/* LOGO */
	CLIPMANAGER->AddClip("logo", "sprites/title/logo.png", 768, 107);

	/* ICON */
	CLIPMANAGER->AddClip("play", "sprites/title/play.png", 30, 30);
	CLIPMANAGER->AddClip("editor", "sprites/title/editor.png", 42, 42);
	CLIPMANAGER->AddClip("settings", "sprites/title/settings.png", 42, 42);
	CLIPMANAGER->AddClip("about", "sprites/title/about.png", 42, 42);
	CLIPMANAGER->AddClip("exit", "sprites/title/exit.png", 42, 42);

	/* Menu Board */
	CLIPMANAGER->AddClip("board", "sprites/title/board.png", 480, 3000);
	CLIPMANAGER->AddClip("choice", "sprites/title/choice.png", 250, 100);

	/* Setting Img */
	CLIPMANAGER->AddClip("settingtitle", "sprites/title/settingword.png", 957, 30);
	CLIPMANAGER->AddClip("settingmenuboard", "sprites/title/settingmenu.png", 324, 68);
	CLIPMANAGER->AddClip("choice2", "sprites/title/choice2.png", 300, 45);
	CLIPMANAGER->AddClip("gobackidle", "sprites/title/gobackidle.png", 210, 64);
	CLIPMANAGER->AddClip("gobackchoice", "sprites/title/gobackchoice.png", 210, 64);
}

void TitleScene::RenderAndPositionManager()
{
	/* BACKGROUND */
	_backgroundImg.renderer->Init("background");
	_backgroundImg.transform->SetPosition(BACKGROUND_WIDTH / 2, BACKGROUND_HEIGHT / 2);

	/* LOGO */
	_logoImg.renderer->Init("logo");
	_logoImg.transform->SetPosition(BACKGROUND_WIDTH / 2, BACKGROUND_HEIGHT / 2 - 365);

	/* ICON */
	_playButtonImg.renderer->Init("play");
	_playButtonImg.transform->SetPosition(BACKGROUND_WIDTH / 2 - 400, BACKGROUND_HEIGHT / 2 - 200);
	_editorButtonImg.renderer->Init("editor");
	_editorButtonImg.transform->SetPosition(BACKGROUND_WIDTH / 2 - 400, BACKGROUND_HEIGHT / 2 - 100);
	_settingButtonImg.renderer->Init("settings");
	_settingButtonImg.transform->SetPosition(BACKGROUND_WIDTH / 2 - 400, BACKGROUND_HEIGHT / 2);
	_abuotButtonImg.renderer->Init("about");
	_abuotButtonImg.transform->SetPosition(BACKGROUND_WIDTH / 2 - 400, BACKGROUND_HEIGHT / 2 + 100);
	_exitButtonImg.renderer->Init("exit");
	_exitButtonImg.transform->SetPosition(BACKGROUND_WIDTH / 2 - 400, BACKGROUND_HEIGHT / 2 + 200);

	/* Menu Board */
	_boardImg.renderer->Init("board");
	_boardImg.transform->SetPosition(BACKGROUND_WIDTH / 2 - 323, 0);
	_choiceImg.renderer->Init("choice");
	_choiceImg.transform->SetPosition(300, 300);

	/* SETTING IMG */
	/* BOOL 변수 */
	_grab = false;
	_inInfo = false;
	_inSetting = false;
	_alphaTrigger = false;
	_choiceSoundSettingButton = false;
	_grab = false;

	/* 최상단 황금색 설정 부분 */
	_settingTitleImg.renderer->Init("settingtitle");
	_settingTitleImg.transform->SetPosition(BACKGROUND_WIDTH / 2, 20);

	/* 세팅 메뉴 보드 부분 */
	_settingMenuBoardImg.renderer->Init("settingmenuboard");
	_settingMenuBoardImg.transform->SetPosition(BACKGROUND_WIDTH / 2, BACKGROUND_HEIGHT / 2);

	/* 소리에 마우스 커서를 올렸을 때 회색박스가 나오는 부분*/
	_settingMenuChoiceImg.renderer->Init("choice2");
	_settingMenuChoiceImg.transform->SetPosition(BACKGROUND_WIDTH / 2, BACKGROUND_HEIGHT / 2);

	/* 뒤로가기 부분 */
	_goBackIdleImg.renderer->Init("gobackidle");
	_goBackIdleImg.transform->SetPosition(BACKGROUND_WIDTH / 2, BACKGROUND_HEIGHT - 70);
	_goBackChoiceImg.renderer->Init("gobackchoice");
	_goBackChoiceImg.transform->SetPosition(BACKGROUND_WIDTH / 2, BACKGROUND_HEIGHT - 70);
}

void TitleScene::MakeRect()
{
	/* Menu Board RECT 생성 */
	for (int i = 0; i < 5; i++)
	{
		_menuRect[i] = RectMakeCenter(Vector2(WINSIZEX / 2 - 440, BACKGROUND_HEIGHT / 2 - 200 + 100 * i), Vector2(250, 100));
	}

	/* SETTING RECT 생성 (소리 & 뒤로가기) */
	_settingRect = RectMakeCenter(Vector2(WINSIZEX / 2, BACKGROUND_HEIGHT / 2), Vector2(250, 100));
	_goBackRect = RectMakeCenter(Vector2(BACKGROUND_WIDTH / 2 + 100, BACKGROUND_HEIGHT - 70), Vector2(250, 100));
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
		// Color INFO
		// White = 0, Black, Yellow, Red, Blue, Green, Gray, End
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
