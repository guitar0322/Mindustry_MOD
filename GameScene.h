#pragma once
#include "Scene.h"
#include "Button.h"
#define PROP_UI_STARTX WINSIZEX - 170
#define PROP_UI_STARTY WINSIZEY - 140
class GameScene :
    public Scene
{
private:
    GameObject uiControler;
    UIBase categorySelect;
    UIBase propSelect;

    UIBase buildingCategoryFrame;
    Button defenseIcon;
    Button railIcon;
    Button turretIcon;
    Button productionIcon;

    Button copperWallIcon;
    Button mechanicDrillIcon;
    Button duoIcon;
    Button conveyorIcon;

    vector<GameObject*> wallIconV;
    vector<GameObject*> drillIconV;
    vector<GameObject*> turretIconV;
    vector<GameObject*> railIconV;

    int selectCategoryIdx;
public:
    virtual HRESULT Init();
    virtual void Update();
    virtual void Render();
    virtual void Release();
    void InitClip();
    void InitCategoryUI();
    void InitPropUI();
};

