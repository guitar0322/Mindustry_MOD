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
class UIControler;

class GameScene :
    public Scene
{
private:
	Player* _player;
	GameObject* _projectileManager;

	//======
    PropContainer* propContainer;
    UIControler* uiControler;
    UIBase categorySelect;
    UIBase propSelect;

    ImageObject propPreview;

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

	//¿Œ∞‘¿” ∏ 
	GameMap* gameMap;

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

