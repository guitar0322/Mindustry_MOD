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
HRESULT GameScene::Init()
{
    Scene::Init();

	InitClip();
	PlayerClip();

	SetBackBufferSize(1600, 1600);
    COLLIDERMANAGER->PartitionArea(10, 10);
    StaticBuffer->BeginDraw();
	MainCam->SetScreenSize(WINSIZEX, WINSIZEY);
	MainCam->SetRenderSize(1600, 1010);
    MainCam->transform->SetPosition(1600 / 2, 1600 / 2);

    selectCategoryIdx = 0;
    _gameInfo = new GameInfo();
    _gameInfo->Init();

    _propContainer = new PropContainer();
    _propFactory = new PropFactory();
    _propFactory->Init();
	//_propFactory->tag = TAGMANAGER->GetTag("player");
    _propFactory->propContainer = _propContainer;
    _propFactory->LinkGameInfo(_gameInfo);

    _resourceManager = new ResourceManager();
    _resourceManager->propContainer = _propContainer;
    _resourceManager->Init();

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

	/*===================================*/
	/*인게임 맵 초기화 -> 유림*/
	_gameMap = new GameMap;
	_gameMap->Init();
    _uiControler->gameMap = _gameMap;

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
        /* 연구부분 */
        _lockDes = false;
        _research = false;
        _inDetail = false;

        /* 메뉴부분 */
        _menu = false;
        _menu_ReallyEnd = false;
    }

    // _uiControler 이미지 연동
    {
        /* 연구부분 */
        _uiControler->choiceImg = &_choiceImg;
        _uiControler->lockImg = &_lockImg;
        _uiControler->inResearchChoiceImg = &_inResearchChoiceImg;
        _uiControler->research_goBackIdleImg = &_research_goBackIdleImg;
        _uiControler->research_goBackChoiceImg = &_research_goBackChoiceImg;
        _uiControler->coreDBIdleImg = &_coreDBIdleImg;
        _uiControler->coreDBChoiceImg = &_coreDBChoiceImg;
        _uiControler->detailDes_GoBackIdleImg = &_detailDes_goBackIdleImg;
        _uiControler->detailDes_GoBackChoiceImg = &_detailDes_goBackChoiceImg;

        /* 메뉴부분 */
        _uiControler->menu_GoBackIdleImg = &_menu_GoBackIdleImg;
        _uiControler->menu_GoBackChoiceImg = &_menu_GoBackChoiceImg;
        _uiControler->menu_SettingIdleImg = &_menu_SettingIdleImg;
        _uiControler->menu_SettingChoiceImg = &_menu_SettingChoiceImg;
        _uiControler->menu_SaveAndExitIdleImg = &_menu_SaveAndExitIdleImg;
        _uiControler->menu_SaveAndExitChoiceImg = &_menu_SaveAndExitChoiceImg;
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
	/*===================================================================== */

    /* 게임신 에너미 관련 작업 함수, by 민재. 삭제 금지 */
	SetProjectileManager();
	SetCore();
	SetEnemyManager();
	SetCameraControler();
	SetGameUI();

    /* 사운드 작업 광철 210718 */
	SOUNDMANAGER->addSound("start", "music/land.mp3", true, false);
	SOUNDMANAGER->addSound("bgm1", "music/game1.mp3", true, false);
	SOUNDMANAGER->addSound("bgm2", "music/game2.mp3", true, false);
	SOUNDMANAGER->addSound("bgm3", "music/game9.mp3", true, false);
	SOUNDMANAGER->play("start", 10.0f);
	_musicTime = 0;
   StaticBuffer->EndDraw();

    return S_OK;
}

void GameScene::Update()
{
	MainCam->Update();

    //07-19 플레이어와 UI간의 마우스 클릭 우선순위때문에 UI업데이트 위로 올림
    //카테고리 아이콘 업데이트
    {
        _defenseIcon.Update();
        _railIcon.Update();
        _turretIcon.Update();
        _productionIcon.Update();
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

	/* 플레이어 부분*/
	_player->Update();
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
	//_enemyManager->Update();

	//07.20 민재 인 게임 Wave UI && Player UI 작업//
	InGameUIUpdate();
	_enemyManager->Update();
    
    /* 시영 */
    // 연구 부분 Update
    {
        if (KEYMANAGER->isOnceKeyDown(VK_F1)) _research = true;
        if (KEYMANAGER->isOnceKeyDown(VK_F2)) _research = false;
        if (_research) researchUpdate();
        _research_goBackButton.Update();
        _coreDBButton.Update();
        _detailDes_goBackButton.Update();
    }

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
            }
        }
 
        if (_menu) menuUpdate();
    }

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
		_player->transform->GetChild(3)->gameObject->Render();
		_player->Render();
		_enemyManager->Render();
		_projectileManager->Render();
		_core->Render();
		_cameraControler->Render();
		MainCam->Render();
	}

    //카테고리 아이콘 렌더
    {
        _buildingCategoryFrame.Render();
        _defenseIcon.Render();
        _railIcon.Render();
        _turretIcon.Render();
        _productionIcon.Render();
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

    /* 시영 */
    // 연구
    if (_research) researchRender();
    // 메뉴
    if (_menu) menuRender();

	//07.20 민재 인 게임 Wave UI && Player UI 작업//
	InGameUIRender();

	/* ================================여기 만지지 마세요 ========================================*/
	//자원UI 렌더 -> 유림 (210719)
	ResourcesRender();
	/* ================================여기 만지지 마세요 ========================================*/
	
    //210719 유림 수정
	StringRender();
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
		CLIPMANAGER->AddClip("duo_top","duo/duo.png",32,32);
		CLIPMANAGER->AddClip("duo_body","duo/block-1.png",32,32);
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

        CLIPMANAGER->AddClip("menu_reallyend_check_idle", "sprites/game/menu_reallyend_check_idle.png", 200, 54);
        CLIPMANAGER->AddClip("menu_reallyend_check_choice", "sprites/game/menu_reallyend_check_choice.png", 200, 54);

        CLIPMANAGER->AddClip("menu_reallyend_cancel_idle", "sprites/game/menu_reallyend_cancel_idle.png", 200, 54);
        CLIPMANAGER->AddClip("menu_reallyend_cancel_choice", "sprites/game/menu_reallyend_cancel_choice.png", 200, 54);
    }

	//// ENEMY & CORE 클립 작업 민재 /////
	{
		CLIPMANAGER->AddClip("core", "sprites/blocks/storage/core.png", 96, 96);
		CLIPMANAGER->AddClip("enemy_atrax", "sprites/units/enemy/enemy_atrax.png", 188, 329);
		CLIPMANAGER->AddClip("enemy_dagger_walk", "sprites/units/enemy/enemy_dagger_walk.png", 369, 114, 3, 1, 0.8f);
		CLIPMANAGER->AddClip("projectile", "sprites/units/enemy/projectile.png", 52, 52);
	}

	/////////////////// 07. 20 게임속 Wave UI && Player UI 민재 ////////////////////////////
	{
		CLIPMANAGER->AddClip("uiwavepane","sprites/ingameui/uiwavepane.png", 367, 100);
		CLIPMANAGER->AddClip("playerui", "sprites/ingameui/playerui.png", 70, 70);
		CLIPMANAGER->AddClip("playerhpui", "sprites/ingameui/playerhpui.png", 133, 92);
		CLIPMANAGER->AddClip("waveskipui", "sprites/ingameui/waveskipui.png", 57, 100);
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


	//자원 클립
	CLIPMANAGER->AddClip("copperUI", "sprites/items/item-copper.png", 32, 32);
	CLIPMANAGER->AddClip("leadUI", "sprites/items/item-lead.png", 32, 32);
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

	_player->transform->AddChild(_playerWeaponL->transform);
	_player->transform->AddChild(_playerWeaponR->transform);
	_player->transform->AddChild(_playerCell->transform);
	_player->transform->AddChild(_playerFireCircle->transform);
	_player->transform->AddChild(_playerFire->transform);
	_player->transform->GetChild(2)->SetPosition(_player->transform->GetX() , _player->transform->GetY());

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
	D2DRenderer::GetInstance()->FillRectangle(_resoucesUIBackGround, D2D1::ColorF::Black, 0.7f);
	_resourcesUI[0].Render();
	_resourcesUI[1].Render();

	wstring copperAmount;
	wstring leadAmount;

	if (_gameInfo->GetResourceAmount(COPPER) < 1000)
	{
		copperAmount = to_wstring(_gameInfo->GetResourceAmount(COPPER));
	}
	else
	{
		copperAmount = L"1.0k";
	}

	if (_gameInfo->GetResourceAmount(LEAD) < 1000)
	{
		leadAmount = to_wstring(_gameInfo->GetResourceAmount(LEAD));
	}
	else
	{
		leadAmount = L"1.0k";
	}
	
	D2DRENDERER->RenderText(WINSIZEX / 2 - 70, 5, copperAmount, 28, L"mindustry", D2DRenderer::DefaultBrush::White);
	D2DRENDERER->RenderText(WINSIZEX / 2 + 42, 5, leadAmount, 28, L"mindustry", D2DRenderer::DefaultBrush::White);
}

void GameScene::researchUpdate()
{
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
    /* 버튼 Render */
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
    _mineral.Render();
    _coal.Render();
    _largeCopperWall.Render();
    _titanWall.Render();
    _hail.Render();
    _scorch.Render();
    _launchPad.Render();
    _router.Render();
    _sorter.Render();
    _container.Render();
    _bridgeConveyor.Render();
    _invertedSorter.Render();
    _overflowGate.Render();
    _titaniumConveyor.Render();
    _underflowGate.Render();

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

    //
    _detailDes_goBackIdleImg.Render();
    _detailDes_goBackChoiceImg.Render();
    _detailDes_goBackButton.Render();
}

void GameScene::researchInitUI()
{
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

    _scrapMetal.uiRenderer->Init("research_developed_scrapMetal");
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

#pragma region 메뉴 [돌아가기]
    
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

#pragma region 메뉴 [저장 후 나가기]

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
    _menu_SaveAndExitButton.transform->SetPosition(WINSIZEX / 2, WINSIZEY / 2 + 100);

    /* _menu_SaveAndExitButton ENTERT, CLICK, EXIT 하기 */

    _menu_SaveAndExitButton.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inMenu_AcitveChoiceImg_SaveAndExit, _uiControler,
            true),
        EVENT::ENTER);

    // CLICK

    _menu_SaveAndExitButton.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::inMenu_AcitveChoiceImg_SaveAndExit, _uiControler,
            false),
        EVENT::EXIT);

    //_menu_GoBackButton.uiMouseEvent->RegistCallback(l
    //    std::bind(&UIControler::inMenu_ReturnToGameScene, _uiControler,
    //        &_menu, false),
    //    EVENT::CLICK);


#pragma endregion

#pragma region 정말로 종료하시겠습니까? 화면

    _menu_ReallyEnd_Img.uiRenderer->Init("menu_reallyendimg");
    _menu_ReallyEnd_Img.uiRenderer->SetAlpha(0.95f);
    _menu_ReallyEnd_Img.uiMouseEvent->enable = false;
    _menu_ReallyEnd_Img.transform->SetPosition(WINSIZEX / 2, WINSIZEY / 2);
    _menu_ReallyEnd_Img.SetActive(false);

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

    _menu_ReallyEnd_Cancle_Idle.Update();
    _menu_ReallyEnd_Cancle_Choice.Update();
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

    _menu_ReallyEnd_Cancle_Idle.Render();
    _menu_ReallyEnd_Cancle_Choice.Render();
}

void GameScene::SetProjectileManager()
{
	_projectileManager = new GameObject();
	_projectileManager->AddComponent(new ProjectileManager());
	_projectileManager->GetComponent<ProjectileManager>()->Init();
	_projectileManager->GetComponent<ProjectileManager>()->SetPlayer(_player);
	_player->controler->SetProjectileManager(_projectileManager->GetComponent<ProjectileManager>());
}

void GameScene::SetCore()
{
	_core = new Prop();
	_core->Init();
	_core->tag = TAGMANAGER->GetTag("prop");
	_core->renderer->Init("core");
	_core->transform->SetPosition(25 * TILESIZE + 16, 36 * TILESIZE + 16);
	_core->collider->transform->SetPosition(_core->transform->GetX(), _core->transform->GetY());
	_core->collider->RefreshPartition();
}

void GameScene::SetEnemyManager()
{
	_enemyManager = new GameObject();
	_enemyManager->AddComponent(new EnemyManager());
	_enemyManager->GetComponent<EnemyManager>()->SetTestCoreTransform(_core);
	_enemyManager->GetComponent<EnemyManager>()->SetProjectileManager(_projectileManager->GetComponent<ProjectileManager>());
	_enemyManager->GetComponent<EnemyManager>()->Init();
	_projectileManager->GetComponent<ProjectileManager>()->SetEnemyManager(_enemyManager->GetComponent<EnemyManager>());
}

void GameScene::SetCameraControler()
{
    _cameraControler = new GameObject();
    _cameraControler->AddComponent(new CameraControler());
    _cameraControler->GetComponent<CameraControler>()->Init();
    _cameraControler->GetComponent<CameraControler>()->SetPlayerTr(_player->transform);
}

void GameScene::SetGameUI()
{
	_wavePane.Init();
	_wavePane.uiRenderer->Init("uiwavepane");
	_wavePane.transform->SetPosition(183, 45);

	_playerUi.Init();
	_playerUi.uiRenderer->Init("playerui");
	_playerUi.transform->SetPosition(65, 45);

	_playerHpUi.Init();
	_playerHpUi.uiRenderer->Init("playerhpui");
	_playerHpUi.transform->SetPosition(65, 50);

	_waveSkipUi.Init();
	_waveSkipUi.uiRenderer->Init("waveskipui");
	_waveSkipUi.transform->SetPosition(380, 45);
}

void GameScene::InGameUIUpdate()
{
	_wavePane.Update();
	_playerUi.Update();
	_playerHpUi.Update();
	_waveSkipUi.Update();
}

void GameScene::InGameUIRender()
{
	_wavePane.Render();
	_playerUi.Render();
	_playerHpUi.Render();
	_waveSkipUi.Render();
	D2DRENDERER->RenderText(150, 5, L"wave", 25, L"fontello", D2DRenderer::DefaultBrush::Yellow);
	D2DRENDERER->RenderText(150, 35, L"다음 단계까지", 20, L"fontello", D2DRenderer::DefaultBrush::Yellow);
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

	wstring minute = L"MINUTE : ";
	minute.append(to_wstring(_enemyManager->GetComponent<EnemyManager>()->GetTimeMinute()));
	D2DRENDERER->RenderText(10, 10, minute, 30, L"fontello", D2DRenderer::DefaultBrush::Blue);

	wstring second = L"SECOND: ";
	second.append(to_wstring(_enemyManager->GetComponent<EnemyManager>()->GetTimeSecond()));
	D2DRENDERER->RenderText(10, 60, second, 30, L"fontello", D2DRenderer::DefaultBrush::Blue);

	wstring wave = L"CurWave: ";
	wave.append(to_wstring(_enemyManager->GetComponent<EnemyManager>()->GetCurWave()));
	D2DRENDERER->RenderText(10, 110, wave, 30, L"fontello", D2DRenderer::DefaultBrush::Blue);

    /*wstring mineCount = L"mineCount";
    mineCount.append(to_wstring(_mineCount));
    D2DRENDERER->RenderText(WINSIZEX / 2 - 50, 10, mineCount, 20, L"fontello", D2DRenderer::DefaultBrush::White);*/
}
