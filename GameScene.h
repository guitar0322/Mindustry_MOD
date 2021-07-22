#pragma once
#include "Scene.h"
#include "Button.h"
#include "GameMap.h"
#include "Player.h"
#include "ProjectileManager.h"
#include "Prop.h"

#define PROP_UI_STARTX WINSIZEX - 230
#define PROP_UI_STARTY WINSIZEY - 187
#define CATEGORY_UI_STARTX WINSIZEX - 65
#define CATEGORY_UI_STARTY WINSIZEY - 190

class PropContainer;
class PropFactory;
class UIControler;
class GameInfo;
class Item;
class ResourceManager;
class Core;
class Astar;

class GameScene :
    public Scene
{
private:
	float _musicTime;

    Item* testCopper;
	/* ============================================*/
	/* =========== �÷��̾� �κ� -> ���� ============*/

	Player* _player;
	ImageObject* _playerWeaponL;
	ImageObject* _playerWeaponR;
	ImageObject* _playerCell;
	ImageObject* _playerFireCircle;
	ImageObject* _playerFire;
	GameObject* _projectileManager;

	//======
    PropContainer* _propContainer;
    PropFactory* _propFactory;
    ResourceManager* _resourceManager;
    GameInfo* _gameInfo;
    Astar* _aStar;
    UIControler* _uiControler;
    UIBase _categorySelect;
    UIBase _propSelect;

    ImageObject _propPreview;

    UIBase _buildingCategoryFrame;
    UIBase _defenseIcon;
    UIBase _railIcon;
    UIBase _turretIcon;
    UIBase _productionIcon;

    UIBase _copperWallIcon;
    UIBase _mechanicDrillIcon;
    UIBase _duoIcon;
    UIBase _conveyorIcon;

    vector<GameObject*> _wallIconV;
    vector<GameObject*> _drillIconV;
    vector<GameObject*> _turretIconV;
    vector<GameObject*> _railIconV;

	//�ΰ��� �� -> ����
	GameMap* _gameMap;

	//�ΰ��� �ڿ�UI ���� -> ����
	Rect _resoucesUIBackGround;
	UIBase _resourcesUI[2];
	int test;

    int selectCategoryIdx;

    /* �ÿ� - �����κ� */
    bool    _lockDes;
    bool    _research;                       // ���� ����
    bool    _inDetail;                       // �� ���� ����
    bool    _all_Resources_State;            // ��ü �ڿ� [����], [����] ����

    int     _all_Resources_Count;            // ��ü �ڿ� ����
    UIBase  _all_Resources_Open1_Img;        // ��ü �ڿ� [����] 1��
    UIBase  _all_Resources_Open2_Img;        // ��ü �ڿ� [����] 2��
    UIBase  _all_Resources_Open3_Img;        // ��ü �ڿ� [����] 3��
    UIBase  _all_Resources_Close_Img;        // ��ü �ڿ� [����]
    UIBase  _all_Resources_Img;              // ��ü �ڿ� �̹��� (�浹 - ȸ��)
    UIBase  _all_Resources_Text;             // ��ü �ڿ� �ؽ�Ʈ
    Button  _all_Resources_Button;           // ��ü �ڿ� ��ư
    UIBase  _all_Resources_Mineral[3];       // ��ü �ڿ� ���� �̹��� 
    wstring _all_Resources_Copper_Count;
    wstring _all_Resources_Lead_Count;
    wstring _all_Resources_Scrap_Count;

    UIBase  _choiceImg;
    UIBase  _lockImg;                        // ���� ���� �ڹ��� �̹���
    UIBase  _inResearchChoiceImg;            // �������� �� �⺻���� �� �� i�� ���콺 �浹�� �Ͼ�� ��쿡 ������ ȸ������â

    Button  _coreSlice;                      // �ھ� : ����
    Button  _coreBasicDescription;           // �ھ� : ���� �⺻ ����
    Button  _coreDetailDescriptionButton;    // �ھ� : ���� �⺻ ������ [i] �ֺ� ��ư
    UIBase  _coreDetailDescriptionImg;       // �ھ� : ���� �� ���� �̹���

    Button  _mechanicalDrill;                // ���� �帱
    Button  _conveyor;                       // �����̾�
    Button  _crossover;                      // ������
    Button  _distributor;                    // �й��
    Button  _outpost;                        // ���ʱ���
    Button  _copper;                         // ����
    Button  _water;                          // ��
    Button  _lead;                           // ��
    Button  _sand;                           // ��
    Button  _duo;                            // ���
    Button  _copperWall;                     // ���� ��
    Button  _scatter;                        // ��ĳ��
    Button  _coreFoundation;                 // �ھ� : ���
    Button  _mechanicalPump;                 // ���� ����
    Button  _graphiteCompressor;             // �濬 �����
    Button  _thermalGenerator;               // ȭ�� ������
    Button  _groundFactory;                  // ���� ������
    Button  _frozenForest;                   // ������ ��
    Button  _titan;                          // ƼŸ��
    Button  _metaglass;                      // ��ȭ ����
    Button  _scrapMetal;                     // ��ö
    Button  _mineral;                        // ����
    Button  _coal;                           // ��ź
    Button  _largeCopperWall;                // ���� ���� ��
    Button  _titanWall;                      // Ÿ��ź ��
    Button  _hail;                           // ����
    Button  _scorch;                         // ����ġ
    Button  _launchPad;                      // ���� �ڿ� ���۱�
    Button  _router;                         // ���� �й��
    Button  _sorter;                         // ����
    Button  _container;                      // �����̳�
    Button  _bridgeConveyor;                 // �ٸ� �����̾�
    Button  _invertedSorter;                 // ���� ����
    Button  _overflowGate;                   // ��ȭ ����
    Button  _titaniumConveyor;               // ƼŸ�� �����̾�
    Button  _underflowGate;                  // ����ȭ ����

    /* ���� ���� ��� ������ UI (�ڷΰ���, �ھ� ������ ���̽�) */
    UIBase  _research_goBackIdleImg;
    UIBase  _research_goBackChoiceImg;
    Button  _research_goBackButton;
    UIBase  _coreDBIdleImg;
    UIBase  _coreDBChoiceImg;
    Button  _coreDBButton;

    /* UI �󼼺��� ���� ��� ������ UI (�ڷΰ���) */
    UIBase  _detailDes_goBackIdleImg;
    UIBase  _detailDes_goBackChoiceImg;
    Button  _detailDes_goBackButton;

    /* �ÿ� - �޴��κ� */
    bool    _menu;                          // �޴� ����

    UIBase  _menuImg;                       // �޴� �̹���

    UIBase  _menu_GoBackIdleImg;            // �޴� [���ư���] �⺻ ���� �̹���
    UIBase  _menu_GoBackChoiceImg;          // �޴� [���ư���] ���� ���� �̹���
    Button  _menu_GoBackButton;             // �޴� [���ư���] ��ư

    UIBase  _menu_SettingIdleImg;           // �޴� [����] �⺻ ���� �̹���
    UIBase  _menu_SettingChoiceImg;         // �޴� [����] ���� ���� �̹���
    Button  _menu_SettingButton;            // �޴� [����] ��ư

    UIBase  _menu_SaveAndExitIdleImg;       // �޴� [���� �� ������] �⺻ ���� �̹���
    UIBase  _menu_SaveAndExitChoiceImg;     // �޴� [���� �� ������] ���� ���� �̹���
    Button  _menu_SaveAndExitButton;        // �޴� [���� �� ������] ��ư

    bool    _menu_ReallyEnd;                // ������ �����Ͻðڽ��ϱ� ����

    UIBase  _menu_ReallyEnd_Img;            // ������ �����Ͻðڽ��ϱ�? �̹���

    UIBase  _menu_ReallyEnd_Cancle_Idle;    // ������ �����Ͻðڽ��ϱ�? [���] �⺻ ���� �̹���
    UIBase  _menu_ReallyEnd_Cancle_Choice;  // ������ �����Ͻðڽ��ϱ�? [���] ���� ���� �̹���
    Button  _menu_ReallyEnd_Cancle_Button;  // ������ �����Ͻðڽ��ϱ�? [���] ��ư

    UIBase  _menu_ReallyEnd_Check_Idle;     // ������ �����Ͻðڽ��ϱ�? [Ȯ��] �⺻ ���� �̹���
    UIBase  _menu_ReallyEnd_Check_Choice;   // ������ �����Ͻðڽ��ϱ�? [Ȯ��] ���� ���� �̹���
    Button  _menu_ReallyEnd_Check_Button;   // ������ �����Ͻðڽ��ϱ�? [Ȯ��] ��ư

	// EnemyManager 210717 �۾� - ���� // 
	GameObject* _enemyManager;
	Core* _core;
	//// 07/20 ���� Enemy WAve �� Player UI �۾�/////
	UIBase _wavePane;
	UIBase _playerUi;
	UIBase _playerHpUi;

	UIBase _enemyWaveSkip;
	Button _enemyWaveSkipButton;

	UIBase _enemyWaveSkipClick;

    GameObject* _cameraControler;
public:
    virtual HRESULT Init();
    virtual void Update();
    virtual void Render();
    virtual void Release();
    void InitClip();
    void InitCategoryUI();
    void InitPropUI();

	/*���� 210719*/
	//�÷��̾�
	void PlayerClip();
	void PlayerInit();
	//�ڿ�
	void ResourcesInit();
	void ResourcesUpdate();
	void ResourcesRender();

    /* �ÿ� */
    // ����
    void researchInitUI();
    void researchUpdate();
    void researchRender();
    // �޴�
    void menuInitUI();
    void menuUpdate();
    void menuRender();

    // EnemyManager 210717 �۾� - ���� // 
    void SetProjectileManager();
	void SetCore();
	void SetEnemyManager();
	void SetCameraControler();
	void SetGameUI();
	void InGameUIUpdate();
	void InGameUIRender();

	/* ȭ�鿡 ���� ��� �� ���� ������ - ���� (210719)*/
	void StringRender();

};

