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
	/* Menu Board RECT �浹ó�� */
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

	/* SETTING ���� �Ҹ����� ������ ���콺 �浹�� ���� ��� */
	if (Vector2InRect(&_settingRect, &_ptMouse))
	{
		_choiceSoundSettingButton = true;
	}		
	else
	{
		_choiceSoundSettingButton = false;
	}

	/* SETTING ���� �ڷΰ��� ������ ���콺 �浹�� ���� ��� */
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
	*	Render ���� ���� ����!
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

	/* �޴��� ����� �� ���ȭ�� & �ΰ� ���İ� ���� */
	AlphaManager();

	/* SETTING ������ �� �̹��� ��� */
	if (_inSetting)
	{
		_settingTitleImg.Render();
		_settingMenuBoardImg.Render();
		_goBackIdleImg.Render();
	}

	/* Intro ������ �� �̹��� ��� */
	if (_inInfo)
	{
		_goBackIdleImg.Render();
	}

	if (_inSetting)
	{
		_goBackIdleImg.Render();
	}

	/* SETTING ���¿� [�Ҹ�] ��ó�� ���콺�� ���� ��� */
	if (_inSetting && _choiceSoundSettingButton)
	{
		_settingMenuChoiceImg.Render();
	}

	/* SETTING Ȥ�� Info ���¿��� [�ڷΰ���] ��ó�� ���콺�� ���� ��� */
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
	/* BOOL ���� */
	_grab = false;
	_inInfo = false;
	_inSetting = false;
	_alphaTrigger = false;
	_choiceSoundSettingButton = false;
	_grab = false;

	/* �ֻ�� Ȳ�ݻ� ���� �κ� */
	_settingTitleImg.renderer->Init("settingtitle");
	_settingTitleImg.transform->SetPosition(BACKGROUND_WIDTH / 2, 20);

	/* ���� �޴� ���� �κ� */
	_settingMenuBoardImg.renderer->Init("settingmenuboard");
	_settingMenuBoardImg.transform->SetPosition(BACKGROUND_WIDTH / 2, BACKGROUND_HEIGHT / 2);

	/* �Ҹ��� ���콺 Ŀ���� �÷��� �� ȸ���ڽ��� ������ �κ�*/
	_settingMenuChoiceImg.renderer->Init("choice2");
	_settingMenuChoiceImg.transform->SetPosition(BACKGROUND_WIDTH / 2, BACKGROUND_HEIGHT / 2);

	/* �ڷΰ��� �κ� */
	_goBackIdleImg.renderer->Init("gobackidle");
	_goBackIdleImg.transform->SetPosition(BACKGROUND_WIDTH / 2, BACKGROUND_HEIGHT - 70);
	_goBackChoiceImg.renderer->Init("gobackchoice");
	_goBackChoiceImg.transform->SetPosition(BACKGROUND_WIDTH / 2, BACKGROUND_HEIGHT - 70);
}

void TitleScene::MakeRect()
{
	/* Menu Board RECT ���� */
	for (int i = 0; i < 5; i++)
	{
		_menuRect[i] = RectMakeCenter(Vector2(WINSIZEX / 2 - 440, BACKGROUND_HEIGHT / 2 - 200 + 100 * i), Vector2(250, 100));
	}

	/* SETTING RECT ���� (�Ҹ� & �ڷΰ���) */
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
	D2DRENDERER->RenderText(WINSIZEX / 2 - 400, BACKGROUND_HEIGHT / 2 - 220, L"�÷���", 25, L"fontello", D2DRenderer::DefaultBrush::White);
	D2DRENDERER->RenderText(WINSIZEX / 2 - 400, BACKGROUND_HEIGHT / 2 - 120, L"������", 25, L"fontello", D2DRenderer::DefaultBrush::White);
	D2DRENDERER->RenderText(WINSIZEX / 2 - 390, BACKGROUND_HEIGHT / 2 - 15, L"����", 25, L"fontello", D2DRenderer::DefaultBrush::White);
	D2DRENDERER->RenderText(WINSIZEX / 2 - 390, BACKGROUND_HEIGHT / 2 + 85, L"����", 25, L"fontello", D2DRenderer::DefaultBrush::White);
	D2DRENDERER->RenderText(WINSIZEX / 2 - 400, BACKGROUND_HEIGHT / 2 + 185, L"������", 25, L"fontello", D2DRenderer::DefaultBrush::White);

	/* SETTING ������ �� ���� ���  */
	if (_inSetting)
	{
		D2DRENDERER->RenderText(WINSIZEX / 2 - 20, BACKGROUND_HEIGHT / 2 - 15, L"�Ҹ�", 20, L"fontello", D2DRenderer::DefaultBrush::White);
	}

	/* SETTING ������ �� ���� ���  */
	if (_inInfo)
	{
		// Color INFO
		// White = 0, Black, Yellow, Red, Blue, Green, Gray, End
		D2DRENDERER->RenderText(WINSIZEX / 2 - 200, BACKGROUND_HEIGHT / 2 - 220, L"�� FILO (FIRST IN LAST OUT)", 30, L"fontello", D2DRenderer::DefaultBrush::Red);
		D2DRENDERER->RenderText(WINSIZEX / 2 - 200, BACKGROUND_HEIGHT / 2 - 170, L"������ : �̽ÿ�, ȫ�뿵, �ڱ�ö, ������, ������", 25, L"fontello", D2DRenderer::DefaultBrush::White);

		D2DRENDERER->RenderText(WINSIZEX / 2 - 200, BACKGROUND_HEIGHT / 2 - 70, L"���� ����", 30, L"fontello", D2DRenderer::DefaultBrush::Red);
		D2DRENDERER->RenderText(WINSIZEX / 2 - 200, BACKGROUND_HEIGHT / 2 - 20, L"�̽ÿ� : ��Ʈ��, Ÿ��Ʋ UI, ����, �̴ϸ�, SAVE&LOAD, �ھ� DB, �ִϸ��̼� ��", 25, L"fontello", D2DRenderer::DefaultBrush::White);
		D2DRENDERER->RenderText(WINSIZEX / 2 - 200, BACKGROUND_HEIGHT / 2 + 30, L"ȫ�뿵 : �����ӿ�ũ, ���๰, ���๰ UI", 25, L"fontello", D2DRenderer::DefaultBrush::White);
		D2DRENDERER->RenderText(WINSIZEX / 2 - 200, BACKGROUND_HEIGHT / 2 + 80, L"�ڱ�ö : �÷��̾�, �÷��̾� UI", 25, L"fontello", D2DRenderer::DefaultBrush::White);
		D2DRENDERER->RenderText(WINSIZEX / 2 - 200, BACKGROUND_HEIGHT / 2 + 130, L"������ : Ÿ�ϸ�, Ÿ�ϸ� UI", 25, L"fontello", D2DRenderer::DefaultBrush::White);
		D2DRENDERER->RenderText(WINSIZEX / 2 - 200, BACKGROUND_HEIGHT / 2 + 180, L"������ : ��, �� �Ѿ�, �� AI, �� UI", 25, L"fontello", D2DRenderer::DefaultBrush::White);
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
		/* enemyPlane ���� */
		_enemyPlane[i] = new GameObject();
		_enemyPlane[i]->AddComponent(new Renderer());
		_enemyPlane[i]->GetComponent<Renderer>()->Init("antumbra");
		_enemyPlane[i]->transform->SetScale(0.2, 0.2);
		_enemyPlane[i]->transform->SetAngle(45.f);
		_enemyPlane[i]->SetActive(false);

		/* enemyPlaneShadow ���� */
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
			float rndY = BACKGROUND_HEIGHT + rndX; /* rndY�� 1�� �Լ� ���� */

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

		/* speed ��ŭ �̵� */
		float speed = 300.f * TIMEMANAGER->getElapsedTime();
		_enemyPlane[i]->transform->Move(speed, -speed);
		
		/* �� ������ ������� */
		if (_enemyPlane[i]->transform->GetX() >= BACKGROUND_WIDTH + 40)
		{
			_enemyPlane[i]->SetActive(false);
			_enemyPlaneShadow[i]->SetActive(false);
		}
	}
}
