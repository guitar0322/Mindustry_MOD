#pragma once
#include "Scene.h"
#include "Button.h"
#include "GameMap.h"
#include "Player.h"
#include "ProjectileManager.h"

#define PROP_UI_STARTX WINSIZEX - 230
#define PROP_UI_STARTY WINSIZEY - 187
#define CATEGORY_UI_STARTX WINSIZEX - 65
#define CATEGORY_UI_STARTY WINSIZEY - 190
class PropContainer;
class PropFactory;
class UIControler;
class GameInfo;

class GameScene :
    public Scene
{
private:
	Player* _player;
	GameObject* _projectileManager;

	/* 인게임 게임 시스템 객체*/
    PropContainer* propContainer;
    PropFactory* propFactory;
    UIControler* uiControler;
    GameInfo* gameInfo;

    UIBase categorySelect;
    UIBase propSelect;

    ImageObject propPreview;

    UIBase buildingCategoryFrame;
    UIBase defenseIcon;
    UIBase railIcon;
    UIBase turretIcon;
    UIBase productionIcon;

    UIBase copperWallIcon;
    UIBase mechanicDrillIcon;
    UIBase duoIcon;
    UIBase conveyorIcon;

    vector<GameObject*> wallIconV;
    vector<GameObject*> drillIconV;
    vector<GameObject*> turretIconV;
    vector<GameObject*> railIconV;

	//인게임 맵
	GameMap* gameMap;

    int selectCategoryIdx;

    /* SHUNG 210715 */
    UIBase _choiceImg;
    Button _CoreSlice;

public:
    virtual HRESULT Init();
    virtual void Update();
    virtual void Render();
    virtual void Release();
    void InitClip();
    void InitCategoryUI();
    void InitPropUI();
};

