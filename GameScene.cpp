#include "stdafx.h"
#include "GameScene.h"
#include "UIControler.h"
#include "UIMouseEvent.h"
HRESULT GameScene::Init()
{
    Scene::Init();
    selectCategoryIdx = 0;
    uiControler.AddComponent(new UIControler());
    uiControler.GetComponent<UIControler>()->Init();
    uiControler.GetComponent<UIControler>()->categorySelect = &categorySelect;
    uiControler.GetComponent<UIControler>()->railIconV = &railIconV;
    uiControler.GetComponent<UIControler>()->drillIconV = &drillIconV;
    uiControler.GetComponent<UIControler>()->turretIconV = &turretIconV;
    uiControler.GetComponent<UIControler>()->wallIconV = &wallIconV;
    uiControler.GetComponent<UIControler>()->preIconV = &turretIconV;
    InitClip();
    InitCategoryUI();
    InitPropUI();
    return S_OK;
}

void GameScene::Update()
{
    buildingCategoryFrame.Update();
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
}

void GameScene::Render()
{
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
}

void GameScene::Release()
{
}

void GameScene::InitClip()
{
    CLIPMANAGER->AddClip("ui_frame", "sprites/ui/pane-build.png", 378, 318);
    //카테고리 아이콘 클립
    {
		CLIPMANAGER->AddClip("defense_icon", "icons/defense.png", 16, 16);
		CLIPMANAGER->AddClip("rail_icon", "icons/distribution.png", 20, 20);
		CLIPMANAGER->AddClip("turret_icon", "icons/turret.png", 20, 20);
		CLIPMANAGER->AddClip("production_icon", "icons/production.png", 20, 20);
    }

    //설치물 아이콘 클립
    {
		CLIPMANAGER->AddClip("copper_wall", "sprites/blocks/walls/copper-wall.png", 32, 32);
		CLIPMANAGER->AddClip("mechanical_drill", "sprites/blocks/drills/mechanical-drill-icon.png", 64, 64);
		CLIPMANAGER->AddClip("duo", "sprites/blocks/turrets/duo.png", 32, 32);
		CLIPMANAGER->AddClip("conveyor", "sprites/blocks/distribution/conveyors/conveyor-0-0.png", 32, 32);
    }

    CLIPMANAGER->AddClip("button_select", "sprites/ui/button-select.9.png", 30, 30);
}

void GameScene::InitCategoryUI()
{
    buildingCategoryFrame.uiRenderer->Init("ui_frame");
    buildingCategoryFrame.uiRenderer->SetAlpha(0.7f);
    buildingCategoryFrame.transform->SetPosition(WINSIZEX - 94, WINSIZEY - 80);
    buildingCategoryFrame.transform->SetScale(0.5f, 0.5f);

    defenseIcon.uiRenderer->Init("defense_icon");
    defenseIcon.transform->SetPosition(WINSIZEX - 15, WINSIZEY - 115);
    /**********************************************************
    * 버튼 콜백함수 등록방법
    * RegistCallback 매개변수(std::bind(&클래스명::함수명, 클래스의 인스턴스, 매개변수....), 등록이벤트 종류);
    * 등록이벤트 종류
    * 1.ENTER : 마우스가 진입했을때
    * 2.EXIT : 마우스가 빠져나갔을때
    * 3.CLICK : 마우스로 클릭했을때
    ************************************************************/
    defenseIcon.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::ClickCategoryIcon, uiControler.GetComponent<UIControler>(), &defenseIcon, 3), EVENT::CLICK);

    railIcon.uiRenderer->Init("rail_icon");
    railIcon.transform->SetPosition(defenseIcon.transform->GetX() - 30, defenseIcon.transform->GetY());
    railIcon.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::ClickCategoryIcon, uiControler.GetComponent<UIControler>(), &railIcon, 2), EVENT::CLICK);

    turretIcon.uiRenderer->Init("turret_icon");
    turretIcon.transform->SetPosition(railIcon.transform->GetX(), railIcon.transform->GetY() - 26);
    turretIcon.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::ClickCategoryIcon, uiControler.GetComponent<UIControler>(), &turretIcon, 0), EVENT::CLICK);

    productionIcon.uiRenderer->Init("production_icon");
    productionIcon.transform->SetPosition(defenseIcon.transform->GetX(), turretIcon.transform->GetY());
    productionIcon.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::ClickCategoryIcon, uiControler.GetComponent<UIControler>(), &productionIcon, 1), EVENT::CLICK);

    categorySelect.uiRenderer->Init("button_select");
    categorySelect.transform->SetPosition(turretIcon.transform->GetX(), turretIcon.transform->GetY());
}

void GameScene::InitPropUI()
{
    //벽 아이콘 초기화
    {
		copperWallIcon.uiRenderer->Init("copper_wall");
		copperWallIcon.transform->SetPosition(PROP_UI_STARTX, PROP_UI_STARTY);
		copperWallIcon.transform->SetScale(0.7f, 0.7f);
		wallIconV.push_back(&copperWallIcon);

        wallIconV[0]->SetActive(false);
    }

    //드릴 아이콘 초기화
    {
		mechanicDrillIcon.uiRenderer->Init("mechanical_drill");
		mechanicDrillIcon.transform->SetPosition(PROP_UI_STARTX, PROP_UI_STARTY);
		mechanicDrillIcon.transform->SetScale(0.4f, 0.4f);
		drillIconV.push_back(&mechanicDrillIcon);

        drillIconV[0]->SetActive(false);
    }
    //터렛 아이콘 초기화
    {
        duoIcon.uiRenderer->Init("duo");
        duoIcon.transform->SetPosition(PROP_UI_STARTX, PROP_UI_STARTY);
        duoIcon.transform->SetScale(0.7f, 0.7f);
        turretIconV.push_back(&duoIcon);

    }

    //레일 아이콘 초기화
    {
        conveyorIcon.uiRenderer->Init("conveyor");
        conveyorIcon.transform->SetPosition(PROP_UI_STARTX, PROP_UI_STARTY);
        conveyorIcon.transform->SetScale(0.7f, 0.7f);
        railIconV.push_back(&conveyorIcon);

        railIconV[0]->SetActive(false);
    }

    propSelect.uiRenderer->Init("button_select");
    propSelect.transform->SetPosition(PROP_UI_STARTX, PROP_UI_STARTY);
    propSelect.SetActive(false);
}
