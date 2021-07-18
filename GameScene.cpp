#include "stdafx.h"
#include "GameScene.h"
#include "UIControler.h"
#include "PropContainer.h"
#include "PlayerControler.h"
#include "PropFactory.h"
#include "UIMouseEvent.h"
#include "GameInfo.h"

HRESULT GameScene::Init()
{
    Scene::Init();

	InitClip();
	SetBackBufferSize(1600, 1600);
    StaticBuffer->BeginDraw();
	MainCam->SetRenderSize(1600, 1010);
    MainCam->transform->SetPosition(800, 505);

    selectCategoryIdx = 0;
    propContainer = new PropContainer();
    propFactory = new PropFactory();
    propFactory->Init();
    propFactory->propContainer = propContainer;

    uiControler = new UIControler();
    uiControler->Init();
    uiControler->categorySelect = &categorySelect;
    uiControler->propSelect = &propSelect;
    uiControler->propPreview = &propPreview;
               
    uiControler->turretIconV = &turretIconV;
    uiControler->drillIconV = &drillIconV;
    uiControler->railIconV = &railIconV;
    uiControler->wallIconV = &wallIconV;
    uiControler->preIconV = &turretIconV;

    uiControler->propFactory = propFactory;

    gameInfo = new GameInfo();
    gameInfo->Init();
    gameInfo->AddResource(COPPER, 500);

    propFactory->LinkGameInfo(gameInfo);

	gameMap = new GameMap;
	gameMap->Init();

    InitClip();
    InitCategoryUI();
    InitPropUI();

    /* SHUNG 210715 */
    uiControler->choiceImg = &_choiceImg;

	/* 플레이어 부분*/
	_player = new Player();
	_player->Init();
	_player->renderer->Init("player");
	_player->transform->SetPosition(1500, 900);
	_player->transform->SetAngle(0.0f);
	MainCam->transform->SetPosition(_player->transform->position.x, _player->transform->position.y);

	_projectileManager = new GameObject();
	_projectileManager->AddComponent(new ProjectileManager());
	_projectileManager->GetComponent<ProjectileManager>()->Init();

	_player->controler->SetProjectileManager(_projectileManager->GetComponent<ProjectileManager>());
    StaticBuffer->EndDraw();
	//========================================

    return S_OK;
}

void GameScene::Update()
{
    buildingCategoryFrame.Update();
    propFactory->Update();
    propContainer->Update();
    uiControler->Update();
    propPreview.Update();
	gameMap->Update();

	/* 플레이어 부분*/
	_player->Update();
	MainCam->transform->SetPosition(_player->transform->position.x, _player->transform->position.y);
	MainCam->Update();
	_projectileManager->Update();
	//========================================

    //카테고리 아이콘 업데이트
    {
		defenseIcon.Update();
        railIcon.Update();
		turretIcon.Update();
		productionIcon.Update();
    }
    //설치물 아이콘 업데이트
    {
        copperWallIcon.Update();
        mechanicDrillIcon.Update();
        duoIcon.Update();
        conveyorIcon.Update();
    }
    categorySelect.Update();
    propSelect.Update();

    /* SHUNG 210715 */
    _CoreSlice.Update();
    _choiceImg.Update();
}

void GameScene::Render()
{
    MainCam->StaticToBackBuffer();
	gameMap->Render();
    propFactory->Render();
    propContainer->Render();
    propPreview.Render();
    uiControler->Render();
	_player->Render();
	_projectileManager->Render();
	MainCam->Render();

    //카테고리 아이콘 렌더
    {
        buildingCategoryFrame.Render();
        defenseIcon.Render();
        railIcon.Render();
        turretIcon.Render();
        productionIcon.Render();
    }
    //설치물 아이콘 렌더
    {
        copperWallIcon.Render();
        mechanicDrillIcon.Render();
        duoIcon.Render();
        conveyorIcon.Render();
    }
    categorySelect.Render();
    propSelect.Render();

    /* SHUNG 210715 */
    _CoreSlice.Render();
    _choiceImg.Render();

	wstring wstr = L"player speed : ";
	wstr.append(to_wstring(_player->controler->GetSpeed()));
	D2DRENDERER->RenderText(100, 100, wstr, 20, L"맑은고딕", D2DRenderer::DefaultBrush::White);

	wstring wstrangle = L"Angle : ";
	wstrangle.append(to_wstring(_player->controler->GetTargetAngle()));
	D2DRENDERER->RenderText(100, 150, wstrangle, 20, L"맑은고딕", D2DRenderer::DefaultBrush::White);
	
	/*wstring mineCount = L"";
	mineCount.append(to_wstring(_mineCount));
	D2DRENDERER->RenderText(WINSIZEX / 2 - 50, 10, mineCount, 20, L"fontello", D2DRenderer::DefaultBrush::White);*/
}

void GameScene::Release()
{
	NEW_SAFE_RELEASE(_player);
    NEW_SAFE_RELEASE(propContainer);
    SAFE_DELETE(propContainer);
    NEW_SAFE_RELEASE(uiControler);
    SAFE_DELETE(uiControler);
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

	//플레이어 클립
	CLIPMANAGER->AddClip("player", "player/alpha.png", 48, 48);
	CLIPMANAGER->AddClip("enemy_projectile", "sprites/units/weapons/missiles-mount.png", 48, 48);

    CLIPMANAGER->AddClip("button_select", "sprites/ui/button-select.10.png", 52, 52);

    /* SHUNG 210715 */
    CLIPMANAGER->AddClip("research_core", "sprites/game/core.png", 74, 56);
    CLIPMANAGER->AddClip("research_choice", "sprites/game/choice.png", 75, 56);
}

void GameScene::InitCategoryUI()
{
    buildingCategoryFrame.uiRenderer->Init("ui_frame");
    buildingCategoryFrame.uiRenderer->SetAlpha(0.7f);
    buildingCategoryFrame.transform->SetPosition(WINSIZEX - 132, WINSIZEY - 111);
    buildingCategoryFrame.transform->SetScale(0.7f, 0.7f);
    buildingCategoryFrame.uiMouseEvent->enable = false;

    turretIcon.uiRenderer->Init("turret_icon");
    turretIcon.transform->SetPosition(CATEGORY_UI_STARTX, CATEGORY_UI_STARTY);
	/**********************************************************
    * 버튼 콜백함수 등록방법
    * RegistCallback 매개변수(std::bind(&클래스명::함수명, 클래스의 인스턴스, 매개변수....), 등록이벤트 종류);
    * 등록이벤트 종류
    * 1.ENTER : 마우스가 진입했을때
    * 2.EXIT : 마우스가 빠져나갔을때
    * 3.CLICK : 마우스로 클릭했을때
    ************************************************************/
    turretIcon.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::ClickCategoryIcon, uiControler, &turretIcon, 0), EVENT::CLICK);

    productionIcon.uiRenderer->Init("production_icon");
    productionIcon.transform->SetPosition(turretIcon.transform->GetX() + 40, turretIcon.transform->GetY());
    productionIcon.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::ClickCategoryIcon, uiControler, &productionIcon, 1), EVENT::CLICK);

    railIcon.uiRenderer->Init("rail_icon");
    railIcon.transform->SetPosition(turretIcon.transform->GetX(), turretIcon.transform->GetY() + 40);
    railIcon.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::ClickCategoryIcon, uiControler, &railIcon, 2), EVENT::CLICK);

    defenseIcon.uiRenderer->Init("defense_icon");
    defenseIcon.transform->SetPosition(turretIcon.transform->GetX() + 40, turretIcon.transform->GetY() + 40);
    defenseIcon.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::ClickCategoryIcon, uiControler, &defenseIcon, 3), EVENT::CLICK);

    categorySelect.uiRenderer->Init("button_select");
    categorySelect.transform->SetPosition(turretIcon.transform->GetX(), turretIcon.transform->GetY());

    /* SHUNG 210715 */
    _choiceImg.uiRenderer->Init("research_choice");
    _choiceImg.transform->SetPosition(WINSIZEX / 2, WINSIZEY / 2);
    _choiceImg.transform->SetScale(0.75f, 0.75f);
    _choiceImg.SetActive(false);

    _CoreSlice.uiRenderer->Init("research_core");
    _CoreSlice.transform->SetPosition(WINSIZEX / 2, WINSIZEY / 2);
    _CoreSlice.transform->SetScale(0.75f, 0.75f);

    _CoreSlice.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::ActiveChoiceImg, uiControler, _CoreSlice.transform, true), EVENT::ENTER);
    _CoreSlice.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::ActiveChoiceImg, uiControler, _CoreSlice.transform, false), EVENT::EXIT);
}

void GameScene::InitPropUI()
{
    //터렛 아이콘 초기화
    {
        duoIcon.uiRenderer->Init("duo");
        duoIcon.transform->SetPosition(PROP_UI_STARTX, PROP_UI_STARTY);
        duoIcon.uiMouseEvent->RegistCallback(
            std::bind(&UIControler::ClickPropIcon, uiControler, &duoIcon, 0), EVENT::CLICK);
        turretIconV.push_back(&duoIcon);

    }

    //드릴 아이콘 초기화
    {
		mechanicDrillIcon.uiRenderer->Init("mechanical_drill");
		mechanicDrillIcon.transform->SetPosition(PROP_UI_STARTX, PROP_UI_STARTY);
		mechanicDrillIcon.transform->SetScale(0.5f, 0.5f);
        mechanicDrillIcon.uiMouseEvent->RegistCallback(
            std::bind(&UIControler::ClickPropIcon, uiControler, &mechanicDrillIcon, 0), EVENT::CLICK);
		drillIconV.push_back(&mechanicDrillIcon);

        for (int i = 0; i < drillIconV.size(); i++)
        {
            drillIconV[i]->SetActive(false);
        }
    }

    //레일 아이콘 초기화
    {
        conveyorIcon.uiRenderer->Init("conveyor");
        conveyorIcon.transform->SetPosition(PROP_UI_STARTX, PROP_UI_STARTY);
        conveyorIcon.uiMouseEvent->RegistCallback(
            std::bind(&UIControler::ClickPropIcon, uiControler, &conveyorIcon, 0), EVENT::CLICK);
        railIconV.push_back(&conveyorIcon);

        for (int i = 0; i < railIconV.size(); i++)
        {
            railIconV[i]->SetActive(false);
        }
    }

    //벽 아이콘 초기화
    {
        copperWallIcon.uiRenderer->Init("copper_wall");
        copperWallIcon.transform->SetPosition(PROP_UI_STARTX, PROP_UI_STARTY);
        copperWallIcon.uiMouseEvent->RegistCallback(
            std::bind(&UIControler::ClickPropIcon, uiControler, &copperWallIcon, 0), EVENT::CLICK);
        wallIconV.push_back(&copperWallIcon);

        for (int i = 0; i < wallIconV.size(); i++)
        {
            wallIconV[i]->SetActive(false);
        }
    }

    propSelect.uiRenderer->Init("button_select");
    propSelect.transform->SetPosition(PROP_UI_STARTX, PROP_UI_STARTY);
    propSelect.SetActive(false);

    propPreview.Init();
    propPreview.renderer->Init(32, 32);
    propPreview.renderer->SetAlpha(0.5f);
    propPreview.SetActive(false);

    /* SHUNG 210715 */
}
