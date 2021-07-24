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
    // 자원추가 (시영)
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
	/*인게임 맵 초기화 -> 유림*/
	_gameMap = new GameMap;
	_gameMap->Init();

    _aStar = new Astar();
    _aStar->LinkGameMap(_gameMap);
    _aStar->LinkPropContainer(_propContainer);

    _uiControler->gameMap = _gameMap;
    _propFactory->LinkGameMap(_gameMap);
	//자원 UI 초기화
	ResourcesInit();
	/*===================================*/

    InitCategoryUI();
    InitPropUI();

    /* 시영 */
    // 연구 Init
    researchInitUI();
    // 메뉴 Init
    menuInitUI();

    // BOOL 변수 초기화 
    {
        // 커서 
        _isMineral = true;

        /* 연구부분 */
        _lockDes = false;
        _research = false;
        _inDetail = false;

        _all_Resources_State = true;
        _all_Resources_Count = 1;
        // true = 열려있는 상태
        // false = 닫혀있는 상태

        /* 메뉴부분 */
        _menu = false;
        _menu_ReallyEnd = false;
    }

    // _uiControler 이미지 연동
    {
        _uiControler->isMineral = &_isMineral;
        /* 게임화면 내에서 카테고리 아이콘에 ENTER 됐을 경우 나오는 회색 이미지 */
        _uiControler->coreDBIcon = &_coreDBIcon;
        _uiControler->researchIcon = &_researchIcon;
        _uiControler->inGame_TouchToIcon = &_inGame_TouchToIcon;

        // 연구
        /* 전체 자원 버튼 (회색) */
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

        /* 연구 */
        _uiControler->research_goBackIdleImg = &_research_goBackIdleImg;
        _uiControler->research_goBackChoiceImg = &_research_goBackChoiceImg;
        _uiControler->coreDBIdleImg = &_coreDBIdleImg;
        _uiControler->coreDBChoiceImg = &_coreDBChoiceImg;

        /* 상세보기 */
        _uiControler->detailDes_GoBackIdleImg = &_detailDes_goBackIdleImg;
        _uiControler->detailDes_GoBackChoiceImg = &_detailDes_goBackChoiceImg;

        /* 메뉴부분 */
        _uiControler->menu_GoBackIdleImg = &_menu_GoBackIdleImg;
        _uiControler->menu_GoBackChoiceImg = &_menu_GoBackChoiceImg;
        _uiControler->menu_SettingIdleImg = &_menu_SettingIdleImg;
        _uiControler->menu_SettingChoiceImg = &_menu_SettingChoiceImg;
        _uiControler->menu_SaveAndExitIdleImg = &_menu_SaveAndExitIdleImg;
        _uiControler->menu_SaveAndExitChoiceImg = &_menu_SaveAndExitChoiceImg;
        _uiControler->menu_SaveAndExitButton = &_menu_SaveAndExitButton;

        /* 정말로 종료하시겠습니까? 부분 */
        _uiControler->menu_ReallyEnd_Img = &_menu_ReallyEnd_Img;
        _uiControler->menu_ReallyEnd_Check_Idle = &_menu_ReallyEnd_Check_Idle;
        _uiControler->menu_ReallyEnd_Check_Choice = &_menu_ReallyEnd_Check_Choice;
        _uiControler->menu_ReallyEnd_Cancle_Idle = &_menu_ReallyEnd_Cancle_Idle;
        _uiControler->menu_ReallyEnd_Cancle_Choice = &_menu_ReallyEnd_Cancle_Choice;
    }

    #pragma region 연구 상태에서 [돌아가기] 이미지, 버튼

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

    #pragma region 연구 상태에서 [코어 DB] 이미지, 버튼

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
    // 코어 DB 화면 구성할 때 불 값으로 연결시켜주기 (현재 임시로 _research를 꺼주고 있다)
    _coreDBButton.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ReturnToCoreDBScene, _uiControler, &_research, false), EVENT::CLICK);
    _coreDBButton.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveCoreDBImg, _uiControler, false), EVENT::EXIT);

    #pragma endregion

    #pragma region 상세 설명 상태에서 [돌아가기] 이미지, 버튼

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
	/* 플레이어 부분 초기화 -> 유림 */
	PlayerInit();
    _respawn->LinkPlayer(_player->controler);
	/*===================================================================== */

    /* 게임신 에너미 관련 작업 함수, by 민재. 삭제 금지 */
	SetProjectileManager();
	SetCore();
	SetEnemyManager();
	SetCameraControler();
	SetGameUIInit();

	_uiControler->enemyWaveSkip = &_enemyWaveSkip;
	_uiControler->enemyWaveSkipClick = &_enemyWaveSkipClick;

    /* 사운드 작업 광철 210718 */
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
    //07-19 플레이어와 UI간의 마우스 클릭 우선순위때문에 UI업데이트 위로 올림
    //카테고리 아이콘 업데이트
    {
        _defenseIcon.Update();
        _railIcon.Update();
        _turretIcon.Update();
        _productionIcon.Update();

        // 코어 데이터베이스, 연구 아이콘 추가 (시영)
        _coreDBIcon.Update();
        _researchIcon.Update();

        // 게임화면 내에서 카테고리 아이콘에 ENTER 됐을 경우 나오는 회색 이미지 (시영)
        _inGame_TouchToIcon.Update();
    }

    //설치물 아이콘 업데이트
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

    /* 시영 */
    // 메뉴 부분 Update
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

    // 연구 부분 Update
    {
        // 전체 자원 개수 파악
        if (_gameInfo->GetResourceAmount(COPPER) >= 1)
            _all_Resources_Count = 1;

        if (_gameInfo->GetResourceAmount(COPPER) >= 1 && _gameInfo->GetResourceAmount(LEAD) >= 1)
            _all_Resources_Count = 2;

        if (_gameInfo->GetResourceAmount(COPPER) >= 1 && _gameInfo->GetResourceAmount(LEAD) >= 1 && _gameInfo->GetResourceAmount(SCRAP) >= 1)
            _all_Resources_Count = 3;

        // 광물 변수 카운트 출력 - 구리
        if (_gameInfo->GetResourceAmount(COPPER) >= 1)
            _all_Resources_Copper_Count = to_wstring(_gameInfo->GetResourceAmount(COPPER));

        // 광물 변수 카운트 출력 - 납
        if (_gameInfo->GetResourceAmount(LEAD) >= 1)
            _all_Resources_Lead_Count = to_wstring(_gameInfo->GetResourceAmount(LEAD));

        // 광물 변수 카운트 출력 - 고철
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

	/* 플레이어 부분*/
	_player->Update();
    // 플레이어 그림자 (시영 추가) ==
    _playerShadow->Update();
    _playerShadow->transform->SetPosition(_player->transform->GetX() - 50, _player->transform->GetY() + 50);
    // ============================
	_playerWeaponL->Update();
	_playerWeaponR->Update();
	_playerCell->Update();
	_projectileManager->Update();
    _cameraControler->Update();

	// 광물 부분 -> 유림 210719
	ResourcesUpdate();
	//========================================
	_cameraControler->Update();
    _buildingCategoryFrame.Update();

    //카테고리 아이콘 업데이트 
    _propPreview.Update();
	_gameMap->Update();
	//========================================
    _categorySelect.Update();
    _propSelect.Update();
	_core->Update();

	//07.20 민재 인 게임 Wave UI && Player UI 작업//
	_enemyManager->Update();

    /* 사운드 작업 광철 210718 */
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
	//플레이어 관련 렌더 -> 유림
	{
		_player->transform->GetChild(4)->gameObject->Render();
		_player->Render();
        // 플레이어 그림자 (시영 추가) ==
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

    //카테고리 아이콘 렌더
    {
        // 게임화면 내에서 카테고리 아이콘에 ENTER 됐을 경우 나오는 회색 이미지 (시영)
        _inGame_TouchToIcon.Render();

        _buildingCategoryFrame.Render();
        _defenseIcon.Render();
        _railIcon.Render();
        _turretIcon.Render();
        _productionIcon.Render();
        // 코어 데이터베이스, 연구 아이콘 추가 (시영)
        _coreDBIcon.Render();
        _researchIcon.Render();
    }
    //설치물 아이콘 렌더
    {
        _copperWallIcon.Render();
        _mechanicDrillIcon.Render();
        _duoIcon.Render();
        _conveyorIcon.Render();
    }
    _categorySelect.Render();
    _propSelect.Render();

	InGameUIRender();
    //07.20 민재 인 게임 Wave UI && Player UI 작업//
	//자원UI 렌더 -> 유림 (210719)
	ResourcesRender();
	_player->controler->playerUI.Render();
	_player->controler->playerHpUIPane.Render();
	_player->controler->playerHpUI.Render();
	_player->controler->playerHpUIAlpha.Render();

    /* 시영 */
    // 연구
    if (_research) researchRender();
    if (_research && _all_Resources_State)
    {
        if (_all_Resources_Count == 1)
        {
            _all_Resources_Open1_Img.Render();

            D2DRENDERER->RenderText(WINSIZEX / 2 - 620, WINSIZEY / 2 - 360, _all_Resources_Copper_Count, 14, L"mindustry", D2DRenderer::DefaultBrush::White);
            _all_Resources_Mineral[0].Render();
            D2DRENDERER->RenderText(WINSIZEX / 2 - 550, WINSIZEY / 2 - 360, L"구리", 14, L"fontello", D2DRenderer::DefaultBrush::White);
        }

        if (_all_Resources_Count == 2)
        {
            _all_Resources_Open2_Img.Render();

            D2DRENDERER->RenderText(WINSIZEX / 2 - 620, WINSIZEY / 2 - 360, _all_Resources_Copper_Count, 14, L"mindustry", D2DRenderer::DefaultBrush::White);
            D2DRENDERER->RenderText(WINSIZEX / 2 - 620, WINSIZEY / 2 - 330, _all_Resources_Lead_Count, 14, L"mindustry", D2DRenderer::DefaultBrush::White);
            _all_Resources_Mineral[0].Render();
            _all_Resources_Mineral[1].Render();
            D2DRENDERER->RenderText(WINSIZEX / 2 - 550, WINSIZEY / 2 - 360, L"구리", 14, L"fontello", D2DRenderer::DefaultBrush::White);
            D2DRENDERER->RenderText(WINSIZEX / 2 - 550, WINSIZEY / 2 - 330, L"납", 14, L"fontello", D2DRenderer::DefaultBrush::White);
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
            D2DRENDERER->RenderText(WINSIZEX / 2 - 550, WINSIZEY / 2 - 360, L"구리", 14, L"fontello", D2DRenderer::DefaultBrush::White);
            D2DRENDERER->RenderText(WINSIZEX / 2 - 550, WINSIZEY / 2 - 330, L"납", 14, L"fontello", D2DRenderer::DefaultBrush::White);
            D2DRENDERER->RenderText(WINSIZEX / 2 - 550, WINSIZEY / 2 - 300, L"고철", 14, L"fontello", D2DRenderer::DefaultBrush::White);
        }
    }

    // 메뉴
    if (_menu) menuRender();

	/* ================================여기 만지지 마세요 ========================================*/
    //210719 유림 수정
	StringRender();

    // 마우스 관련 작업 (시영)
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
	//카테고리 아이콘 클립
	{
		CLIPMANAGER->AddClip("turret_icon", "icons/turret.png", 32, 32);
		CLIPMANAGER->AddClip("production_icon", "icons/production.png", 32, 32);
		CLIPMANAGER->AddClip("rail_icon", "icons/distribution.png", 32, 32);
		CLIPMANAGER->AddClip("defense_icon", "icons/defense.png", 32, 32);
        // 코어 데이터베이스, 연구 아이콘 추가 (시영)
        CLIPMANAGER->AddClip("core_db_icon", "sprites/game/book.png", 14, 14);
        CLIPMANAGER->AddClip("research_icon", "sprites/game/tree.png", 14, 14);

        // 게임화면 내에서 카테고리 아이콘에 ENTER 됐을 경우 나오는 회색 이미지
        CLIPMANAGER->AddClip("in_game_touch_to_icon", "sprites/game/in_game_touch_to_icon.png", 48, 48);
	}

	//설치물 아이콘 클립
	{
		CLIPMANAGER->AddClip("duo", "sprites/blocks/turrets/duo-icon.png", 32, 32);
		CLIPMANAGER->AddClip("mechanical_drill", "sprites/blocks/drills/mechanical-drill-icon.png", 64, 64);
		CLIPMANAGER->AddClip("conveyor", "sprites/blocks/distribution/conveyors/conveyor-0-0.png", 32, 32);
		CLIPMANAGER->AddClip("copper_wall", "sprites/blocks/walls/copper-wall.png", 32, 32);
	}

    //컨베이어 벨트 클립
    {
        CLIPMANAGER->AddClip("conveyor_I", "sprites/blocks/distribution/conveyors/conveyor-I.png", 128, 32, 4, 1, 0.06f);
        CLIPMANAGER->AddClip("conveyor_L", "sprites/blocks/distribution/conveyors/conveyor-L.png", 128, 32, 4, 1, 0.06f);
        CLIPMANAGER->AddClip("conveyor_L2", "sprites/blocks/distribution/conveyors/conveyor-L2.png", 128, 32, 4, 1, 0.06f);
        CLIPMANAGER->AddClip("conveyor_T", "sprites/blocks/distribution/conveyors/conveyor-T.png", 128, 32, 4, 1, 0.06f);
        CLIPMANAGER->AddClip("conveyor_T2", "sprites/blocks/distribution/conveyors/conveyor-T2.png", 128, 32, 4, 1, 0.06f);
        CLIPMANAGER->AddClip("conveyor_T3", "sprites/blocks/distribution/conveyors/conveyor-T3.png", 128, 32, 4, 1, 0.06f);
        CLIPMANAGER->AddClip("conveyor_cross", "sprites/blocks/distribution/conveyors/conveyor-cross.png", 128, 32, 4, 1, 0.06f);
    }

    //드릴 클립
    {
        CLIPMANAGER->AddClip("drill_body", "sprites/blocks/drills/mechanical-drill.png", 64, 64);
        CLIPMANAGER->AddClip("drill_top", "sprites/blocks/drills/mechanical-drill-top.png", 64, 64);
        CLIPMANAGER->AddClip("drill_rotator", "sprites/blocks/drills/mechanical-drill-rotator.png", 64, 64);
    }
    //터렛 클립
    {
        CLIPMANAGER->AddClip("duo_head", "sprites/blocks/turrets/duo-head.png", 32, 32);
        CLIPMANAGER->AddClip("duo_base", "sprites/blocks/turrets/bases/block-1.png", 32, 32);
    }
    //그 이외 클립
    {
        CLIPMANAGER->AddClip("conveyor_arrow", "sprites/blocks/extra/conveyor-arrow.png", 96, 96);
        CLIPMANAGER->AddClip("copper", "sprites/items/item-copper.png", 32, 32);
        CLIPMANAGER->AddClip("lead", "sprites/items/item-lead.png", 32, 32);
    }
	//플레이어 클립
	{
		CLIPMANAGER->AddClip("player", "player/alpha.png", 48, 48);
		CLIPMANAGER->AddClip("enemy_projectile", "sprites/units/weapons/missiles-mount.png", 48, 48);
		CLIPMANAGER->AddClip("bullet", "sprites/effects/bullet.png", 52, 52);
		CLIPMANAGER->AddClip("player_weapon_L", "player/small-basic-weapon-L.png", 48, 48);
		CLIPMANAGER->AddClip("player_weapon_R", "player/small-basic-weapon-R.png", 48, 48);
	}
	CLIPMANAGER->AddClip("button_select", "sprites/ui/button-select.10.png", 52, 52);

    /* 시영 */
    /* 연구 클립 */
    {
        // 전체 자원
        CLIPMANAGER->AddClip("all_resources_open_1", "sprites/game/all_resources_open_1.png", 224, 104);
        CLIPMANAGER->AddClip("all_resources_open_2", "sprites/game/all_resources_open_2.png", 224, 128);
        CLIPMANAGER->AddClip("all_resources_open_3", "sprites/game/all_resources_open_3.png", 224, 152);
        CLIPMANAGER->AddClip("all_resources_close", "sprites/game/all_resources_close.png", 224, 80);
        CLIPMANAGER->AddClip("all_resources_text", "sprites/game/all_resources_text.png", 136, 20);
        CLIPMANAGER->AddClip("all_resources_event", "sprites/game/all_resources_event.png", 200, 51);

        // 연구
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

        /* SHUNG 210718 연구 누를 경우 나오는 UI (뒤로가기, 코어 데이터 베이스) */
        CLIPMANAGER->AddClip("research_gobackidle", "sprites/game/gobackidle.png", 210, 64);
        CLIPMANAGER->AddClip("research_gobackchoice", "sprites/game/gobackchoice.png", 210, 64);
        CLIPMANAGER->AddClip("research_coredbidle", "sprites/game/core_db_idle.png", 210, 64);
        CLIPMANAGER->AddClip("research_coredbchoice", "sprites/game/core_db_choice.png", 210, 64);
    }

    /* 메뉴 클립 */
    {
        CLIPMANAGER->AddClip("menu_menuimg", "sprites/game/menu.png", WINSIZEX, WINSIZEY);
        
        CLIPMANAGER->AddClip("menu_goback_idle", "sprites/game/menu_gobackidle.png", 220, 55);
        CLIPMANAGER->AddClip("menu_goback_choice", "sprites/game/menu_gobackchoice.png", 220, 55);

        CLIPMANAGER->AddClip("menu_setting_idle", "sprites/game/menu_setting_idle.png", 220, 55);
        CLIPMANAGER->AddClip("menu_setting_choice", "sprites/game/menu_setting_choice.png", 220, 55);

        CLIPMANAGER->AddClip("menu_save_and_exit_idle", "sprites/game/menu_save_and_exit_idle.png", 240, 55);
        CLIPMANAGER->AddClip("menu_save_and_exit_choice", "sprites/game/menu_save_and_exit_choice.png", 240, 55);

        // 정말로 종료하시겠습니까?
        CLIPMANAGER->AddClip("menu_reallyendimg", "sprites/game/menu_reallyend.png", WINSIZEX, WINSIZEY);

        CLIPMANAGER->AddClip("menu_reallyend_cancel_idle", "sprites/game/menu_reallyend_cancel_idle.png", 200, 54);
        CLIPMANAGER->AddClip("menu_reallyend_cancel_choice", "sprites/game/menu_reallyend_cancel_choice.png", 200, 54);

        CLIPMANAGER->AddClip("menu_reallyend_check_idle", "sprites/game/menu_reallyend_check_idle.png", 200, 54);
        CLIPMANAGER->AddClip("menu_reallyend_check_choice", "sprites/game/menu_reallyend_check_choice.png", 200, 54);

    }

	//// ENEMY & CORE 클립 작업 민재 /////
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
    * 버튼 콜백함수 등록방법
    * RegistCallback 매개변수(std::bind(&클래스명::함수명, 클래스의 인스턴스, 매개변수....), 등록이벤트 종류);
    * 등록이벤트 종류
    * 1.ENTER : 마우스가 진입했을때
    * 2.EXIT : 마우스가 빠져나갔을때
    * 3.CLICK : 마우스로 클릭했을때
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

    // 코어 데이터베이스 아이콘 추가 (시영)
    _coreDBIcon.uiRenderer->Init("core_db_icon");
    _coreDBIcon.transform->SetScale(2.5f, 2.5f);
    _coreDBIcon.transform->SetPosition(WINSIZEX / 2 + 435, WINSIZEY - 25);

    //_coreDBIcon.uiMouseEvent->RegistCallback(
    //    std::bind(&UIControler::inGame_Acitve_Choice_Img, _uiControler,
    //        &_coreDBIcon, &_isMineral, true),
    //    EVENT::ENTER);

    /* 코어 데이터베이스 클릭 아직 없음 (07/23) */

    //_coreDBIcon.uiMouseEvent->RegistCallback(
    //    std::bind(&UIControler::inGame_Acitve_Choice_Img, _uiControler,
    //        &_coreDBIcon, &_isMineral, false),
    //    EVENT::EXIT);

    // 연구 아이콘 추가 (시영)
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

    // 게임화면 내에서 카테고리 아이콘에 ENTER 됐을 경우 나오는 회색 이미지 (시영)
    _inGame_TouchToIcon.uiRenderer->Init("in_game_touch_to_icon");
    _inGame_TouchToIcon.SetActive(false);

    _categorySelect.uiRenderer->Init("button_select");
    _categorySelect.transform->SetPosition(_turretIcon.transform->GetX(), _turretIcon.transform->GetY());
}

void GameScene::InitPropUI()
{
    //터렛 아이콘 초기화
    {
        _duoIcon.uiRenderer->Init("duo");
        _duoIcon.transform->SetPosition(PROP_UI_STARTX, PROP_UI_STARTY);
        _duoIcon.uiMouseEvent->RegistCallback(
            std::bind(&UIControler::ClickPropIcon, _uiControler, &_duoIcon, 0), EVENT::CLICK);
        _turretIconV.push_back(&_duoIcon);

    }

    //드릴 아이콘 초기화
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

    //레일 아이콘 초기화
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

    //벽 아이콘 초기화
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
	//플레이어 클립
	CLIPMANAGER->AddClip("player", "player/alpha.png", 48, 48);
	//CLIPMANAGER->AddClip("enemy_projectile", "sprites/units/weapons/missiles-mount.png", 48, 48);
	CLIPMANAGER->AddClip("bullet", "sprites/effects/bullet.png", 52, 52);
	CLIPMANAGER->AddClip("player_weapon_L", "player/small-basic-weapon-L.png", 48, 48);
	CLIPMANAGER->AddClip("player_weapon_R", "player/small-basic-weapon-R.png", 48, 48);
	CLIPMANAGER->AddClip("player_cell", "player/alpha-cell.png", 48, 48);
	CLIPMANAGER->AddClip("player_fire_circle", "player/alpha_fire_circle.png", 17, 17);
	CLIPMANAGER->AddClip("player_fire", "player/alpha_fire.png", 30, 30);
    // 플레이어 그림자 추가 (시영)
    CLIPMANAGER->AddClip("player_shadow", "player/shadow/alpha_shadow.png", 48, 48);

	//자원 클립
	CLIPMANAGER->AddClip("copperUI", "sprites/items/item-copper.png", 32, 32);
	CLIPMANAGER->AddClip("leadUI", "sprites/items/item-lead.png", 32, 32);
    //자원 클립 - 고철 추가 (시영)
    CLIPMANAGER->AddClip("scrapUI", "sprites/game/item-scrap.png", 32, 32);
}

void GameScene::PlayerInit()
{
	/* 플레이어 부분 초기화 -> 유림 */
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

	//플레이어 포신 유림.
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

	_player->transform->AddChild(_playerWeaponL->transform);		//웨폰L 자식 1
	_player->transform->AddChild(_playerWeaponR->transform);		//웨폰R 자식 2
	_player->transform->AddChild(_playerCell->transform);			//플레이어 부선기 자식3
	_player->transform->AddChild(_playerFireCircle->transform);		//플레이어 불꽃 하얀부분 자식4
	_player->transform->AddChild(_playerFire->transform);			//플레이어 불꽃 자식5
	//부선기만 이곳에서 렌더하므로 초기화
	_player->transform->GetChild(3)->SetPosition(_player->transform->GetX() , _player->transform->GetY());
    // 플레이어 그림자 (시영 추가) =================
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
    // 12시 방향 자원 표시
    // 검은색 배경화면
	D2DRenderer::GetInstance()->FillRectangle(_resoucesUIBackGround, D2D1::ColorF::Black, 0.7f);
	_resourcesUI[0].Render();   // 구리 이미지
	_resourcesUI[1].Render();   // 납 이미지

	wstring copperAmount;
	wstring leadAmount;

	if (_gameInfo->GetResourceAmount(COPPER) < 1000)
	{
        // 구리 현재 카운트 출력
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
        // 납 숫자 출력
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
    // 배경화면
    _research_bg.Update();

    // 전체 자원
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
    // 배경화면
    _research_bg.Render();

    // 전체 자원
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

    /* Lock, Choice, 회색 Choice */
    _lockImg.Render();
    _choiceImg.Render();

    /* 설명 Render - 설명이 버튼을 가리게끔 출력되기 위해 놓는다.*/
    _coreBasicDescription.Render();

    // i에 마우스 충돌이 일어났을 경우에 나오는 회색선택창의 render
    _inResearchChoiceImg.Render();

    /* 기본 설명에서의 i가 연구상태 내에서 회색선택창 위에 올라와야 하므로 여기다 넣는다. */
    _coreDetailDescriptionButton.Render();

    //
    _research_goBackIdleImg.Render();
    _research_goBackChoiceImg.Render();
    _research_goBackButton.Render();
    _coreDBIdleImg.Render();
    _coreDBChoiceImg.Render();
    _coreDBButton.Render();

    /* 상세 설명 넣으세요 */
    _coreDetailDescriptionImg.Render();

    _detailDes_goBackIdleImg.Render();
    _detailDes_goBackChoiceImg.Render();
    _detailDes_goBackButton.Render();
}

void GameScene::researchInitUI()
{
#pragma region 전체 자원

    // 전체 자원 [열림]
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

    // 전체 자원 [닫힘]
    _all_Resources_Close_Img.uiRenderer->Init("all_resources_close");
    _all_Resources_Close_Img.uiMouseEvent->enable = false;
    _all_Resources_Close_Img.transform->SetPosition(WINSIZEX / 2 - 560, WINSIZEY / 2 - 380);
    _all_Resources_Close_Img.SetActive(false);

    // 전체 자원 이미지 (충돌 - 회색)
    _all_Resources_Img.uiRenderer->Init("all_resources_event");
    _all_Resources_Img.uiMouseEvent->enable = false;
    _all_Resources_Img.transform->SetPosition(WINSIZEX / 2 - 560, WINSIZEY / 2 - 380);
    _all_Resources_Img.SetActive(false);

    // 전체 자원 텍스트
    _all_Resources_Text.uiRenderer->Init("all_resources_text");
    _all_Resources_Text.uiMouseEvent->enable = false;
    _all_Resources_Text.transform->SetPosition(WINSIZEX / 2 - 580, WINSIZEY / 2 - 378);
    _all_Resources_Text.SetActive(true);

    // 전체 자원 버튼
    _all_Resources_Button.Init();
    _all_Resources_Button.uiRenderer->Init(210, 50);
    _all_Resources_Button.transform->SetPosition(WINSIZEX / 2 - 560, WINSIZEY / 2 - 380);

    // 전체 자원 버튼 마우스 이벤트
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

    // 전체 자원 광물 이미지 - 구리
    _all_Resources_Mineral[0].Init();
    _all_Resources_Mineral[0].uiRenderer->Init("copperUI");
    _all_Resources_Mineral[0].uiMouseEvent->enable = false;
    _all_Resources_Mineral[0].transform->SetPosition(WINSIZEX / 2 - 575, WINSIZEY / 2 - 345);

    // 전체 자원 광물 이미지 - 납
    _all_Resources_Mineral[1].Init();
    _all_Resources_Mineral[1].uiRenderer->Init("leadUI");
    _all_Resources_Mineral[1].uiMouseEvent->enable = false;
    _all_Resources_Mineral[1].transform->SetPosition(WINSIZEX / 2 - 575, WINSIZEY / 2 - 315);
    
    // 전체 자원 광물 이미지 - 고철
    _all_Resources_Mineral[2].Init();
    _all_Resources_Mineral[2].uiRenderer->Init("scrapUI");
    _all_Resources_Mineral[2].uiMouseEvent->enable = false;
    _all_Resources_Mineral[2].transform->SetPosition(WINSIZEX / 2 - 575, WINSIZEY / 2 - 285);
   
#pragma endregion

#pragma region 배경화면

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

#pragma region 연구상태 내에서 기본설명 볼 때 i에 마우스 충돌이 일어났을 경우에 나오는 회색선택창

    _inResearchChoiceImg.uiRenderer->Init("in_research_choice");
    _inResearchChoiceImg.uiMouseEvent->enable = false;
    _inResearchChoiceImg.transform->SetPosition(WINSIZEX / 2, WINSIZEY / 2);
    _inResearchChoiceImg.SetActive(false);

#pragma endregion

#pragma region 코어 : 조각

    // 코어 : 조각 버튼
    _coreSlice.uiRenderer->Init("research_core");
    _coreSlice.transform->SetPosition(WINSIZEX / 2, WINSIZEY / 2);
    _coreSlice.transform->SetScale(0.75f, 0.75f);

    // 코어 : 조각 기본 설명
    _coreBasicDescription.uiRenderer->Init("research_core_basic_description");
    _coreBasicDescription.transform->SetPosition(WINSIZEX / 2 + 103, WINSIZEY / 2 + 78);
    _coreBasicDescription.SetActive(false);

    // 코어 : 조각 기본 설명의 [i] 주변 버튼
    _coreDetailDescriptionButton.uiRenderer->Init("in_research_about");
    _coreDetailDescriptionButton.transform->SetPosition(WINSIZEX / 2 + 57, WINSIZEY / 2 + 22);
    _coreDetailDescriptionButton.SetActive(false);

    // 코어 : 조각 상세 설명 이미지
    _coreDetailDescriptionImg.uiRenderer->Init("research_core_detail_description");
    _coreDetailDescriptionImg.transform->SetPosition(WINSIZEX / 2, WINSIZEY / 2);
    _coreDetailDescriptionImg.uiRenderer->SetAlpha(1.f);
    _coreDetailDescriptionImg.uiMouseEvent->enable = false;
    _coreDetailDescriptionImg.SetActive(false);

    /* 기본 아이콘 */
    _coreSlice.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImgWithBasicDes, _uiControler,
            _coreSlice.transform, &_coreBasicDescription, &_coreDetailDescriptionButton, &_inDetail, true),
        EVENT::ENTER);

    _coreSlice.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_inActiveChoiceImgWithBasicDes, _uiControler,
            _coreSlice.transform, &_coreBasicDescription, &_lockDes, &_coreDetailDescriptionButton, false),
        EVENT::EXIT);

    /* 기본 설명 버튼 */
    _coreBasicDescription.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_inBasicDes, _uiControler,
            _coreSlice.transform, &_coreBasicDescription, &_lockDes, true),
        EVENT::ENTER);
    
    _coreBasicDescription.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_disableInBasicDes, _uiControler,
            _coreSlice.transform, &_coreBasicDescription, &_lockDes, &_coreDetailDescriptionButton, false),
        EVENT::EXIT);

    /* 기본 설명 [i] 주변 버튼 */
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
  
#pragma region 기계식 드릴

    _mechanicalDrill.uiRenderer->Init("research_drill");
    _mechanicalDrill.transform->SetPosition(WINSIZEX / 2 - 200, WINSIZEY / 2 - 50);
    _mechanicalDrill.transform->SetScale(0.75f, 0.75f);

    _mechanicalDrill.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _mechanicalDrill.transform, true), EVENT::ENTER);
    _mechanicalDrill.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _mechanicalDrill.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region 컨베이너

    _conveyor.uiRenderer->Init("research_conveyor");
    _conveyor.transform->SetPosition(WINSIZEX / 2 - 400, WINSIZEY / 2 - 50);
    _conveyor.transform->SetScale(0.75f, 0.75f);

    _conveyor.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _conveyor.transform, true), EVENT::ENTER);
    _conveyor.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _conveyor.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region 교차기

    _crossover.uiRenderer->Init("research_crossover");
    _crossover.transform->SetPosition(WINSIZEX / 2 - 400, WINSIZEY / 2 - 100);
    _crossover.transform->SetScale(0.75f, 0.75f);

    _crossover.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _crossover.transform, true), EVENT::ENTER);
    _crossover.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _crossover.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region 분배기

    _distributor.uiRenderer->Init("research_undeveloped_distributor");
    _distributor.transform->SetPosition(WINSIZEX / 2 - 400, WINSIZEY / 2 - 150);
    _distributor.transform->SetScale(0.75f, 0.75f);

    _distributor.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _distributor.transform, true), EVENT::ENTER);
    _distributor.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _distributor.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region 전초기지

    _outpost.uiRenderer->Init("research_outpost");
    _outpost.transform->SetPosition(WINSIZEX / 2 + 200, WINSIZEY / 2 + 50);
    _outpost.transform->SetScale(0.75f, 0.75f);

    _outpost.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _outpost.transform, true), EVENT::ENTER);
    _outpost.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _outpost.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region 구리

    _copper.uiRenderer->Init("research_copper");
    _copper.transform->SetPosition(WINSIZEX / 2 + 600, WINSIZEY / 2 + 50);
    _copper.transform->SetScale(0.75f, 0.75f);

    _copper.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _copper.transform, true), EVENT::ENTER);
    _copper.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _copper.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region 물

    _water.uiRenderer->Init("research_water");
    _water.transform->SetPosition(WINSIZEX / 2 + 400, WINSIZEY / 2 + 100);
    _water.transform->SetScale(0.75f, 0.75f);

    _water.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _water.transform, true), EVENT::ENTER);
    _water.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _water.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region 납

    _lead.uiRenderer->Init("research_lead");
    _lead.transform->SetPosition(WINSIZEX / 2 + 500, WINSIZEY / 2 + 100);
    _lead.transform->SetScale(0.75f, 0.75f);

    _lead.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _lead.transform, true), EVENT::ENTER);
    _lead.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _lead.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region 모래

    _sand.uiRenderer->Init("research_sand");
    _sand.transform->SetPosition(WINSIZEX / 2 + 600, WINSIZEY / 2 + 100);
    _sand.transform->SetScale(0.75f, 0.75f);

    _sand.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _sand.transform, true), EVENT::ENTER);
    _sand.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _sand.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region 듀오

    _duo.uiRenderer->Init("research_duo");
    _duo.transform->SetPosition(WINSIZEX / 2 + 600, WINSIZEY / 2 - 50);
    _duo.transform->SetScale(0.75f, 0.75f);

    _duo.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _duo.transform, true), EVENT::ENTER);
    _duo.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _duo.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region 구리 벽

    _copperWall.uiRenderer->Init("research_undeveloped_copperWall");
    _copperWall.transform->SetPosition(WINSIZEX / 2 + 450, WINSIZEY / 2 - 100);
    _copperWall.transform->SetScale(0.75f, 0.75f);

    _copperWall.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _copperWall.transform, true), EVENT::ENTER);
    _copperWall.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _copperWall.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region 스캐터

    _scatter.uiRenderer->Init("research_undeveloped_scatter");
    _scatter.transform->SetPosition(WINSIZEX / 2 + 550, WINSIZEY / 2 - 100);
    _scatter.transform->SetScale(0.75f, 0.75f);

    _scatter.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _scatter.transform, true), EVENT::ENTER);
    _scatter.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _scatter.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region 코어 : 기반

    _coreFoundation.uiRenderer->Init("research_lock");
    _coreFoundation.transform->SetPosition(WINSIZEX / 2 - 300, WINSIZEY / 2 - 50);
    _coreFoundation.transform->SetScale(0.75f, 0.75f);

    _coreFoundation.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _coreFoundation.transform, true), EVENT::ENTER);
    _coreFoundation.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _coreFoundation.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region 기계식 펌프

    _mechanicalPump.uiRenderer->Init("research_lock");
    _mechanicalPump.transform->SetPosition(WINSIZEX / 2 - 250, WINSIZEY / 2 - 100);
    _mechanicalPump.transform->SetScale(0.75f, 0.75f);

    _mechanicalPump.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _mechanicalPump.transform, true), EVENT::ENTER);
    _mechanicalPump.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _mechanicalPump.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region 흑연 압축기

    _graphiteCompressor.uiRenderer->Init("research_lock");
    _graphiteCompressor.transform->SetPosition(WINSIZEX / 2 - 175, WINSIZEY / 2 - 100);
    _graphiteCompressor.transform->SetScale(0.75f, 0.75f);

    _graphiteCompressor.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _graphiteCompressor.transform, true), EVENT::ENTER);
    _graphiteCompressor.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _graphiteCompressor.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region 화력 발전기

    _thermalGenerator.uiRenderer->Init("research_lock");
    _thermalGenerator.transform->SetPosition(WINSIZEX / 2 - 100, WINSIZEY / 2 - 100);
    _thermalGenerator.transform->SetScale(0.75f, 0.75f);

    _thermalGenerator.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _thermalGenerator.transform, true), EVENT::ENTER);
    _thermalGenerator.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _thermalGenerator.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region 지상 발전기

    _groundFactory.uiRenderer->Init("research_lock");
    _groundFactory.transform->SetPosition(WINSIZEX / 2 - 225, WINSIZEY / 2 + 50);
    _groundFactory.transform->SetScale(0.75f, 0.75f);

    _groundFactory.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _groundFactory.transform, true), EVENT::ENTER);
    _groundFactory.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _groundFactory.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region 얼어붙은 숲

    _frozenForest.uiRenderer->Init("research_lock");
    _frozenForest.transform->SetPosition(WINSIZEX / 2 + 200, WINSIZEY / 2 + 100);
    _frozenForest.transform->SetScale(0.75f, 0.75f);

    _frozenForest.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _frozenForest.transform, true), EVENT::ENTER);
    _frozenForest.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _frozenForest.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region 티타늄

    _titan.uiRenderer->Init("research_lock");
    _titan.transform->SetPosition(WINSIZEX / 2 + 475, WINSIZEY / 2 + 150);
    _titan.transform->SetScale(0.75f, 0.75f);

    _titan.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _titan.transform, true), EVENT::ENTER);
    _titan.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _titan.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region 강화 유리

    _metaglass.uiRenderer->Init("research_lock");
    _metaglass.transform->SetPosition(WINSIZEX / 2 + 525, WINSIZEY / 2 + 150);
    _metaglass.transform->SetScale(0.75f, 0.75f);

    _metaglass.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _metaglass.transform, true), EVENT::ENTER);
    _metaglass.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _metaglass.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region 고철

    //_scrapMetal.uiRenderer->Init("research_developed_scrapMetal");
    _scrapMetal.uiRenderer->Init("research_lock");

    _scrapMetal.transform->SetPosition(WINSIZEX / 2 + 575, WINSIZEY / 2 + 150);
    _scrapMetal.transform->SetScale(0.75f, 0.75f);

    _scrapMetal.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _scrapMetal.transform, true), EVENT::ENTER);
    _scrapMetal.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _scrapMetal.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region 광재

    _mineral.uiRenderer->Init("research_lock");
    _mineral.transform->SetPosition(WINSIZEX / 2 + 575, WINSIZEY / 2 + 200);
    _mineral.transform->SetScale(0.75f, 0.75f);

    _mineral.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _mineral.transform, true), EVENT::ENTER);
    _mineral.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _mineral.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region 석탄

    _coal.uiRenderer->Init("research_lock");
    _coal.transform->SetPosition(WINSIZEX / 2 + 625, WINSIZEY / 2 + 150);
    _coal.transform->SetScale(0.75f, 0.75f);

    _coal.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _coal.transform, true), EVENT::ENTER);
    _coal.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _coal.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region 대형 구리 벽

    _largeCopperWall.uiRenderer->Init("research_undeveloped_largeCopperWall");
    _largeCopperWall.transform->SetPosition(WINSIZEX / 2 + 450, WINSIZEY / 2 - 150);
    _largeCopperWall.transform->SetScale(0.75f, 0.75f);

    _largeCopperWall.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _largeCopperWall.transform, true), EVENT::ENTER);
    _largeCopperWall.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _largeCopperWall.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region 타이탄 벽

    _titanWall.uiRenderer->Init("research_lock");
    _titanWall.transform->SetPosition(WINSIZEX / 2 + 450, WINSIZEY / 2 - 200);
    _titanWall.transform->SetScale(0.75f, 0.75f);

    _titanWall.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _titanWall.transform, true), EVENT::ENTER);
    _titanWall.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _titanWall.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region 헤일

    _hail.uiRenderer->Init("research_lock");
    _hail.transform->SetPosition(WINSIZEX / 2 + 550, WINSIZEY / 2 - 150);
    _hail.transform->SetScale(0.75f, 0.75f);

    _hail.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _hail.transform, true), EVENT::ENTER);
    _hail.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _hail.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region 스코치

    _scorch.uiRenderer->Init("research_lock");
    _scorch.transform->SetPosition(WINSIZEX / 2 + 650, WINSIZEY / 2 - 100);
    _scorch.transform->SetScale(0.75f, 0.75f);

    _scorch.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _scorch.transform, true), EVENT::ENTER);
    _scorch.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _scorch.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region 지역 자원 수송기

    _launchPad.uiRenderer->Init("research_lock");
    _launchPad.transform->SetPosition(WINSIZEX / 2 - 550, WINSIZEY / 2 - 200);
    _launchPad.transform->SetScale(0.75f, 0.75f);

    _launchPad.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _launchPad.transform, true), EVENT::ENTER);
    _launchPad.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _launchPad.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region 대형 분배기

    _router.uiRenderer->Init("research_undeveloped_router");
    _router.transform->SetPosition(WINSIZEX / 2 - 475, WINSIZEY / 2 - 200);
    _router.transform->SetScale(0.75f, 0.75f);

    _router.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _router.transform, true), EVENT::ENTER);
    _router.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _router.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region 필터

    _sorter.uiRenderer->Init("research_undeveloped_sorter");
    _sorter.transform->SetPosition(WINSIZEX / 2 - 400, WINSIZEY / 2 - 200);
    _sorter.transform->SetScale(0.75f, 0.75f);

    _sorter.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _sorter.transform, true), EVENT::ENTER);
    _sorter.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _sorter.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region 컨테이너

    _container.uiRenderer->Init("research_lock");
    _container.transform->SetPosition(WINSIZEX / 2 - 325, WINSIZEY / 2 - 200);
    _container.transform->SetScale(0.75f, 0.75f);

    _container.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _container.transform, true), EVENT::ENTER);
    _container.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _container.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region 다리 컨테이너

    _bridgeConveyor.uiRenderer->Init("research_undeveloped_bridgeConveyor");
    _bridgeConveyor.transform->SetPosition(WINSIZEX / 2 - 250, WINSIZEY / 2 - 200);
    _bridgeConveyor.transform->SetScale(0.75f, 0.75f);

    _bridgeConveyor.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _bridgeConveyor.transform, true), EVENT::ENTER);
    _bridgeConveyor.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _bridgeConveyor.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region 반전 필터

    _invertedSorter.uiRenderer->Init("research_undeveloped_invertedSorter");
    _invertedSorter.transform->SetPosition(WINSIZEX / 2 - 425, WINSIZEY / 2 - 250);
    _invertedSorter.transform->SetScale(0.75f, 0.75f);

    _invertedSorter.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _invertedSorter.transform, true), EVENT::ENTER);
    _invertedSorter.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _invertedSorter.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region 포화 필터

    _overflowGate.uiRenderer->Init("research_undeveloped_overflowGate");
    _overflowGate.transform->SetPosition(WINSIZEX / 2 - 375, WINSIZEY / 2 - 250);
    _overflowGate.transform->SetScale(0.75f, 0.75f);

    _overflowGate.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _overflowGate.transform, true), EVENT::ENTER);
    _overflowGate.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _overflowGate.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region 티타늄 컨베이어

    _titaniumConveyor.uiRenderer->Init("research_lock");
    _titaniumConveyor.transform->SetPosition(WINSIZEX / 2 - 250, WINSIZEY / 2 - 250);
    _titaniumConveyor.transform->SetScale(0.75f, 0.75f);

    _titaniumConveyor.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _titaniumConveyor.transform, true), EVENT::ENTER);
    _titaniumConveyor.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inResearch_ActiveChoiceImg, _uiControler, _titaniumConveyor.transform, false), EVENT::EXIT);

#pragma endregion

#pragma region 불포화 필터

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
#pragma region 메뉴 화면

    _menuImg.uiRenderer->Init("menu_menuimg");
    _menuImg.uiRenderer->SetAlpha(0.95f);
    _menuImg.uiMouseEvent->enable = false;
    _menuImg.transform->SetPosition(WINSIZEX / 2, WINSIZEY / 2);
    _menuImg.SetActive(false);

#pragma endregion

#pragma region 메뉴 [돌아가기] 이미지 & 버튼
    
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

#pragma region 메뉴 [설정] 이미지 & 버튼

#pragma endregion

#pragma region 메뉴 [저장 후 나가기] 이미지 & 버튼

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

#pragma region 정말로 종료하시겠습니까? 화면

    _menu_ReallyEnd_Img.uiRenderer->Init("menu_reallyendimg");
    _menu_ReallyEnd_Img.uiRenderer->SetAlpha(0.95f);
    _menu_ReallyEnd_Img.uiMouseEvent->enable = false;
    _menu_ReallyEnd_Img.transform->SetPosition(WINSIZEX / 2, WINSIZEY / 2);
    _menu_ReallyEnd_Img.SetActive(false);

#pragma endregion

#pragma region 정말로 종료하시겠습니까? [취소] 이미지 & 버튼

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

#pragma region 정말로 종료하시겠습니까? [확인] 이미지 & 버튼

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
    // 메뉴
    _menu_GoBackIdleImg.Update();
    _menu_GoBackChoiceImg.Update();
    _menu_GoBackButton.Update();

    _menu_SettingIdleImg.Update();
    _menu_SettingChoiceImg.Update();
    _menu_SettingButton.Update();

    _menu_SaveAndExitIdleImg.Update();
    _menu_SaveAndExitChoiceImg.Update();
    _menu_SaveAndExitButton.Update();

    // 정말로 종료하시겠습니까?
    _menu_ReallyEnd_Check_Idle.Update();
    _menu_ReallyEnd_Check_Choice.Update();
    _menu_ReallyEnd_Check_Button.Update();

    _menu_ReallyEnd_Cancle_Idle.Update();
    _menu_ReallyEnd_Cancle_Choice.Update();
    _menu_ReallyEnd_Cancle_Button.Update();
}

void GameScene::menuRender()
{
    // 메뉴
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

    // 정말로 종료하시겠습니까?
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

	D2DRENDERER->RenderText(150, 5, L"단계", 22, L"fontello", D2DRenderer::DefaultBrush::Yellow);
	D2DRENDERER->RenderText(202, 7, wave, 22, L"mindustry", D2DRenderer::DefaultBrush::Yellow);
	D2DRENDERER->RenderText(220, 7, L"/10", 22, L"mindustry", D2DRenderer::DefaultBrush::Yellow);
	D2DRENDERER->RenderText(150, 30, L"다음 단계까지", 20, L"fontello", D2DRenderer::DefaultBrush::Yellow);

	D2DRENDERER->RenderText(155, 58, minute, 20, L"mindustry", D2DRenderer::DefaultBrush::White);
	D2DRENDERER->RenderText(173, 55, L"분", 20, L"fontello", D2DRenderer::DefaultBrush::White);
	D2DRENDERER->RenderText(198, 58, second, 20, L"mindustry", D2DRenderer::DefaultBrush::White);
	D2DRENDERER->RenderText(230, 55, L"초", 20, L"fontello", D2DRenderer::DefaultBrush::White);
}

void GameScene::InGameUIClip()
{
	/////////////////// 07. 20 게임속 Wave UI && Player UI 민재 ////////////////////////////
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
	//D2DRENDERER->RenderText(100, 100, wstr, 20, L"맑은고딕", D2DRenderer::DefaultBrush::White);

	//wstring wstrangle = L"Angle : ";
	//wstrangle.append(to_wstring(_player->controler->GetTargetAngle()));
	//D2DRENDERER->RenderText(100, 150, wstrangle, 20, L"맑은고딕", D2DRenderer::DefaultBrush::White);

	//wstring time = L"MusicTime: ";
	//time.append(to_wstring(_musicTime));
	//D2DRENDERER->RenderText(10, 140, time, 30, L"fontello", D2DRenderer::DefaultBrush::Blue);

	/* 에너미 관련 작업 민재, 삭제 금지*/
	/*wstring hp = L"HP : ";
	hp.append(to_wstring(_player->GetComponent<PlayerControler>()->GetHp()));
	D2DRENDERER->RenderText(10, 150, hp, 30, L"fontello", D2DRenderer::DefaultBrush::Blue);

    /*wstring mineCount = L"mineCount";
    mineCount.append(to_wstring(_mineCount));
    D2DRENDERER->RenderText(WINSIZEX / 2 - 50, 10, mineCount, 20, L"fontello", D2DRenderer::DefaultBrush::White);*/
}
