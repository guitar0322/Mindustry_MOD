#include "stdafx.h"
#include "GameScene.h"
#include "UIControler.h"
#include "PropContainer.h"
#include "PlayerControler.h"
#include "PropFactory.h"
#include "UIMouseEvent.h"
#include "EnemyManager.h"
#include "GameInfo.h"
#include <string>
#include "Prop.h"
#include "CameraControler.h"
#include "Item.h"
#include "ResourceManager.h"
#include "Core.h"
#include "CoreComponent.h"
#include "Astar.h"
#include "Respawn.h"
#include "resource.h"

HRESULT GameScene::Init()
{
    Scene::Init();

	InitClip();
	PlayerClip();
	InGameUIClip();

	SetBackBufferSize(1600, 1600);
    COLLIDERMANAGER->PartitionArea(10, 10);
    StaticBuffer->BeginDraw();
	MainCam->SetScreenSize(WINSIZEX, WINSIZEY);
	MainCam->SetRenderSize(1600, 1010);
    MainCam->transform->SetPosition(1600 / 2, 1600 / 2);

    selectCategoryIdx = 0;

    _gameInfo = new GameInfo();
    _gameInfo->Init();
    _gameInfo->AddResource(COPPER, 500);
    // �ڿ��߰� (�ÿ�)
    _gameInfo->AddResource(LEAD, 0);
    _gameInfo->AddResource(SCRAP, 0);

    _propContainer = new PropContainer();
	_propFactory = new PropFactory();
    _propFactory->Init();
	_propFactory->propContainer = _propContainer;
    _propFactory->LinkGameInfo(_gameInfo);

    _resourceManager = new ResourceManager();
    _resourceManager->propContainer = _propContainer;
    _resourceManager->Init();
    _propFactory->LinkResourceManager(_resourceManager);

    _uiControler = new UIControler();
    _uiControler->Init();
    _uiControler->categorySelect = &_categorySelect;
    _uiControler->propSelect = &_propSelect;
    _uiControler->propPreview = &_propPreview;
               
    _uiControler->turretIconV = &_turretIconV;
    _uiControler->drillIconV = &_drillIconV;
    _uiControler->railIconV = &_railIconV;
    _uiControler->wallIconV = &_wallIconV;
    _uiControler->preIconV = &_turretIconV;

    _uiControler->propFactory = _propFactory;
    _uiControler->propContainer = _propContainer;
    _respawn = new Respawn();

	/*===================================*/
	/*�ΰ��� �� �ʱ�ȭ -> ����*/
	_gameMap = new GameMap;
	_gameMap->Init();

    _aStar = new Astar();
    _aStar->LinkGameMap(_gameMap);
    _aStar->LinkPropContainer(_propContainer);

    _uiControler->gameMap = _gameMap;
    _propFactory->LinkGameMap(_gameMap);
	//�ڿ� UI �ʱ�ȭ
	ResourcesInit();
	/*===================================*/

    InitCategoryUI();
    InitPropUI();

    /* �ÿ� */
    // ���� Init
    researchInitUI();
    // �޴� Init
    menuInitUI();

    // BOOL ���� �ʱ�ȭ 
    {
        // Ŀ�� 
        _isMineral = true;

        /* �����κ� */
        _lockDes = false;
        _research = false;
        _inDetail = false;

        _all_Resources_State = true;
        _all_Resources_Count = 1;
        // true = �����ִ� ����
        // false = �����ִ� ����

        /* �޴��κ� */
        _menu = false;
        _menu_ReallyEnd = false;
    }

    // _uiControler �̹��� ����
    {
        _uiControler->isMineral = &_isMineral;
        /* ����ȭ�� ������ ī�װ� �����ܿ� ENTER ���� ��� ������ ȸ�� �̹��� */
        _uiControler->coreDBIcon = &_coreDBIcon;
        _uiControler->researchIcon = &_researchIcon;
        _uiControler->inGame_TouchToIcon = &_inGame_TouchToIcon;

        // ����
        /* ��ü �ڿ� ��ư (ȸ��) */
        _uiControler->all_Resources_Count = _all_Resources_Count;
        _uiControler->all_Resources_Img = &_all_Resources_Img;
        _uiControler->all_Resources_Open1_Img = &_all_Resources_Open1_Img;
        _uiControler->all_Resources_Open2_Img = &_all_Resources_Open2_Img;
        _uiControler->all_Resources_Open3_Img = &_all_Resources_Open3_Img;
        _uiControler->all_Resources_Close_Img = &_all_Resources_Close_Img;
        _uiControler->all_Resources_Text = &_all_Resources_Text;

        /* ? */
        _uiControler->choiceImg = &_choiceImg;
        _uiControler->lockImg = &_lockImg;
        _uiControler->inResearchChoiceImg = &_inResearchChoiceImg;

        /* ���� */
        _uiControler->research_goBackIdleImg = &_research_goBackIdleImg;
        _uiControler->research_goBackChoiceImg = &_research_goBackChoiceImg;
        _uiControler->coreDBIdleImg = &_coreDBIdleImg;
        _uiControler->coreDBChoiceImg = &_coreDBChoiceImg;

        /* �󼼺��� */
        _uiControler->detailDes_GoBackIdleImg = &_detailDes_goBackIdleImg;
        _uiControler->detailDes_GoBackChoiceImg = &_detailDes_goBackChoiceImg;

        /* �޴��κ� */
        _uiControler->menu_GoBackIdleImg = &_menu_GoBackIdleImg;
        _uiControler->menu_GoBackChoiceImg = &_menu_GoBackChoiceImg;
        _uiControler->menu_SettingIdleImg = &_menu_SettingIdleImg;
        _uiControler->menu_SettingChoiceImg = &_menu_SettingChoiceImg;
        _uiControler->menu_SaveAndExitIdleImg = &_menu_SaveAndExitIdleImg;
        _uiControler->menu_SaveAndExitChoiceImg = &_menu_SaveAndExitChoiceImg;
        _uiControler->menu_SaveAndExitButton = &_menu_SaveAndExitButton;

        /* ������ �����Ͻðڽ��ϱ�? �κ� */
        _uiControler->menu_ReallyEnd_Img = &_menu_ReallyEnd_Img;
        _uiControler->menu_ReallyEnd_Check_Idle = &_menu_ReallyEnd_Check_Idle;
        _uiControler->menu_ReallyEnd_Check_Choice = &_menu_ReallyEnd_Check_Choice;
        _uiControler->menu_ReallyEnd_Cancle_Idle = &_menu_ReallyEnd_Cancle_Idle;
        _uiControler->menu_ReallyEnd_Cancle_Choice = &_menu_ReallyEnd_Cancle_Choice;
    }

    #pragma region ���� ���¿��� [���ư���] �̹���, ��ư

    _research_goBackIdleImg.uiRenderer->Init("research_gobackidle");
    _research_goBackIdleImg.transform->SetPosition(WINSIZEX / 2 - 200, WINSIZEY - 70);
    _research_goBackIdleImg.SetActive(true);

    _research_goBackChoiceImg.uiRenderer->Init("research_gobackchoice");
    _research_goBackChoiceImg.transform->SetPosition(WINSIZEX / 2 - 200, WINSIZEY - 70);
    _research_goBackChoiceImg.SetActive(false);

    _research_goBackButton.Init();
    _research_goBackButton.uiRenderer->Init(220, 65);
    _research_goBackButton.transform->SetPosition(WINSIZEX / 2 - 200, WINSIZEY - 70);

    _research_goBackButton.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveGoBackImg, _uiControler,
            true),
        EVENT::ENTER);

    _research_goBackButton.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ReturnToGameScene, _uiControler,
            &_research, false),
        EVENT::CLICK);

    _research_goBackButton.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveGoBackImg, _uiControler,
            false),
        EVENT::EXIT);

    #pragma endregion

    #pragma region ���� ���¿��� [�ھ� DB] �̹���, ��ư

    _coreDBIdleImg.uiRenderer->Init("research_coredbidle");
    _coreDBIdleImg.transform->SetPosition(WINSIZEX / 2 + 100, WINSIZEY - 70);
    _coreDBIdleImg.SetActive(true);

    _coreDBChoiceImg.uiRenderer->Init("research_coredbchoice");
    _coreDBChoiceImg.transform->SetPosition(WINSIZEX / 2 + 100, WINSIZEY - 70);
    _coreDBChoiceImg.SetActive(false);

    _coreDBButton.Init();
    _coreDBButton.uiRenderer->Init(220, 65);
    _coreDBButton.transform->SetPosition(WINSIZEX / 2 + 100, WINSIZEY - 70);

    _coreDBButton.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveCoreDBImg, _uiControler, true), EVENT::ENTER);
    // �ھ� DB ȭ�� ������ �� �� ������ ��������ֱ� (���� �ӽ÷� _research�� ���ְ� �ִ�)
    _coreDBButton.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ReturnToCoreDBScene, _uiControler, &_research, false), EVENT::CLICK);
    _coreDBButton.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveCoreDBImg, _uiControler, false), EVENT::EXIT);

    #pragma endregion

    #pragma region �� ���� ���¿��� [���ư���] �̹���, ��ư

    _detailDes_goBackIdleImg.uiRenderer->Init("research_gobackidle");
    _detailDes_goBackIdleImg.transform->SetPosition(WINSIZEX / 2, WINSIZEY - 70);
    _detailDes_goBackIdleImg.SetActive(false);

    _detailDes_goBackChoiceImg.uiRenderer->Init("research_gobackchoice");
    _detailDes_goBackChoiceImg.transform->SetPosition(WINSIZEX / 2, WINSIZEY - 70);
    _detailDes_goBackChoiceImg.SetActive(false);

    _detailDes_goBackButton.Init();
    _detailDes_goBackButton.uiRenderer->Init(220, 65);
    _detailDes_goBackButton.transform->SetPosition(WINSIZEX / 2, WINSIZEY - 70);

    _detailDes_goBackButton.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inDetailDes_ActiveGoBackImg, _uiControler,
            &_inDetail, true),
        EVENT::ENTER);
    
    _detailDes_goBackButton.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ReturnToResearchScene,_uiControler,
            &_inDetail, &_coreDetailDescriptionImg, false),
        EVENT::CLICK);
    
    _detailDes_goBackButton.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inDetailDes_ReturnToResearch, _uiControler,
            false),
        EVENT::EXIT);

    #pragma endregion

	/*===================================================================== */
	/* �÷��̾� �κ� �ʱ�ȭ -> ���� */
	PlayerInit();
    _respawn->LinkPlayer(_player->controler);
	/*===================================================================== */

    /* ���ӽ� ���ʹ� ���� �۾� �Լ�, by ����. ���� ���� */
	SetProjectileManager();
	SetCore();
	SetEnemyManager();
	SetCameraControler();
	SetGameUIInit();

	_uiControler->enemyWaveSkip = &_enemyWaveSkip;
	_uiControler->enemyWaveSkipClick = &_enemyWaveSkipClick;

    /* ���� �۾� ��ö 210718 */
	//SOUNDMANAGER->addSound("start", "music/land.mp3", true, false);
	//SOUNDMANAGER->addSound("bgm1", "music/game1.mp3", true, false);
	//SOUNDMANAGER->addSound("bgm2", "music/game2.mp3", true, false);
	//SOUNDMANAGER->addSound("bgm3", "music/game9.mp3", true, false);
	//SOUNDMANAGER->play("start", 10.0f);
	//_musicTime = 0;
    //StaticBuffer->EndDraw();

    return S_OK;
}

void GameScene::Update()
{
	MainCam->Update();
    EFFECTMANAGER->Update();
    //07-19 �÷��̾�� UI���� ���콺 Ŭ�� �켱���������� UI������Ʈ ���� �ø�
    //ī�װ� ������ ������Ʈ
    {
        _defenseIcon.Update();
        _railIcon.Update();
        _turretIcon.Update();
        _productionIcon.Update();

        // �ھ� �����ͺ��̽�, ���� ������ �߰� (�ÿ�)
        _coreDBIcon.Update();
        _researchIcon.Update();

        // ����ȭ�� ������ ī�װ� �����ܿ� ENTER ���� ��� ������ ȸ�� �̹��� (�ÿ�)
        _inGame_TouchToIcon.Update();
    }

    //��ġ�� ������ ������Ʈ
    {
        _copperWallIcon.Update();
        _mechanicDrillIcon.Update();
        _duoIcon.Update();
        _conveyorIcon.Update();
    }

    _propFactory->Update();
    _propContainer->Update();
    _resourceManager->Update();
    _uiControler->Update();
    _respawn->Update();
	InGameUIUpdate();

    /* �ÿ� */
    // �޴� �κ� Update
    {
        if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
        {
            if (_menu)
            {
                _menu = false;
                _menuImg.SetActive(false);
            }
            else
            {
                _menu = true;
                _menuImg.SetActive(true);
                _menu_SaveAndExitButton.uiMouseEvent->enable = true;
            }
        }

        if (_menu) menuUpdate();
    }

    // ���� �κ� Update
    {
        // ��ü �ڿ� ���� �ľ�
        if (_gameInfo->GetResourceAmount(COPPER) >= 1)
            _all_Resources_Count = 1;

        if (_gameInfo->GetResourceAmount(COPPER) >= 1 && _gameInfo->GetResourceAmount(LEAD) >= 1)
            _all_Resources_Count = 2;

        if (_gameInfo->GetResourceAmount(COPPER) >= 1 && _gameInfo->GetResourceAmount(LEAD) >= 1 && _gameInfo->GetResourceAmount(SCRAP) >= 1)
            _all_Resources_Count = 3;

        // ���� ���� ī��Ʈ ��� - ����
        if (_gameInfo->GetResourceAmount(COPPER) >= 1)
            _all_Resources_Copper_Count = to_wstring(_gameInfo->GetResourceAmount(COPPER));

        // ���� ���� ī��Ʈ ��� - ��
        if (_gameInfo->GetResourceAmount(LEAD) >= 1)
            _all_Resources_Lead_Count = to_wstring(_gameInfo->GetResourceAmount(LEAD));

        // ���� ���� ī��Ʈ ��� - ��ö
        if (_gameInfo->GetResourceAmount(SCRAP) >= 1)
            _all_Resources_Scrap_Count = to_wstring(_gameInfo->GetResourceAmount(SCRAP));

        if (_research)
        {
            researchUpdate();
            if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE)) _research = false;
        }
        _research_goBackButton.Update();
        _coreDBButton.Update();
        _detailDes_goBackButton.Update();
    }

	/* �÷��̾� �κ�*/
	_player->Update();
    // �÷��̾� �׸��� (�ÿ� �߰�) ==
    _playerShadow->Update();
    _playerShadow->transform->SetPosition(_player->transform->GetX() - 50, _player->transform->GetY() + 50);
    // ============================
	_playerWeaponL->Update();
	_playerWeaponR->Update();
	_playerCell->Update();
	_projectileManager->Update();
    _cameraControler->Update();

	// ���� �κ� -> ���� 210719
	ResourcesUpdate();
	//========================================
	_cameraControler->Update();
    _buildingCategoryFrame.Update();

    //ī�װ� ������ ������Ʈ 
    _propPreview.Update();
	_gameMap->Update();
	//========================================
    _categorySelect.Update();
    _propSelect.Update();
	_core->Update();

	//07.20 ���� �� ���� Wave UI && Player UI �۾�//
	_enemyManager->Update();

    /* ���� �۾� ��ö 210718 */
    _musicTime += TIMEMANAGER->getElapsedTime();
    if (_musicTime >= 15)
    {
        switch (RND->getInt(3))
        {
        case 0:
            _musicTime = -90.0f;
            SOUNDMANAGER->play("bgm1", 10.0f);
            break;
        case 1:
            _musicTime = -90.0f;
            SOUNDMANAGER->play("bgm2", 10.0f);
            break;
        case 2:
            _musicTime = -180.0f;
            SOUNDMANAGER->play("bgm3", 10.0f);
            break;
        }
    }
}

void GameScene::Render()
{
    MainCam->StaticToBackBuffer();

	_gameMap->Render();

    _propFactory->Render();
    _propContainer->Render();
    _resourceManager->Render();
    _uiControler->Render();

    COLLIDERMANAGER->Render();
	//�÷��̾� ���� ���� -> ����
	{
		_player->transform->GetChild(4)->gameObject->Render();
		_player->Render();
        // �÷��̾� �׸��� (�ÿ� �߰�) ==
        _playerShadow->Render();
        // ============================
		_enemyManager->Render();
        EFFECTMANAGER->Render();
		_player->Render();
		_projectileManager->Render();
		_core->Render();
		_cameraControler->Render();
		MainCam->Render();
	}

    //ī�װ� ������ ����
    {
        // ����ȭ�� ������ ī�װ� �����ܿ� ENTER ���� ��� ������ ȸ�� �̹��� (�ÿ�)
        _inGame_TouchToIcon.Render();

        _buildingCategoryFrame.Render();
        _defenseIcon.Render();
        _railIcon.Render();
        _turretIcon.Render();
        _productionIcon.Render();
        // �ھ� �����ͺ��̽�, ���� ������ �߰� (�ÿ�)
        _coreDBIcon.Render();
        _researchIcon.Render();
    }
    //��ġ�� ������ ����
    {
        _copperWallIcon.Render();
        _mechanicDrillIcon.Render();
        _duoIcon.Render();
        _conveyorIcon.Render();
    }
    _categorySelect.Render();
    _propSelect.Render();

	InGameUIRender();
    //07.20 ���� �� ���� Wave UI && Player UI �۾�//
	//�ڿ�UI ���� -> ���� (210719)
	ResourcesRender();
	_player->controler->playerUI.Render();
	_player->controler->playerHpUIPane.Render();
	_player->controler->playerHpUI.Render();
	_player->controler->playerHpUIAlpha.Render();

    /* �ÿ� */
    // ����
    if (_research) researchRender();
    if (_research && _all_Resources_State)
    {
        if (_all_Resources_Count == 1)
        {
            _all_Resources_Open1_Img.Render();

            D2DRENDERER->RenderText(WINSIZEX / 2 - 620, WINSIZEY / 2 - 360, _all_Resources_Copper_Count, 14, L"mindustry", D2DRenderer::DefaultBrush::White);
            _all_Resources_Mineral[0].Render();
            D2DRENDERER->RenderText(WINSIZEX / 2 - 550, WINSIZEY / 2 - 360, L"����", 14, L"fontello", D2DRenderer::DefaultBrush::White);
        }

        if (_all_Resources_Count == 2)
        {
            _all_Resources_Open2_Img.Render();

            D2DRENDERER->RenderText(WINSIZEX / 2 - 620, WINSIZEY / 2 - 360, _all_Resources_Copper_Count, 14, L"mindustry", D2DRenderer::DefaultBrush::White);
            D2DRENDERER->RenderText(WINSIZEX / 2 - 620, WINSIZEY / 2 - 330, _all_Resources_Lead_Count, 14, L"mindustry", D2DRenderer::DefaultBrush::White);
            _all_Resources_Mineral[0].Render();
            _all_Resources_Mineral[1].Render();
            D2DRENDERER->RenderText(WINSIZEX / 2 - 550, WINSIZEY / 2 - 360, L"����", 14, L"fontello", D2DRenderer::DefaultBrush::White);
            D2DRENDERER->RenderText(WINSIZEX / 2 - 550, WINSIZEY / 2 - 330, L"��", 14, L"fontello", D2DRenderer::DefaultBrush::White);
        }

        if (_all_Resources_Count == 3)
        {
            _all_Resources_Open3_Img.Render();

            D2DRENDERER->RenderText(WINSIZEX / 2 - 620, WINSIZEY / 2 - 360, _all_Resources_Copper_Count, 14, L"mindustry", D2DRenderer::DefaultBrush::White);
            D2DRENDERER->RenderText(WINSIZEX / 2 - 620, WINSIZEY / 2 - 330, _all_Resources_Lead_Count, 14, L"mindustry", D2DRenderer::DefaultBrush::White);
            D2DRENDERER->RenderText(WINSIZEX / 2 - 620, WINSIZEY / 2 - 300, _all_Resources_Scrap_Count, 14, L"mindustry", D2DRenderer::DefaultBrush::White);
            _all_Resources_Mineral[0].Render();
            _all_Resources_Mineral[1].Render();
            _all_Resources_Mineral[2].Render();
            D2DRENDERER->RenderText(WINSIZEX / 2 - 550, WINSIZEY / 2 - 360, L"����", 14, L"fontello", D2DRenderer::DefaultBrush::White);
            D2DRENDERER->RenderText(WINSIZEX / 2 - 550, WINSIZEY / 2 - 330, L"��", 14, L"fontello", D2DRenderer::DefaultBrush::White);
            D2DRENDERER->RenderText(WINSIZEX / 2 - 550, WINSIZEY / 2 - 300, L"��ö", 14, L"fontello", D2DRenderer::DefaultBrush::White);
        }
    }

    // �޴�
    if (_menu) menuRender();

	/* ================================���� ������ ������ ========================================*/
    //210719 ���� ����
	StringRender();

    // ���콺 ���� �۾� (�ÿ�)
}

void GameScene::Release()
{
	NEW_SAFE_RELEASE(_player);
    NEW_SAFE_RELEASE(_propContainer);
    SAFE_DELETE(_propContainer);
    NEW_SAFE_RELEASE(_uiControler);
    SAFE_DELETE(_uiControler);
}

void GameScene::InitClip()
{
	//ī�װ� ������ Ŭ��
	{
		CLIPMANAGER->AddClip("turret_icon", "icons/turret.png", 32, 32);
		CLIPMANAGER->AddClip("production_icon", "icons/production.png", 32, 32);
		CLIPMANAGER->AddClip("rail_icon", "icons/distribution.png", 32, 32);
		CLIPMANAGER->AddClip("defense_icon", "icons/defense.png", 32, 32);
        // �ھ� �����ͺ��̽�, ���� ������ �߰� (�ÿ�)
        CLIPMANAGER->AddClip("core_db_icon", "sprites/game/book.png", 14, 14);
        CLIPMANAGER->AddClip("research_icon", "sprites/game/tree.png", 14, 14);

        // ����ȭ�� ������ ī�װ� �����ܿ� ENTER ���� ��� ������ ȸ�� �̹���
        CLIPMANAGER->AddClip("in_game_touch_to_icon", "sprites/game/in_game_touch_to_icon.png", 48, 48);
	}

	//��ġ�� ������ Ŭ��
	{
		CLIPMANAGER->AddClip("duo", "sprites/blocks/turrets/duo-icon.png", 32, 32);
		CLIPMANAGER->AddClip("mechanical_drill", "sprites/blocks/drills/mechanical-drill-icon.png", 64, 64);
		CLIPMANAGER->AddClip("conveyor", "sprites/blocks/distribution/conveyors/conveyor-0-0.png", 32, 32);
		CLIPMANAGER->AddClip("copper_wall", "sprites/blocks/walls/copper-wall.png", 32, 32);
	}

    //�����̾� ��Ʈ Ŭ��
    {
        CLIPMANAGER->AddClip("conveyor_I", "sprites/blocks/distribution/conveyors/conveyor-I.png", 128, 32, 4, 1, 0.06f);
        CLIPMANAGER->AddClip("conveyor_L", "sprites/blocks/distribution/conveyors/conveyor-L.png", 128, 32, 4, 1, 0.06f);
        CLIPMANAGER->AddClip("conveyor_L2", "sprites/blocks/distribution/conveyors/conveyor-L2.png", 128, 32, 4, 1, 0.06f);
        CLIPMANAGER->AddClip("conveyor_T", "sprites/blocks/distribution/conveyors/conveyor-T.png", 128, 32, 4, 1, 0.06f);
        CLIPMANAGER->AddClip("conveyor_T2", "sprites/blocks/distribution/conveyors/conveyor-T2.png", 128, 32, 4, 1, 0.06f);
        CLIPMANAGER->AddClip("conveyor_T3", "sprites/blocks/distribution/conveyors/conveyor-T3.png", 128, 32, 4, 1, 0.06f);
        CLIPMANAGER->AddClip("conveyor_cross", "sprites/blocks/distribution/conveyors/conveyor-cross.png", 128, 32, 4, 1, 0.06f);
    }

    //�帱 Ŭ��
    {
        CLIPMANAGER->AddClip("drill_body", "sprites/blocks/drills/mechanical-drill.png", 64, 64);
        CLIPMANAGER->AddClip("drill_top", "sprites/blocks/drills/mechanical-drill-top.png", 64, 64);
        CLIPMANAGER->AddClip("drill_rotator", "sprites/blocks/drills/mechanical-drill-rotator.png", 64, 64);
    }
    //�ͷ� Ŭ��
    {
        CLIPMANAGER->AddClip("duo_head", "sprites/blocks/turrets/duo-head.png", 32, 32);
        CLIPMANAGER->AddClip("duo_base", "sprites/blocks/turrets/bases/block-1.png", 32, 32);
    }
    //�� �̿� Ŭ��
    {
        CLIPMANAGER->AddClip("conveyor_arrow", "sprites/blocks/extra/conveyor-arrow.png", 96, 96);
        CLIPMANAGER->AddClip("copper", "sprites/items/item-copper.png", 32, 32);
        CLIPMANAGER->AddClip("lead", "sprites/items/item-lead.png", 32, 32);
    }
	//�÷��̾� Ŭ��
	{
		CLIPMANAGER->AddClip("player", "player/alpha.png", 48, 48);
		CLIPMANAGER->AddClip("enemy_projectile", "sprites/units/weapons/missiles-mount.png", 48, 48);
		CLIPMANAGER->AddClip("bullet", "sprites/effects/bullet.png", 52, 52);
		CLIPMANAGER->AddClip("player_weapon_L", "player/small-basic-weapon-L.png", 48, 48);
		CLIPMANAGER->AddClip("player_weapon_R", "player/small-basic-weapon-R.png", 48, 48);
	}
	CLIPMANAGER->AddClip("button_select", "sprites/ui/button-select.10.png", 52, 52);

    /* �ÿ� */
    /* ���� Ŭ�� */
    {
        // ��ü �ڿ�
        CLIPMANAGER->AddClip("all_resources_open_1", "sprites/game/all_resources_open_1.png", 224, 104);
        CLIPMANAGER->AddClip("all_resources_open_2", "sprites/game/all_resources_open_2.png", 224, 128);
        CLIPMANAGER->AddClip("all_resources_open_3", "sprites/game/all_resources_open_3.png", 224, 152);
        CLIPMANAGER->AddClip("all_resources_close", "sprites/game/all_resources_close.png", 224, 80);
        CLIPMANAGER->AddClip("all_resources_text", "sprites/game/all_resources_text.png", 136, 20);
        CLIPMANAGER->AddClip("all_resources_event", "sprites/game/all_resources_event.png", 200, 51);

        // ����
        CLIPMANAGER->AddClip("research_bg", "sprites/game/research_background.png", 1600, 1010);
        CLIPMANAGER->AddClip("research_choice", "sprites/game/choice.png", 75, 56);
        CLIPMANAGER->AddClip("research_lock", "sprites/game/lock.png", 74, 56);
        CLIPMANAGER->AddClip("in_research_choice", "sprites/game/in_research_choice.png", 50, 60);
        CLIPMANAGER->AddClip("in_research_about", "sprites/game/i.png", 24, 44);

        CLIPMANAGER->AddClip("research_core", "sprites/game/core.png", 74, 56);
        CLIPMANAGER->AddClip("research_core_basic_description", "sprites/game/core_basic_description.png", 159, 193);
        CLIPMANAGER->AddClip("research_core_detail_description", "sprites/game/core_detail_description.png", WINSIZEX, WINSIZEY);

        CLIPMANAGER->AddClip("research_drill", "sprites/game/drill.png", 74, 56);
        CLIPMANAGER->AddClip("research_conveyor", "sprites/game/conveyor.png", 74, 56);
        CLIPMANAGER->AddClip("research_crossover", "sprites/game/crossover.png", 74, 56);
        CLIPMANAGER->AddClip("research_undeveloped_distributor", "sprites/game/undeveloped_distributor.png", 74, 56);
        CLIPMANAGER->AddClip("research_developed_distributor", "sprites/game/developed_distributor.png", 74, 56);
        CLIPMANAGER->AddClip("research_outpost", "sprites/game/outpost.png", 74, 56);
        CLIPMANAGER->AddClip("research_copper", "sprites/game/copper.png", 74, 56);
        CLIPMANAGER->AddClip("research_water", "sprites/game/water.png", 74, 56);
        CLIPMANAGER->AddClip("research_lead", "sprites/game/lead.png", 74, 56);
        CLIPMANAGER->AddClip("research_sand", "sprites/game/sand.png", 74, 56);
        CLIPMANAGER->AddClip("research_duo", "sprites/game/duo.png", 74, 56);
        CLIPMANAGER->AddClip("research_undeveloped_copperWall", "sprites/game/undeveloped_copperWall.png", 74, 56);
        CLIPMANAGER->AddClip("research_developed_copperWall", "sprites/game/developed_copperWall.png", 74, 56);
        CLIPMANAGER->AddClip("research_undeveloped_scatter", "sprites/game/undeveloped_scatter.png", 74, 56);
        CLIPMANAGER->AddClip("research_developed_scatter", "sprites/game/developed_scatter.png", 74, 56);
        CLIPMANAGER->AddClip("research_undeveloped_largeCopperWall", "sprites/game/undeveloped_largeCopperWall.png", 74, 56);
        CLIPMANAGER->AddClip("research_developed_largeCopperWall", "sprites/game/developed_largeCopperWall.png", 74, 56);
        CLIPMANAGER->AddClip("research_undeveloped_router", "sprites/game/undeveloped_router.png", 74, 56);
        CLIPMANAGER->AddClip("research_developed_router", "sprites/game/developed_router.png", 74, 56);
        CLIPMANAGER->AddClip("research_undeveloped_sorter", "sprites/game/undeveloped_sorter.png", 74, 56);
        CLIPMANAGER->AddClip("research_developed_sorter", "sprites/game/developed_sorter.png", 74, 56);
        CLIPMANAGER->AddClip("research_undeveloped_bridgeConveyor", "sprites/game/undeveloped_bridgeConveyor.png", 74, 56);
        CLIPMANAGER->AddClip("research_developed_bridgeConveyor", "sprites/game/developed_bridgeConveyor.png", 74, 56);
        CLIPMANAGER->AddClip("research_undeveloped_invertedSorter", "sprites/game/undeveloped_invertedSorter.png", 74, 56);
        CLIPMANAGER->AddClip("research_developed_invertedSorter", "sprites/game/developed_invertedSorter.png", 74, 56);
        CLIPMANAGER->AddClip("research_undeveloped_overflowGate", "sprites/game/undeveloped_overflowGate.png", 74, 56);
        CLIPMANAGER->AddClip("research_developed_overflowGate", "sprites/game/developed_overflowGate.png", 74, 56);
        CLIPMANAGER->AddClip("research_undeveloped_underflowGate", "sprites/game/undeveloped_underflowGate.png", 74, 56);
        CLIPMANAGER->AddClip("research_developed_underflowGate", "sprites/game/developed_underflowGate.png", 74, 56);
        CLIPMANAGER->AddClip("research_developed_scrapMetal", "sprites/game/scrapMetal.png", 74, 56);

        /* SHUNG 210718 ���� ���� ��� ������ UI (�ڷΰ���, �ھ� ������ ���̽�) */
        CLIPMANAGER->AddClip("research_gobackidle", "sprites/game/gobackidle.png", 210, 64);
        CLIPMANAGER->AddClip("research_gobackchoice", "sprites/game/gobackchoice.png", 210, 64);
        CLIPMANAGER->AddClip("research_coredbidle", "sprites/game/core_db_idle.png", 210, 64);
        CLIPMANAGER->AddClip("research_coredbchoice", "sprites/game/core_db_choice.png", 210, 64);
    }

    /* �޴� Ŭ�� */
    {
        CLIPMANAGER->AddClip("menu_menuimg", "sprites/game/menu.png", WINSIZEX, WINSIZEY);
        
        CLIPMANAGER->AddClip("menu_goback_idle", "sprites/game/menu_gobackidle.png", 220, 55);
        CLIPMANAGER->AddClip("menu_goback_choice", "sprites/game/menu_gobackchoice.png", 220, 55);

        CLIPMANAGER->AddClip("menu_setting_idle", "sprites/game/menu_setting_idle.png", 220, 55);
        CLIPMANAGER->AddClip("menu_setting_choice", "sprites/game/menu_setting_choice.png", 220, 55);

        CLIPMANAGER->AddClip("menu_save_and_exit_idle", "sprites/game/menu_save_and_exit_idle.png", 240, 55);
        CLIPMANAGER->AddClip("menu_save_and_exit_choice", "sprites/game/menu_save_and_exit_choice.png", 240, 55);

        // ������ �����Ͻðڽ��ϱ�?
        CLIPMANAGER->AddClip("menu_reallyendimg", "sprites/game/menu_reallyend.png", WINSIZEX, WINSIZEY);

        CLIPMANAGER->AddClip("menu_reallyend_cancel_idle", "sprites/game/menu_reallyend_cancel_idle.png", 200, 54);
        CLIPMANAGER->AddClip("menu_reallyend_cancel_choice", "sprites/game/menu_reallyend_cancel_choice.png", 200, 54);

        CLIPMANAGER->AddClip("menu_reallyend_check_idle", "sprites/game/menu_reallyend_check_idle.png", 200, 54);
        CLIPMANAGER->AddClip("menu_reallyend_check_choice", "sprites/game/menu_reallyend_check_choice.png", 200, 54);

    }

	//// ENEMY & CORE Ŭ�� �۾� ���� /////
	{
		CLIPMANAGER->AddClip("core", "sprites/blocks/storage/core.png", 96, 96);
		CLIPMANAGER->AddClip("enemy_atrax", "sprites/units/enemy/enemy_atrax.png", 188, 329);
		CLIPMANAGER->AddClip("enemy_dagger_walk", "sprites/units/enemy/enemy_dagger_walk.png", 369, 114, 3, 1, 0.8f);
		CLIPMANAGER->AddClip("projectile", "sprites/units/enemy/projectile.png", 52, 52);
	}
}

void GameScene::InitCategoryUI()
{
    _buildingCategoryFrame.uiRenderer->Init("ui_frame");
    _buildingCategoryFrame.uiRenderer->SetAlpha(0.7f);
    _buildingCategoryFrame.transform->SetPosition(WINSIZEX - 132, WINSIZEY - 111);
    _buildingCategoryFrame.transform->SetScale(0.7f, 0.7f);
    _buildingCategoryFrame.uiMouseEvent->enable = false;

    _turretIcon.uiRenderer->Init("turret_icon");
    _turretIcon.transform->SetPosition(CATEGORY_UI_STARTX, CATEGORY_UI_STARTY);
	/**********************************************************
    * ��ư �ݹ��Լ� ��Ϲ��
    * RegistCallback �Ű�����(std::bind(&Ŭ������::�Լ���, Ŭ������ �ν��Ͻ�, �Ű�����....), ����̺�Ʈ ����);
    * ����̺�Ʈ ����
    * 1.ENTER : ���콺�� ����������
    * 2.EXIT : ���콺�� ������������
    * 3.CLICK : ���콺�� Ŭ��������
    ************************************************************/
    _turretIcon.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::ClickCategoryIcon, _uiControler, &_turretIcon, 0), EVENT::CLICK);

    _productionIcon.uiRenderer->Init("production_icon");
    _productionIcon.transform->SetPosition(_turretIcon.transform->GetX() + 40, _turretIcon.transform->GetY());
    _productionIcon.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::ClickCategoryIcon, _uiControler, &_productionIcon, 1), EVENT::CLICK);

    _railIcon.uiRenderer->Init("rail_icon");
    _railIcon.transform->SetPosition(_turretIcon.transform->GetX(), _turretIcon.transform->GetY() + 40);
    _railIcon.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::ClickCategoryIcon, _uiControler, &_railIcon, 2), EVENT::CLICK);

    _defenseIcon.uiRenderer->Init("defense_icon");
    _defenseIcon.transform->SetPosition(_turretIcon.transform->GetX() + 40, _turretIcon.transform->GetY() + 40);
    _defenseIcon.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::ClickCategoryIcon, _uiControler, &_defenseIcon, 3), EVENT::CLICK);

    // �ھ� �����ͺ��̽� ������ �߰� (�ÿ�)
    _coreDBIcon.uiRenderer->Init("core_db_icon");
    _coreDBIcon.transform->SetScale(2.5f, 2.5f);
    _coreDBIcon.transform->SetPosition(WINSIZEX / 2 + 435, WINSIZEY - 25);

    //_coreDBIcon.uiMouseEvent->RegistCallback(
    //    std::bind(&UIControler::inGame_Acitve_Choice_Img, _uiControler,
    //        &_coreDBIcon, &_isMineral, true),
    //    EVENT::ENTER);

    /* �ھ� �����ͺ��̽� Ŭ�� ���� ���� (07/23) */

    //_coreDBIcon.uiMouseEvent->RegistCallback(
    //    std::bind(&UIControler::inGame_Acitve_Choice_Img, _uiControler,
    //        &_coreDBIcon, &_isMineral, false),
    //    EVENT::EXIT);

    // ���� ������ �߰� (�ÿ�)
    _researchIcon.uiRenderer->Init("research_icon");
    _researchIcon.transform->SetScale(2.5f, 2.5f);
    _researchIcon.transform->SetPosition(WINSIZEX / 2 + 477, WINSIZEY - 25);

    _researchIcon.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inGame_Acitve_Choice_Img, _uiControler,
            &_researchIcon, true),
        EVENT::ENTER);

    _researchIcon.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inGame_Acitve_State, _uiControler,
            &_research, true),
        EVENT::CLICK);

    _researchIcon.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inGame_Acitve_Choice_Img, _uiControler,
            &_researchIcon, false),
        EVENT::EXIT);

    // ����ȭ�� ������ ī�װ� �����ܿ� ENTER ���� ��� ������ ȸ�� �̹��� (�ÿ�)
    _inGame_TouchToIcon.uiRenderer->Init("in_game_touch_to_icon");
    _inGame_TouchToIcon.SetActive(false);

    _categorySelect.uiRenderer->Init("button_select");
    _categorySelect.transform->SetPosition(_turretIcon.transform->GetX(), _turretIcon.transform->GetY());
}

void GameScene::InitPropUI()
{
    //�ͷ� ������ �ʱ�ȭ
    {
        _duoIcon.uiRenderer->Init("duo");
        _duoIcon.transform->SetPosition(PROP_UI_STARTX, PROP_UI_STARTY);
        _duoIcon.uiMouseEvent->RegistCallback(
            std::bind(&UIControler::ClickPropIcon, _uiControler, &_duoIcon, 0), EVENT::CLICK);
        _turretIconV.push_back(&_duoIcon);

    }

    //�帱 ������ �ʱ�ȭ
    {
		_mechanicDrillIcon.uiRenderer->Init("mechanical_drill");
		_mechanicDrillIcon.transform->SetPosition(PROP_UI_STARTX, PROP_UI_STARTY);
		_mechanicDrillIcon.transform->SetScale(0.5f, 0.5f);
        _mechanicDrillIcon.uiMouseEvent->RegistCallback(
            std::bind(&UIControler::ClickPropIcon, _uiControler, &_mechanicDrillIcon, 0), EVENT::CLICK);
		_drillIconV.push_back(&_mechanicDrillIcon);

        for (int i = 0; i < _drillIconV.size(); i++)
        {
            _drillIconV[i]->SetActive(false);
        }
    }

    //���� ������ �ʱ�ȭ
    {
        _conveyorIcon.uiRenderer->Init("conveyor");
        _conveyorIcon.transform->SetPosition(PROP_UI_STARTX, PROP_UI_STARTY);
        _conveyorIcon.uiMouseEvent->RegistCallback(
            std::bind(&UIControler::ClickPropIcon, _uiControler, &_conveyorIcon, 0), EVENT::CLICK);
        _railIconV.push_back(&_conveyorIcon);

        for (int i = 0; i < _railIconV.size(); i++)
        {
            _railIconV[i]->SetActive(false);
        }
    }

    //�� ������ �ʱ�ȭ
    {
        _copperWallIcon.uiRenderer->Init("copper_wall");
        _copperWallIcon.transform->SetPosition(PROP_UI_STARTX, PROP_UI_STARTY);
        _copperWallIcon.uiMouseEvent->RegistCallback(
            std::bind(&UIControler::ClickPropIcon, _uiControler, &_copperWallIcon, 0), EVENT::CLICK);
        _wallIconV.push_back(&_copperWallIcon);

        for (int i = 0; i < _wallIconV.size(); i++)
        {
            _wallIconV[i]->SetActive(false);
        }
    }

    _propSelect.uiRenderer->Init("button_select");
    _propSelect.transform->SetPosition(PROP_UI_STARTX, PROP_UI_STARTY);
    _propSelect.SetActive(false);

    _propPreview.Init();
    _propPreview.renderer->Init(32, 32);
    _propPreview.renderer->SetAlpha(0.5f);
    _propPreview.SetActive(false);
}

void GameScene::PlayerClip()
{
	//�÷��̾� Ŭ��
	CLIPMANAGER->AddClip("player", "player/alpha.png", 48, 48);
	//CLIPMANAGER->AddClip("enemy_projectile", "sprites/units/weapons/missiles-mount.png", 48, 48);
	CLIPMANAGER->AddClip("bullet", "sprites/effects/bullet.png", 52, 52);
	CLIPMANAGER->AddClip("player_weapon_L", "player/small-basic-weapon-L.png", 48, 48);
	CLIPMANAGER->AddClip("player_weapon_R", "player/small-basic-weapon-R.png", 48, 48);
	CLIPMANAGER->AddClip("player_cell", "player/alpha-cell.png", 48, 48);
	CLIPMANAGER->AddClip("player_fire_circle", "player/alpha_fire_circle.png", 17, 17);
	CLIPMANAGER->AddClip("player_fire", "player/alpha_fire.png", 30, 30);
    // �÷��̾� �׸��� �߰� (�ÿ�)
    CLIPMANAGER->AddClip("player_shadow", "player/shadow/alpha_shadow.png", 48, 48);

	//�ڿ� Ŭ��
	CLIPMANAGER->AddClip("copperUI", "sprites/items/item-copper.png", 32, 32);
	CLIPMANAGER->AddClip("leadUI", "sprites/items/item-lead.png", 32, 32);
    //�ڿ� Ŭ�� - ��ö �߰� (�ÿ�)
    CLIPMANAGER->AddClip("scrapUI", "sprites/game/item-scrap.png", 32, 32);
}

void GameScene::PlayerInit()
{
	/* �÷��̾� �κ� �ʱ�ȭ -> ���� */
	_player = new Player();
	_player->Init();
	_player->tag = TAGMANAGER->GetTag("player");
	_player->renderer->Init("player");
	_player->transform->SetPosition(1500, 900);
	_player->transform->SetAngle(0.0f);
	_player->controler->LinkProFactory(_propFactory);
	_propFactory->LinkPlayerControler(_player->controler);
    _uiControler->LinkPlayerControler(_player->controler);
	MainCam->transform->SetPosition(_player->transform->position.x, _player->transform->position.y);

	//�÷��̾� ���� ����.
	_playerWeaponL = new ImageObject;
	_playerWeaponL->Init();
	_playerWeaponL->renderer->Init("player_weapon_L");

	_playerWeaponR = new ImageObject;
	_playerWeaponR->Init();
	_playerWeaponR->renderer->Init("player_weapon_R");

	_playerCell = new ImageObject;
	_playerCell->Init();
	_playerCell->renderer->Init("player_cell");

	_playerFireCircle = new ImageObject;
	_playerFireCircle->Init();
	_playerFireCircle->renderer->Init("player_fire_circle");

	_playerFire = new ImageObject;
	_playerFire->Init();
	_playerFire->renderer->Init("player_fire");

	_player->transform->AddChild(_playerWeaponL->transform);		//����L �ڽ� 1
	_player->transform->AddChild(_playerWeaponR->transform);		//����R �ڽ� 2
	_player->transform->AddChild(_playerCell->transform);			//�÷��̾� �μ��� �ڽ�3
	_player->transform->AddChild(_playerFireCircle->transform);		//�÷��̾� �Ҳ� �Ͼ�κ� �ڽ�4
	_player->transform->AddChild(_playerFire->transform);			//�÷��̾� �Ҳ� �ڽ�5
	//�μ��⸸ �̰����� �����ϹǷ� �ʱ�ȭ
	_player->transform->GetChild(3)->SetPosition(_player->transform->GetX() , _player->transform->GetY());
    // �÷��̾� �׸��� (�ÿ� �߰�) =================
    _playerShadow = new ImageObject();
    _playerShadow->renderer->Init("player_shadow");
    _playerShadow->renderer->SetAlpha(0.375f);
    _playerShadow->transform->SetAngle(0.0f);
    _playerShadow->SetActive(true);
    _player->transform->AddChild(_playerShadow->transform);
    // ===========================================

	_player->controler->SetGameInfo(_gameInfo);
	_player->controler->SetGameMap(_gameMap);
}

void GameScene::ResourcesInit()
{
	_resoucesUIBackGround = RectMakeCenter(Vector2((WINSIZEX / 2), 20), Vector2(240, 40));
	
	_resourcesUI[0].Init();
	_resourcesUI[0].uiRenderer->Init("copperUI");
	_resourcesUI[0].transform->SetPosition(WINSIZEX / 2 - 95, 20);

	_resourcesUI[1].Init();
	_resourcesUI[1].uiRenderer->Init("leadUI");
    _resourcesUI[1].transform->SetPosition(WINSIZEX / 2 + 20, 20);
}

void GameScene::ResourcesUpdate()
{
	_resourcesUI[0].Update();
	_resourcesUI[1].Update();
}

void GameScene::ResourcesRender()
{
    // 12�� ���� �ڿ� ǥ��
    // ������ ���ȭ��
	D2DRenderer::GetInstance()->FillRectangle(_resoucesUIBackGround, D2D1::ColorF::Black, 0.7f);
	_resourcesUI[0].Render();   // ���� �̹���
	_resourcesUI[1].Render();   // �� �̹���

	wstring copperAmount;
	wstring leadAmount;

	if (_gameInfo->GetResourceAmount(COPPER) < 1000)
	{
        // ���� ���� ī��Ʈ ���
		copperAmount = to_wstring(_gameInfo->GetResourceAmount(COPPER));
	}
	else
	{
		copperAmount = L"";
		int thousand = _gameInfo->GetResourceAmount(COPPER) / 1000;
		copperAmount.append(to_wstring(thousand));
		copperAmount.append(L".");
		int hundreds = (_gameInfo->GetResourceAmount(COPPER) - (1000 * thousand)) / 100;
		copperAmount.append(to_wstring(hundreds));
		copperAmount.append(L"k");
	}

	if (_gameInfo->GetResourceAmount(LEAD) < 1000)
	{
        // �� ���� ���
		leadAmount = to_wstring(_gameInfo->GetResourceAmount(LEAD));
	}
	else if(_gameInfo->GetResourceAmount(LEAD) > 1000)
	{
		leadAmount = L"";
		int thousand = _gameInfo->GetResourceAmount(LEAD) / 1000;
		leadAmount.append(to_wstring(thousand));
		leadAmount.append(L".");
		int hundreds = (_gameInfo->GetResourceAmount(LEAD) - (1000 * thousand)) / 100;
		leadAmount.append(to_wstring(hundreds));
		leadAmount.append(L"k");

	}

	D2DRENDERER->RenderText(WINSIZEX / 2 - 70, 5, copperAmount, 28, L"mindustry", D2DRenderer::DefaultBrush::White);
	D2DRENDERER->RenderText(WINSIZEX / 2 + 42, 5, leadAmount, 28, L"mindustry", D2DRenderer::DefaultBrush::White);
}

void GameScene::researchUpdate()
{
    // ���ȭ��
    _research_bg.Update();

    // ��ü �ڿ�
    _all_Resources_Open1_Img.Update();
    _all_Resources_Open2_Img.Update();
    _all_Resources_Open3_Img.Update();
    _all_Resources_Close_Img.Update();
    _all_Resources_Img.Update();
    _all_Resources_Text.Update();
    _all_Resources_Button.Update();
    for (int i = 0; i < 3; i++)
    {
        _all_Resources_Mineral[i].Update();
    }

    _choiceImg.Update();
    _lockImg.Update();
    _inResearchChoiceImg.Update();

    _coreSlice.Update();
    _coreDetailDescriptionButton.Update();
    _coreBasicDescription.Update();
    _coreDetailDescriptionImg.Update();

    _mechanicalDrill.Update();
    _conveyor.Update();
    _crossover.Update();
    _distributor.Update();
    _outpost.Update();
    _copper.Update();
    _water.Update();
    _lead.Update();
    _sand.Update();
    _duo.Update();
    _copperWall.Update();
    _scatter.Update();
    _coreFoundation.Update();
    _mechanicalPump.Update();
    _graphiteCompressor.Update();
    _thermalGenerator.Update();
    _groundFactory.Update();
    _frozenForest.Update();
    _titan.Update();
    _metaglass.Update();
    _scrapMetal.Update();
    _mineral.Update();
    _coal.Update();
    _largeCopperWall.Update();
    _titanWall.Update();
    _hail.Update();
    _scorch.Update();
    _launchPad.Update();
    _router.Update();
    _sorter.Update();
    _container.Update();
    _bridgeConveyor.Update();
    _invertedSorter.Update();
    _overflowGate.Update();
    _titaniumConveyor.Update();
    _underflowGate.Update();
}

void GameScene::researchRender()
{
    // ���ȭ��
    _research_bg.Render();

    // ��ü �ڿ�
    _all_Resources_Close_Img.Render();
    _all_Resources_Img.Render();
    _all_Resources_Text.Render();
    _all_Resources_Button.Render();

    _coreSlice.Render();
    _mechanicalDrill.Render();
    _conveyor.Render();
    _crossover.Render();
    _distributor.Render();
    _outpost.Render();
    _copper.Render();
    _water.Render();
    _lead.Render();
    _sand.Render();
    _duo.Render();
    _copperWall.Render();
    _scatter.Render();
    _coreFoundation.Render();
    _mechanicalPump.Render();
    _graphiteCompressor.Render();
    _thermalGenerator.Render();
    _groundFactory.Render();
    _frozenForest.Render();
    _titan.Render();
    _metaglass.Render();
    _scrapMetal.Render();
    //_mineral.Render();
    _coal.Render();
    //_largeCopperWall.Render();
    //_titanWall.Render();
    //_hail.Render();
    _scorch.Render();
    _launchPad.Render();
    _router.Render();
    _sorter.Render();
    _container.Render();
    _bridgeConveyor.Render();
    //_invertedSorter.Render();
    //_overflowGate.Render();
    //_titaniumConveyor.Render();
    //_underflowGate.Render();

    /* Lock, Choice, ȸ�� Choice */
    _lockImg.Render();
    _choiceImg.Render();

    /* ���� Render - ������ ��ư�� �����Բ� ��µǱ� ���� ���´�.*/
    _coreBasicDescription.Render();

    // i�� ���콺 �浹�� �Ͼ�� ��쿡 ������ ȸ������â�� render
    _inResearchChoiceImg.Render();

    /* �⺻ �������� i�� �������� ������ ȸ������â ���� �ö�;� �ϹǷ� ����� �ִ´�. */
    _coreDetailDescriptionButton.Render();

    //
    _research_goBackIdleImg.Render();
    _research_goBackChoiceImg.Render();
    _research_goBackButton.Render();
    _coreDBIdleImg.Render();
    _coreDBChoiceImg.Render();
    _coreDBButton.Render();

    /* �� ���� �������� */
    _coreDetailDescriptionImg.Render();

    _detailDes_goBackIdleImg.Render();
    _detailDes_goBackChoiceImg.Render();
    _detailDes_goBackButton.Render();
}

void GameScene::researchInitUI()
{
#pragma region ��ü �ڿ�

    // ��ü �ڿ� [����]
    _all_Resources_Open1_Img.uiRenderer->Init("all_resources_open_1");
    _all_Resources_Open1_Img.uiMouseEvent->enable = false;
    _all_Resources_Open1_Img.transform->SetPosition(WINSIZEX / 2 - 560, WINSIZEY / 2 - 368);
    _all_Resources_Open1_Img.SetActive(true);

    _all_Resources_Open2_Img.uiRenderer->Init("all_resources_open_2");
    _all_Resources_Open2_Img.uiMouseEvent->enable = false;
    _all_Resources_Open2_Img.transform->SetPosition(WINSIZEX / 2 - 560, WINSIZEY / 2 - 356);
    _all_Resources_Open2_Img.SetActive(true);
    
    _all_Resources_Open3_Img.uiRenderer->Init("all_resources_open_3");
    _all_Resources_Open3_Img.uiMouseEvent->enable = false;
    _all_Resources_Open3_Img.transform->SetPosition(WINSIZEX / 2 - 560, WINSIZEY / 2 - 344);
    _all_Resources_Open3_Img.SetActive(true);

    // ��ü �ڿ� [����]
    _all_Resources_Close_Img.uiRenderer->Init("all_resources_close");
    _all_Resources_Close_Img.uiMouseEvent->enable = false;
    _all_Resources_Close_Img.transform->SetPosition(WINSIZEX / 2 - 560, WINSIZEY / 2 - 380);
    _all_Resources_Close_Img.SetActive(false);

    // ��ü �ڿ� �̹��� (�浹 - ȸ��)
    _all_Resources_Img.uiRenderer->Init("all_resources_event");
    _all_Resources_Img.uiMouseEvent->enable = false;
    _all_Resources_Img.transform->SetPosition(WINSIZEX / 2 - 560, WINSIZEY / 2 - 380);
    _all_Resources_Img.SetActive(false);

    // ��ü �ڿ� �ؽ�Ʈ
    _all_Resources_Text.uiRenderer->Init("all_resources_text");
    _all_Resources_Text.uiMouseEvent->enable = false;
    _all_Resources_Text.transform->SetPosition(WINSIZEX / 2 - 580, WINSIZEY / 2 - 378);
    _all_Resources_Text.SetActive(true);

    // ��ü �ڿ� ��ư
    _all_Resources_Button.Init();
    _all_Resources_Button.uiRenderer->Init(210, 50);
    _all_Resources_Button.transform->SetPosition(WINSIZEX / 2 - 560, WINSIZEY / 2 - 380);

    // ��ü �ڿ� ��ư ���콺 �̺�Ʈ
    _all_Resources_Button.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_Active_Choice_Img, _uiControler,
            &_all_Resources_State),
        EVENT::ENTER);

    _all_Resources_Button.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_Active_all_Resources_Click_Event, _uiControler,
            &_all_Resources_State),
        EVENT::CLICK);
    
    _all_Resources_Button.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_InActive_Choice_Img, _uiControler),
        EVENT::EXIT);

    // ��ü �ڿ� ���� �̹��� - ����
    _all_Resources_Mineral[0].Init();
    _all_Resources_Mineral[0].uiRenderer->Init("copperUI");
    _all_Resources_Mineral[0].uiMouseEvent->enable = false;
    _all_Resources_Mineral[0].transform->SetPosition(WINSIZEX / 2 - 575, WINSIZEY / 2 - 345);

    // ��ü �ڿ� ���� �̹��� - ��
    _all_Resources_Mineral[1].Init();
    _all_Resources_Mineral[1].uiRenderer->Init("leadUI");
    _all_Resources_Mineral[1].uiMouseEvent->enable = false;
    _all_Resources_Mineral[1].transform->SetPosition(WINSIZEX / 2 - 575, WINSIZEY / 2 - 315);
    
    // ��ü �ڿ� ���� �̹��� - ��ö
    _all_Resources_Mineral[2].Init();
    _all_Resources_Mineral[2].uiRenderer->Init("scrapUI");
    _all_Resources_Mineral[2].uiMouseEvent->enable = false;
    _all_Resources_Mineral[2].transform->SetPosition(WINSIZEX / 2 - 575, WINSIZEY / 2 - 285);
   
#pragma endregion

#pragma region ���ȭ��

    _research_bg.uiRenderer->Init("research_bg");
    _research_bg.uiMouseEvent->enable = false;
    _research_bg.transform->SetPosition(0, 0);
    _research_bg.transform->SetScale(2.0f, 2.0f);
    _research_bg.uiRenderer->SetAlpha(0.8f);
    _research_bg.SetActive(true);

#pragma endregion

#pragma region ChoiceImg

    _choiceImg.uiRenderer->Init("research_choice");
    _choiceImg.uiMouseEvent->enable = false;
    _choiceImg.transform->SetPosition(WINSIZEX / 2, WINSIZEY / 2);
    _choiceImg.transform->SetScale(0.75f, 0.75f);
    _choiceImg.SetActive(false);

#pragma endregion

#pragma region LockImg

    _lockImg.uiRenderer->Init("research_lock");
    _lockImg.uiMouseEvent->enable = false;
    _lockImg.transform->SetPosition(WINSIZEX / 2, WINSIZEY / 2);
    _lockImg.transform->SetScale(0.75f, 0.75f);
    _lockImg.SetActive(false);

#pragma endregion

#pragma region �������� ������ �⺻���� �� �� i�� ���콺 �浹�� �Ͼ�� ��쿡 ������ ȸ������â

    _inResearchChoiceImg.uiRenderer->Init("in_research_choice");
    _inResearchChoiceImg.uiMouseEvent->enable = false;
    _inResearchChoiceImg.transform->SetPosition(WINSIZEX / 2, WINSIZEY / 2);
    _inResearchChoiceImg.SetActive(false);

#pragma endregion

#pragma region �ھ� : ����

    // �ھ� : ���� ��ư
    _coreSlice.uiRenderer->Init("research_core");
    _coreSlice.transform->SetPosition(WINSIZEX / 2, WINSIZEY / 2);
    _coreSlice.transform->SetScale(0.75f, 0.75f);

    // �ھ� : ���� �⺻ ����
    _coreBasicDescription.uiRenderer->Init("research_core_basic_description");
    _coreBasicDescription.transform->SetPosition(WINSIZEX / 2 + 103, WINSIZEY / 2 + 78);
    _coreBasicDescription.SetActive(false);

    // �ھ� : ���� �⺻ ������ [i] �ֺ� ��ư
    _coreDetailDescriptionButton.uiRenderer->Init("in_research_about");
    _coreDetailDescriptionButton.transform->SetPosition(WINSIZEX / 2 + 57, WINSIZEY / 2 + 22);
    _coreDetailDescriptionButton.SetActive(false);

    // �ھ� : ���� �� ���� �̹���
    _coreDetailDescriptionImg.uiRenderer->Init("research_core_detail_description");
    _coreDetailDescriptionImg.transform->SetPosition(WINSIZEX / 2, WINSIZEY / 2);
    _coreDetailDescriptionImg.uiRenderer->SetAlpha(1.f);
    _coreDetailDescriptionImg.uiMouseEvent->enable = false;
    _coreDetailDescriptionImg.SetActive(false);

    /* �⺻ ������ */
    _coreSlice.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImgWithBasicDes, _uiControler,
            _coreSlice.transform, &_coreBasicDescription, &_coreDetailDescriptionButton, &_inDetail, true),
        EVENT::ENTER);

    _coreSlice.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_inActiveChoiceImgWithBasicDes, _uiControler,
            _coreSlice.transform, &_coreBasicDescription, &_lockDes, &_coreDetailDescriptionButton, false),
        EVENT::EXIT);

    /* �⺻ ���� ��ư */
    _coreBasicDescription.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_inBasicDes, _uiControler,
            _coreSlice.transform, &_coreBasicDescription, &_lockDes, true),
        EVENT::ENTER);
    
    _coreBasicDescription.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_disableInBasicDes, _uiControler,
            _coreSlice.transform, &_coreBasicDescription, &_lockDes, &_coreDetailDescriptionButton, false),
        EVENT::EXIT);

    /* �⺻ ���� [i] �ֺ� ��ư */
    _coreDetailDescriptionButton.uiMouseEvent->RegistCallback(
       std::bind(&UIControler::inResearch_ActiveInResearchChoiceImg, _uiControler,
           _coreDetailDescriptionButton.transform, true),
        EVENT::ENTER);

    _coreDetailDescriptionButton.uiMouseEvent->RegistCallback(
       std::bind(&UIControler::inResearch_ActiveDetailImg, _uiControler,
           &_coreDetailDescriptionImg, &_inDetail, true),
        EVENT::CLICK);

    _coreDetailDescriptionButton.uiMouseEvent->RegistCallback(
       std::bind(&UIControler::inResearch_ActiveInResearchChoiceImg, _uiControler,
           _coreDetailDescriptionButton.transform, false),
        EVENT::EXIT);

#pragma endregion
  
#pragma region ���� �帱

    _mechanicalDrill.uiRenderer->Init("research_drill");
    _mechanicalDrill.transform->SetPosition(WINSIZEX / 2 - 200, WINSIZEY / 2 - 50);
    _mechanicalDrill.transform->SetScale(0.75f, 0.75f);

    _mechanicalDrill.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _mechanicalDrill.transform, true), EVENT::ENTER);
    _mechanicalDrill.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _mechanicalDrill.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region �����̳�

    _conveyor.uiRenderer->Init("research_conveyor");
    _conveyor.transform->SetPosition(WINSIZEX / 2 - 400, WINSIZEY / 2 - 50);
    _conveyor.transform->SetScale(0.75f, 0.75f);

    _conveyor.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _conveyor.transform, true), EVENT::ENTER);
    _conveyor.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _conveyor.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region ������

    _crossover.uiRenderer->Init("research_crossover");
    _crossover.transform->SetPosition(WINSIZEX / 2 - 400, WINSIZEY / 2 - 100);
    _crossover.transform->SetScale(0.75f, 0.75f);

    _crossover.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _crossover.transform, true), EVENT::ENTER);
    _crossover.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _crossover.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region �й��

    _distributor.uiRenderer->Init("research_undeveloped_distributor");
    _distributor.transform->SetPosition(WINSIZEX / 2 - 400, WINSIZEY / 2 - 150);
    _distributor.transform->SetScale(0.75f, 0.75f);

    _distributor.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _distributor.transform, true), EVENT::ENTER);
    _distributor.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _distributor.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region ���ʱ���

    _outpost.uiRenderer->Init("research_outpost");
    _outpost.transform->SetPosition(WINSIZEX / 2 + 200, WINSIZEY / 2 + 50);
    _outpost.transform->SetScale(0.75f, 0.75f);

    _outpost.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _outpost.transform, true), EVENT::ENTER);
    _outpost.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _outpost.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region ����

    _copper.uiRenderer->Init("research_copper");
    _copper.transform->SetPosition(WINSIZEX / 2 + 600, WINSIZEY / 2 + 50);
    _copper.transform->SetScale(0.75f, 0.75f);

    _copper.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _copper.transform, true), EVENT::ENTER);
    _copper.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _copper.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region ��

    _water.uiRenderer->Init("research_water");
    _water.transform->SetPosition(WINSIZEX / 2 + 400, WINSIZEY / 2 + 100);
    _water.transform->SetScale(0.75f, 0.75f);

    _water.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _water.transform, true), EVENT::ENTER);
    _water.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _water.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region ��

    _lead.uiRenderer->Init("research_lead");
    _lead.transform->SetPosition(WINSIZEX / 2 + 500, WINSIZEY / 2 + 100);
    _lead.transform->SetScale(0.75f, 0.75f);

    _lead.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _lead.transform, true), EVENT::ENTER);
    _lead.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _lead.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region ��

    _sand.uiRenderer->Init("research_sand");
    _sand.transform->SetPosition(WINSIZEX / 2 + 600, WINSIZEY / 2 + 100);
    _sand.transform->SetScale(0.75f, 0.75f);

    _sand.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _sand.transform, true), EVENT::ENTER);
    _sand.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _sand.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region ���

    _duo.uiRenderer->Init("research_duo");
    _duo.transform->SetPosition(WINSIZEX / 2 + 600, WINSIZEY / 2 - 50);
    _duo.transform->SetScale(0.75f, 0.75f);

    _duo.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _duo.transform, true), EVENT::ENTER);
    _duo.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _duo.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region ���� ��

    _copperWall.uiRenderer->Init("research_undeveloped_copperWall");
    _copperWall.transform->SetPosition(WINSIZEX / 2 + 450, WINSIZEY / 2 - 100);
    _copperWall.transform->SetScale(0.75f, 0.75f);

    _copperWall.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _copperWall.transform, true), EVENT::ENTER);
    _copperWall.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _copperWall.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region ��ĳ��

    _scatter.uiRenderer->Init("research_undeveloped_scatter");
    _scatter.transform->SetPosition(WINSIZEX / 2 + 550, WINSIZEY / 2 - 100);
    _scatter.transform->SetScale(0.75f, 0.75f);

    _scatter.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _scatter.transform, true), EVENT::ENTER);
    _scatter.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _scatter.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region �ھ� : ���

    _coreFoundation.uiRenderer->Init("research_lock");
    _coreFoundation.transform->SetPosition(WINSIZEX / 2 - 300, WINSIZEY / 2 - 50);
    _coreFoundation.transform->SetScale(0.75f, 0.75f);

    _coreFoundation.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _coreFoundation.transform, true), EVENT::ENTER);
    _coreFoundation.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _coreFoundation.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region ���� ����

    _mechanicalPump.uiRenderer->Init("research_lock");
    _mechanicalPump.transform->SetPosition(WINSIZEX / 2 - 250, WINSIZEY / 2 - 100);
    _mechanicalPump.transform->SetScale(0.75f, 0.75f);

    _mechanicalPump.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _mechanicalPump.transform, true), EVENT::ENTER);
    _mechanicalPump.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _mechanicalPump.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region �濬 �����

    _graphiteCompressor.uiRenderer->Init("research_lock");
    _graphiteCompressor.transform->SetPosition(WINSIZEX / 2 - 175, WINSIZEY / 2 - 100);
    _graphiteCompressor.transform->SetScale(0.75f, 0.75f);

    _graphiteCompressor.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _graphiteCompressor.transform, true), EVENT::ENTER);
    _graphiteCompressor.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _graphiteCompressor.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region ȭ�� ������

    _thermalGenerator.uiRenderer->Init("research_lock");
    _thermalGenerator.transform->SetPosition(WINSIZEX / 2 - 100, WINSIZEY / 2 - 100);
    _thermalGenerator.transform->SetScale(0.75f, 0.75f);

    _thermalGenerator.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _thermalGenerator.transform, true), EVENT::ENTER);
    _thermalGenerator.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _thermalGenerator.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region ���� ������

    _groundFactory.uiRenderer->Init("research_lock");
    _groundFactory.transform->SetPosition(WINSIZEX / 2 - 225, WINSIZEY / 2 + 50);
    _groundFactory.transform->SetScale(0.75f, 0.75f);

    _groundFactory.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _groundFactory.transform, true), EVENT::ENTER);
    _groundFactory.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _groundFactory.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region ������ ��

    _frozenForest.uiRenderer->Init("research_lock");
    _frozenForest.transform->SetPosition(WINSIZEX / 2 + 200, WINSIZEY / 2 + 100);
    _frozenForest.transform->SetScale(0.75f, 0.75f);

    _frozenForest.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _frozenForest.transform, true), EVENT::ENTER);
    _frozenForest.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _frozenForest.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region ƼŸ��

    _titan.uiRenderer->Init("research_lock");
    _titan.transform->SetPosition(WINSIZEX / 2 + 475, WINSIZEY / 2 + 150);
    _titan.transform->SetScale(0.75f, 0.75f);

    _titan.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _titan.transform, true), EVENT::ENTER);
    _titan.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _titan.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region ��ȭ ����

    _metaglass.uiRenderer->Init("research_lock");
    _metaglass.transform->SetPosition(WINSIZEX / 2 + 525, WINSIZEY / 2 + 150);
    _metaglass.transform->SetScale(0.75f, 0.75f);

    _metaglass.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _metaglass.transform, true), EVENT::ENTER);
    _metaglass.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _metaglass.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region ��ö

    //_scrapMetal.uiRenderer->Init("research_developed_scrapMetal");
    _scrapMetal.uiRenderer->Init("research_lock");

    _scrapMetal.transform->SetPosition(WINSIZEX / 2 + 575, WINSIZEY / 2 + 150);
    _scrapMetal.transform->SetScale(0.75f, 0.75f);

    _scrapMetal.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _scrapMetal.transform, true), EVENT::ENTER);
    _scrapMetal.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _scrapMetal.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region ����

    _mineral.uiRenderer->Init("research_lock");
    _mineral.transform->SetPosition(WINSIZEX / 2 + 575, WINSIZEY / 2 + 200);
    _mineral.transform->SetScale(0.75f, 0.75f);

    _mineral.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _mineral.transform, true), EVENT::ENTER);
    _mineral.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _mineral.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region ��ź

    _coal.uiRenderer->Init("research_lock");
    _coal.transform->SetPosition(WINSIZEX / 2 + 625, WINSIZEY / 2 + 150);
    _coal.transform->SetScale(0.75f, 0.75f);

    _coal.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _coal.transform, true), EVENT::ENTER);
    _coal.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _coal.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region ���� ���� ��

    _largeCopperWall.uiRenderer->Init("research_undeveloped_largeCopperWall");
    _largeCopperWall.transform->SetPosition(WINSIZEX / 2 + 450, WINSIZEY / 2 - 150);
    _largeCopperWall.transform->SetScale(0.75f, 0.75f);

    _largeCopperWall.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _largeCopperWall.transform, true), EVENT::ENTER);
    _largeCopperWall.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _largeCopperWall.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region Ÿ��ź ��

    _titanWall.uiRenderer->Init("research_lock");
    _titanWall.transform->SetPosition(WINSIZEX / 2 + 450, WINSIZEY / 2 - 200);
    _titanWall.transform->SetScale(0.75f, 0.75f);

    _titanWall.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _titanWall.transform, true), EVENT::ENTER);
    _titanWall.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _titanWall.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region ����

    _hail.uiRenderer->Init("research_lock");
    _hail.transform->SetPosition(WINSIZEX / 2 + 550, WINSIZEY / 2 - 150);
    _hail.transform->SetScale(0.75f, 0.75f);

    _hail.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _hail.transform, true), EVENT::ENTER);
    _hail.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _hail.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region ����ġ

    _scorch.uiRenderer->Init("research_lock");
    _scorch.transform->SetPosition(WINSIZEX / 2 + 650, WINSIZEY / 2 - 100);
    _scorch.transform->SetScale(0.75f, 0.75f);

    _scorch.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _scorch.transform, true), EVENT::ENTER);
    _scorch.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _scorch.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region ���� �ڿ� ���۱�

    _launchPad.uiRenderer->Init("research_lock");
    _launchPad.transform->SetPosition(WINSIZEX / 2 - 550, WINSIZEY / 2 - 200);
    _launchPad.transform->SetScale(0.75f, 0.75f);

    _launchPad.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _launchPad.transform, true), EVENT::ENTER);
    _launchPad.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _launchPad.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region ���� �й��

    _router.uiRenderer->Init("research_undeveloped_router");
    _router.transform->SetPosition(WINSIZEX / 2 - 475, WINSIZEY / 2 - 200);
    _router.transform->SetScale(0.75f, 0.75f);

    _router.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _router.transform, true), EVENT::ENTER);
    _router.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _router.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region ����

    _sorter.uiRenderer->Init("research_undeveloped_sorter");
    _sorter.transform->SetPosition(WINSIZEX / 2 - 400, WINSIZEY / 2 - 200);
    _sorter.transform->SetScale(0.75f, 0.75f);

    _sorter.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _sorter.transform, true), EVENT::ENTER);
    _sorter.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _sorter.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region �����̳�

    _container.uiRenderer->Init("research_lock");
    _container.transform->SetPosition(WINSIZEX / 2 - 325, WINSIZEY / 2 - 200);
    _container.transform->SetScale(0.75f, 0.75f);

    _container.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _container.transform, true), EVENT::ENTER);
    _container.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _container.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region �ٸ� �����̳�

    _bridgeConveyor.uiRenderer->Init("research_undeveloped_bridgeConveyor");
    _bridgeConveyor.transform->SetPosition(WINSIZEX / 2 - 250, WINSIZEY / 2 - 200);
    _bridgeConveyor.transform->SetScale(0.75f, 0.75f);

    _bridgeConveyor.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _bridgeConveyor.transform, true), EVENT::ENTER);
    _bridgeConveyor.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _bridgeConveyor.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region ���� ����

    _invertedSorter.uiRenderer->Init("research_undeveloped_invertedSorter");
    _invertedSorter.transform->SetPosition(WINSIZEX / 2 - 425, WINSIZEY / 2 - 250);
    _invertedSorter.transform->SetScale(0.75f, 0.75f);

    _invertedSorter.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _invertedSorter.transform, true), EVENT::ENTER);
    _invertedSorter.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _invertedSorter.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region ��ȭ ����

    _overflowGate.uiRenderer->Init("research_undeveloped_overflowGate");
    _overflowGate.transform->SetPosition(WINSIZEX / 2 - 375, WINSIZEY / 2 - 250);
    _overflowGate.transform->SetScale(0.75f, 0.75f);

    _overflowGate.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _overflowGate.transform, true), EVENT::ENTER);
    _overflowGate.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _overflowGate.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region ƼŸ�� �����̾�

    _titaniumConveyor.uiRenderer->Init("research_lock");
    _titaniumConveyor.transform->SetPosition(WINSIZEX / 2 - 250, WINSIZEY / 2 - 250);
    _titaniumConveyor.transform->SetScale(0.75f, 0.75f);

    _titaniumConveyor.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _titaniumConveyor.transform, true), EVENT::ENTER);
    _titaniumConveyor.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _titaniumConveyor.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region ����ȭ ����

    _underflowGate.uiRenderer->Init("research_undeveloped_underflowGate");
    _underflowGate.transform->SetPosition(WINSIZEX / 2 - 375, WINSIZEY / 2 - 300);
    _underflowGate.transform->SetScale(0.75f, 0.75f);

    _underflowGate.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _underflowGate.transform, true), EVENT::ENTER);
    _underflowGate.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _underflowGate.transform, false), EVENT::EXIT);

#pragma endregion
}

void GameScene::menuInitUI()
{
#pragma region �޴� ȭ��

    _menuImg.uiRenderer->Init("menu_menuimg");
    _menuImg.uiRenderer->SetAlpha(0.95f);
    _menuImg.uiMouseEvent->enable = false;
    _menuImg.transform->SetPosition(WINSIZEX / 2, WINSIZEY / 2);
    _menuImg.SetActive(false);

#pragma endregion

#pragma region �޴� [���ư���] �̹��� & ��ư
    
    _menu_GoBackIdleImg.uiRenderer->Init("menu_goback_idle");
    _menu_GoBackIdleImg.uiMouseEvent->enable = false;
    _menu_GoBackIdleImg.transform->SetPosition(WINSIZEX / 2, WINSIZEY / 2 - 100);
    _menu_GoBackIdleImg.transform->SetScale(1.5f, 1.5f);
    _menu_GoBackIdleImg.SetActive(true);

    _menu_GoBackChoiceImg.uiRenderer->Init("menu_goback_choice");
    _menu_GoBackChoiceImg.uiMouseEvent->enable = false;
    _menu_GoBackChoiceImg.transform->SetPosition(WINSIZEX / 2, WINSIZEY / 2 - 100);
    _menu_GoBackChoiceImg.transform->SetScale(1.5f, 1.5f);
    _menu_GoBackChoiceImg.SetActive(false);

    _menu_GoBackButton.Init();
    _menu_GoBackButton.uiRenderer->Init(330, 80);
    _menu_GoBackButton.transform->SetPosition(WINSIZEX / 2, WINSIZEY / 2 - 100);

    _menu_GoBackButton.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inMenu_ActiveChoiceImg_GoBack, _uiControler,
            true),
        EVENT::ENTER);

    _menu_GoBackButton.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inMenu_ReturnToGameScene, _uiControler,
            &_menu, false),
        EVENT::CLICK);

    _menu_GoBackButton.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inMenu_ActiveChoiceImg_GoBack, _uiControler,
            false),
        EVENT::EXIT);

#pragma endregion

#pragma region �޴� [����] �̹��� & ��ư

#pragma endregion

#pragma region �޴� [���� �� ������] �̹��� & ��ư

    _menu_SaveAndExitIdleImg.uiRenderer->Init("menu_save_and_exit_idle");
    _menu_SaveAndExitIdleImg.uiMouseEvent->enable = false;
    _menu_SaveAndExitIdleImg.transform->SetPosition(WINSIZEX / 2, WINSIZEY / 2 + 100);
    _menu_SaveAndExitIdleImg.transform->SetScale(1.5f, 1.5f);
    _menu_SaveAndExitIdleImg.SetActive(true);

    _menu_SaveAndExitChoiceImg.uiRenderer->Init("menu_save_and_exit_choice");
    _menu_SaveAndExitChoiceImg.uiMouseEvent->enable = false;
    _menu_SaveAndExitChoiceImg.transform->SetPosition(WINSIZEX / 2, WINSIZEY / 2 + 100);
    _menu_SaveAndExitChoiceImg.transform->SetScale(1.5f, 1.5f);
    _menu_SaveAndExitChoiceImg.SetActive(false);
    
    _menu_SaveAndExitButton.Init();
    _menu_SaveAndExitButton.uiRenderer->Init(360, 80);
    _menu_SaveAndExitButton.uiMouseEvent->enable = false;
    _menu_SaveAndExitButton.transform->SetPosition(WINSIZEX / 2, WINSIZEY / 2 + 100);

    _menu_SaveAndExitButton.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inMenu_AcitveChoiceImg_SaveAndExit, _uiControler,
            true),
        EVENT::ENTER);

    _menu_SaveAndExitButton.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inMenu_AcitveRellayEnd, _uiControler,
            &_menu_ReallyEnd, true),
        EVENT::CLICK);

    _menu_SaveAndExitButton.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inMenu_AcitveChoiceImg_SaveAndExit, _uiControler,
            false),
        EVENT::EXIT);

#pragma endregion

#pragma region ������ �����Ͻðڽ��ϱ�? ȭ��

    _menu_ReallyEnd_Img.uiRenderer->Init("menu_reallyendimg");
    _menu_ReallyEnd_Img.uiRenderer->SetAlpha(0.95f);
    _menu_ReallyEnd_Img.uiMouseEvent->enable = false;
    _menu_ReallyEnd_Img.transform->SetPosition(WINSIZEX / 2, WINSIZEY / 2);
    _menu_ReallyEnd_Img.SetActive(false);

#pragma endregion

#pragma region ������ �����Ͻðڽ��ϱ�? [���] �̹��� & ��ư

    _menu_ReallyEnd_Cancle_Idle.uiRenderer->Init("menu_reallyend_cancel_idle");
    _menu_ReallyEnd_Cancle_Idle.uiMouseEvent->enable = false;
    _menu_ReallyEnd_Cancle_Idle.transform->SetPosition(WINSIZEX / 2 - 153, WINSIZEY / 2 + 100);
    _menu_ReallyEnd_Cancle_Idle.transform->SetScale(1.5f, 1.4f);
    _menu_ReallyEnd_Cancle_Idle.SetActive(false);

    _menu_ReallyEnd_Cancle_Choice.uiRenderer->Init("menu_reallyend_cancel_choice");
    _menu_ReallyEnd_Cancle_Choice.uiMouseEvent->enable = false;
    _menu_ReallyEnd_Cancle_Choice.transform->SetPosition(WINSIZEX / 2 - 153, WINSIZEY / 2 + 100);
    _menu_ReallyEnd_Cancle_Choice.transform->SetScale(1.5f, 1.4f);
    _menu_ReallyEnd_Cancle_Choice.SetActive(false);

    _menu_ReallyEnd_Cancle_Button.Init();
    _menu_ReallyEnd_Cancle_Button.uiRenderer->Init(300, 80);
    _menu_ReallyEnd_Cancle_Button.transform->SetPosition(WINSIZEX / 2 - 153, WINSIZEY / 2 + 100);

    _menu_ReallyEnd_Cancle_Button.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inReallyEnd_Active_CancleImg, _uiControler,
            &_menu_ReallyEnd, true),
        EVENT::ENTER);

    _menu_ReallyEnd_Cancle_Button.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inReallyEnd_Return_To_MenuState, _uiControler,
            &_menu_ReallyEnd, false),
        EVENT::CLICK);
    
    _menu_ReallyEnd_Cancle_Button.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inReallyEnd_Active_CancleImg, _uiControler,
            &_menu_ReallyEnd, false),
        EVENT::EXIT);

#pragma endregion

#pragma region ������ �����Ͻðڽ��ϱ�? [Ȯ��] �̹��� & ��ư

    _menu_ReallyEnd_Check_Idle.uiRenderer->Init("menu_reallyend_check_idle");
    _menu_ReallyEnd_Check_Idle.uiMouseEvent->enable = false;
    _menu_ReallyEnd_Check_Idle.transform->SetPosition(WINSIZEX / 2 + 153, WINSIZEY / 2 + 100);
    _menu_ReallyEnd_Check_Idle.transform->SetScale(1.5f, 1.4f);
    _menu_ReallyEnd_Check_Idle.SetActive(false);

    _menu_ReallyEnd_Check_Choice.uiRenderer->Init("menu_reallyend_check_choice");
    _menu_ReallyEnd_Check_Choice.uiMouseEvent->enable = false;
    _menu_ReallyEnd_Check_Choice.transform->SetPosition(WINSIZEX / 2 + 153, WINSIZEY / 2 + 100);
    _menu_ReallyEnd_Check_Choice.transform->SetScale(1.5f, 1.4f);
    _menu_ReallyEnd_Check_Choice.SetActive(false);

    _menu_ReallyEnd_Check_Button.Init();
    _menu_ReallyEnd_Check_Button.uiRenderer->Init(300, 80);
    _menu_ReallyEnd_Check_Button.transform->SetPosition(WINSIZEX / 2 + 153, WINSIZEY / 2 + 100);

    _menu_ReallyEnd_Check_Button.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inReallyEnd_Active_CheckImg, _uiControler,
            &_menu_ReallyEnd, true),
        EVENT::ENTER);
    
    _menu_ReallyEnd_Check_Button.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inReallyEnd_Return_To_TilteScene, _uiControler,
            "title"),
        EVENT::CLICK);
    
    _menu_ReallyEnd_Check_Button.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inReallyEnd_Active_CheckImg, _uiControler,
            &_menu_ReallyEnd, false),
        EVENT::EXIT);

#pragma endregion

}

void GameScene::menuUpdate()
{
    // �޴�
    _menu_GoBackIdleImg.Update();
    _menu_GoBackChoiceImg.Update();
    _menu_GoBackButton.Update();

    _menu_SettingIdleImg.Update();
    _menu_SettingChoiceImg.Update();
    _menu_SettingButton.Update();

    _menu_SaveAndExitIdleImg.Update();
    _menu_SaveAndExitChoiceImg.Update();
    _menu_SaveAndExitButton.Update();

    // ������ �����Ͻðڽ��ϱ�?
    _menu_ReallyEnd_Check_Idle.Update();
    _menu_ReallyEnd_Check_Choice.Update();
    _menu_ReallyEnd_Check_Button.Update();

    _menu_ReallyEnd_Cancle_Idle.Update();
    _menu_ReallyEnd_Cancle_Choice.Update();
    _menu_ReallyEnd_Cancle_Button.Update();
}

void GameScene::menuRender()
{
    // �޴�
    _menuImg.Render();

    _menu_GoBackIdleImg.Render();
    _menu_GoBackChoiceImg.Render();
    _menu_GoBackButton.Render();

    _menu_SettingIdleImg.Render();
    _menu_SettingChoiceImg.Render();
    _menu_SettingButton.Render();

    _menu_SaveAndExitIdleImg.Render();
    _menu_SaveAndExitChoiceImg.Render();
    _menu_SaveAndExitButton.Render();

    // ������ �����Ͻðڽ��ϱ�?
    _menu_ReallyEnd_Img.Render();

    _menu_ReallyEnd_Check_Idle.Render();
    _menu_ReallyEnd_Check_Choice.Render();
    _menu_ReallyEnd_Check_Button.Render();

    _menu_ReallyEnd_Cancle_Idle.Render();
    _menu_ReallyEnd_Cancle_Choice.Render();
    _menu_ReallyEnd_Cancle_Button.Render();
}

void GameScene::SetProjectileManager()
{
	_projectileManager = new GameObject();
	_projectileManager->AddComponent(new ProjectileManager());
	_projectileManager->GetComponent<ProjectileManager>()->Init();
	_player->controler->SetProjectileManager(_projectileManager->GetComponent<ProjectileManager>());
    _propFactory->LinkProjectileManager(_projectileManager->GetComponent<ProjectileManager>());
}

void GameScene::SetCore()
{
	_core = new Core();
	_core->Init();
	_core->tag = TAGMANAGER->GetTag("prop");
	_core->transform->SetPosition(25 * TILESIZE + 16, 36 * TILESIZE + 16);
	_core->collider->RefreshPartition();
    _core->coreComponent->LinkResourceManager(_resourceManager);
    _core->coreComponent->LinkGameInfo(_gameInfo);
}

void GameScene::SetEnemyManager()
{
	_enemyManager = new GameObject();
	_enemyManager->AddComponent(new EnemyManager());
	_enemyManager->GetComponent<EnemyManager>()->SetTestCoreTransform(_core);
	_enemyManager->GetComponent<EnemyManager>()->SetProjectileManager(_projectileManager->GetComponent<ProjectileManager>());
    _enemyManager->GetComponent<EnemyManager>()->SetAstar(_aStar);
	_enemyManager->GetComponent<EnemyManager>()->Init();
    _aStar->LinkEnemyManager(_enemyManager->GetComponent<EnemyManager>());
	_uiControler->SetEnemyManager(_enemyManager->GetComponent<EnemyManager>());
	_enemyManager->GetComponent<EnemyManager>()->SetPlayerTransform(_player->transform);
    _propFactory->LinkEnemyManager(_enemyManager->GetComponent<EnemyManager>());
}

void GameScene::SetCameraControler()
{
    _cameraControler = new GameObject();
    _cameraControler->AddComponent(new CameraControler());
    _cameraControler->GetComponent<CameraControler>()->Init();
    _cameraControler->GetComponent<CameraControler>()->SetPlayerTr(_player->transform);
}

void GameScene::SetGameUIInit()
{
	_wavePane.Init();
	_wavePane.uiRenderer->Init("uiwavepane");
    _wavePane.uiMouseEvent->enable = false;
	_wavePane.transform->SetPosition(183, 45);

	_enemyWaveSkip.Init();
	_enemyWaveSkip.uiRenderer->Init("waveskipui");
	_enemyWaveSkip.transform->SetScale(1.3, 1.3);
	_enemyWaveSkip.uiMouseEvent->enable = false;
	_enemyWaveSkip.transform->SetPosition(390.5f, 45.7f);

	_enemyWaveSkipButton.Init();
	_enemyWaveSkipButton.uiRenderer->Init(57, 100);
	_enemyWaveSkipButton.transform->SetPosition(392, 45);
	_enemyWaveSkipButton.SetActive(true);

	_enemyWaveSkipClick.Init();
	_enemyWaveSkipClick.uiRenderer->Init("waveskipuienter");
	_enemyWaveSkipClick.transform->SetScale(1.3, 1.3);
	_enemyWaveSkipClick.uiMouseEvent->enable = false;
	_enemyWaveSkipClick.transform->SetPosition(390.5f, 45.7f);

	_enemyWaveSkipButton.uiMouseEvent->RegistCallback(
		std::bind(&UIControler::EnemyWaveSkip, _uiControler), EVENT::ENTER);

	_enemyWaveSkipButton.uiMouseEvent->RegistCallback(
		std::bind(&UIControler::EnemyWaveSkipClick, _uiControler), EVENT::CLICK);

	_enemyWaveSkipButton.uiMouseEvent->RegistCallback(
		std::bind(&UIControler::EnemyWaveSkipExit, _uiControler), EVENT::EXIT);
}

void GameScene::InGameUIUpdate()
{
	_wavePane.Update();
	_enemyWaveSkip.Update();
	_enemyWaveSkipButton.Update();
	_enemyWaveSkipClick.Update();
}

void GameScene::InGameUIRender()
{
	_wavePane.Render();
	_enemyWaveSkipClick.Render();
	_enemyWaveSkip.Render();
	_enemyWaveSkipButton.Render();
	_enemyWaveSkipClick.Render();
	
	wstring second = to_wstring(_enemyManager->GetComponent<EnemyManager>()->GetTimeSecond());
	wstring minute = to_wstring(_enemyManager->GetComponent<EnemyManager>()->GetTimeMinute());
	wstring wave = to_wstring(_enemyManager->GetComponent<EnemyManager>()->GetCurWave());

	D2DRENDERER->RenderText(150, 5, L"�ܰ�", 22, L"fontello", D2DRenderer::DefaultBrush::Yellow);
	D2DRENDERER->RenderText(202, 7, wave, 22, L"mindustry", D2DRenderer::DefaultBrush::Yellow);
	D2DRENDERER->RenderText(220, 7, L"/10", 22, L"mindustry", D2DRenderer::DefaultBrush::Yellow);
	D2DRENDERER->RenderText(150, 30, L"���� �ܰ����", 20, L"fontello", D2DRenderer::DefaultBrush::Yellow);

	D2DRENDERER->RenderText(155, 58, minute, 20, L"mindustry", D2DRenderer::DefaultBrush::White);
	D2DRENDERER->RenderText(173, 55, L"��", 20, L"fontello", D2DRenderer::DefaultBrush::White);
	D2DRENDERER->RenderText(198, 58, second, 20, L"mindustry", D2DRenderer::DefaultBrush::White);
	D2DRENDERER->RenderText(230, 55, L"��", 20, L"fontello", D2DRenderer::DefaultBrush::White);
}

void GameScene::InGameUIClip()
{
	/////////////////// 07. 20 ���Ӽ� Wave UI && Player UI ���� ////////////////////////////
	{
		CLIPMANAGER->AddClip("uiwavepane", "sprites/ingameui/uiwavepane.png", 367, 100);
		CLIPMANAGER->AddClip("waveskipui", "sprites/ingameui/waveskipui.png", 36, 77);
		CLIPMANAGER->AddClip("waveskipuienter", "sprites/ingameui/waveskipuienter.png", 36, 77);
	}
}

void GameScene::StringRender()
{
	//wstring wstr = L"player speed : ";
	//wstr.append(to_wstring(_player->controler->GetSpeed()));
	//D2DRENDERER->RenderText(100, 100, wstr, 20, L"�������", D2DRenderer::DefaultBrush::White);

	//wstring wstrangle = L"Angle : ";
	//wstrangle.append(to_wstring(_player->controler->GetTargetAngle()));
	//D2DRENDERER->RenderText(100, 150, wstrangle, 20, L"�������", D2DRenderer::DefaultBrush::White);

	//wstring time = L"MusicTime: ";
	//time.append(to_wstring(_musicTime));
	//D2DRENDERER->RenderText(10, 140, time, 30, L"fontello", D2DRenderer::DefaultBrush::Blue);

	/* ���ʹ� ���� �۾� ����, ���� ����*/
	/*wstring hp = L"HP : ";
	hp.append(to_wstring(_player->GetComponent<PlayerControler>()->GetHp()));
	D2DRENDERER->RenderText(10, 150, hp, 30, L"fontello", D2DRenderer::DefaultBrush::Blue);

    /*wstring mineCount = L"mineCount";
    mineCount.append(to_wstring(_mineCount));
    D2DRENDERER->RenderText(WINSIZEX / 2 - 50, 10, mineCount, 20, L"fontello", D2DRenderer::DefaultBrush::White);*/
}
