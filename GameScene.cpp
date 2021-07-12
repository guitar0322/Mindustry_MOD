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
    uiControler.GetComponent<UIControler>()->propSelect = &propSelect;
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
    propSelect.Update();
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
    propSelect.Render();
}

void GameScene::Release()
{
}

void GameScene::InitClip()
{
    CLIPMANAGER->AddClip("ui_frame", "sprites/ui/pane-build.png", 378, 318);
    //카테고리 아이콘 클립
    {
		CLIPMANAGER->AddClip("defense_icon", "icons/defense.png", 32, 32);
		CLIPMANAGER->AddClip("rail_icon", "icons/distribution.png", 32, 32);
		CLIPMANAGER->AddClip("turret_icon", "icons/turret.png", 32, 32);
		CLIPMANAGER->AddClip("production_icon", "icons/production.png", 32, 32);
    }

    //설치물 아이콘 클립
    {
		CLIPMANAGER->AddClip("copper_wall", "sprites/blocks/walls/copper-wall.png", 32, 32);
		CLIPMANAGER->AddClip("mechanical_drill", "sprites/blocks/drills/mechanical-drill-icon.png", 64, 64);
		CLIPMANAGER->AddClip("duo", "sprites/blocks/turrets/duo.png", 32, 32);
		CLIPMANAGER->AddClip("conveyor", "sprites/blocks/distribution/conveyors/conveyor-0-0.png", 32, 32);
    }

    CLIPMANAGER->AddClip("button_select", "sprites/ui/button-select.10.png", 52, 52);
}

void GameScene::InitCategoryUI()
{
    buildingCategoryFrame.uiRenderer->Init("ui_frame");
    buildingCategoryFrame.uiRenderer->SetAlpha(0.7f);
    buildingCategoryFrame.transform->SetPosition(WINSIZEX - 132, WINSIZEY - 111);
    buildingCategoryFrame.transform->SetScale(0.7f, 0.7f);

    defenseIcon.uiRenderer->Init("defense_icon");
    defenseIcon.transform->SetPosition(WINSIZEX - 20, WINSIZEY - 150);
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
    railIcon.transform->SetPosition(defenseIcon.transform->GetX() - 40, defenseIcon.transform->GetY());
    railIcon.uiMouseEvent->RegistCallback(
        std::bind(&UIControler::ClickCategoryIcon, uiControler.GetComponent<UIControler>(), &railIcon, 2), EVENT::CLICK);

    turretIcon.uiRenderer->Init("turret_icon");
    turretIcon.transform->SetPosition(railIcon.transform->GetX(), railIcon.transform->GetY() - 40);
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
        copperWallIcon.uiMouseEvent->RegistCallback(
            std::bind(&UIControler::ClickPropIcon, uiControler.GetComponent<UIControler>(), &copperWallIcon), EVENT::CLICK);
		wallIconV.push_back(&copperWallIcon);

        for (int i = 0; i < wallIconV.size(); i++)
        {
            wallIconV[i]->SetActive(false);
        }
    }

    //드릴 아이콘 초기화
    {
		mechanicDrillIcon.uiRenderer->Init("mechanical_drill");
		mechanicDrillIcon.transform->SetPosition(PROP_UI_STARTX, PROP_UI_STARTY);
		mechanicDrillIcon.transform->SetScale(0.5f, 0.5f);
        mechanicDrillIcon.uiMouseEvent->RegistCallback(
            std::bind(&UIControler::ClickPropIcon, uiControler.GetComponent<UIControler>(), &mechanicDrillIcon), EVENT::CLICK);
		drillIconV.push_back(&mechanicDrillIcon);

        for (int i = 0; i < drillIconV.size(); i++)
        {
            drillIconV[i]->SetActive(false);
        }
    }
    //터렛 아이콘 초기화
    {
        duoIcon.uiRenderer->Init("duo");
        duoIcon.transform->SetPosition(PROP_UI_STARTX, PROP_UI_STARTY);
        duoIcon.uiMouseEvent->RegistCallback(
            std::bind(&UIControler::ClickPropIcon, uiControler.GetComponent<UIControler>(), &duoIcon), EVENT::CLICK);
        turretIconV.push_back(&duoIcon);

    }

    //레일 아이콘 초기화
    {
        conveyorIcon.uiRenderer->Init("conveyor");
        conveyorIcon.transform->SetPosition(PROP_UI_STARTX, PROP_UI_STARTY);
        conveyorIcon.uiMouseEvent->RegistCallback(
            std::bind(&UIControler::ClickPropIcon, uiControler.GetComponent<UIControler>(), &conveyorIcon), EVENT::CLICK);
        railIconV.push_back(&conveyorIcon);

        for (int i = 0; i < railIconV.size(); i++)
        {
            railIconV[i]->SetActive(false);
        }
    }

    propSelect.uiRenderer->Init("button_select");
    propSelect.transform->SetPosition(PROP_UI_STARTX, PROP_UI_STARTY);
    propSelect.SetActive(false);
}
