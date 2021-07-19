#pragma once
#include "Scene.h"
#include "Button.h"
#include "GameMap.h"
#include "Player.h"
#include "ProjectileManager.h"
#include "Prop.h"
#include "CameraControler.h"

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
	float _musicTime;
    Cam* _miniMapCam;
	Player* _player;
	ImageObject* _playerWeaponL;
	ImageObject* _playerWeaponR;
	GameObject* _projectileManager;
	//======
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

	//¿Œ∞‘¿” ∏ 
	GameMap* gameMap;

    int selectCategoryIdx;

    /* SHUNG 210715 */
    UIBase _choiceImg;
    Button _CoreSlice;

	// EnemyManager // 
	GameObject* _enemyManager;
	Prop* _core;
	CameraControler* _cameraControler;

public:
    virtual HRESULT Init();
    virtual void Update();
    virtual void Render();
    virtual void Release();
    void InitClip();
    void InitCategoryUI();
    void InitPropUI();
	void SetProjectileManager();
	void SetCore();
	void SetEnemyManager();
	void SetCameraControler();
};

