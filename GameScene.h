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

    /* SHUNG 210715-16 */
    bool   _research;
    bool   _lockDes;
    UIBase _choiceImg;
    UIBase _lockImg;
    UIBase _inResearchChoiceImg;            // �������� ������ �⺻���� �� �� i�� ���콺 �浹�� �Ͼ�� ��쿡 ������ ȸ������â

    Button _coreSlice;                      // �ھ� : ����
    Button _coreBasicDescription;           // �ھ� : ���� �⺻ ����
    Button _coreDetailDescription;          // �ھ� : ���� �� ���� ��ư [i]

    Button _mechanicalDrill;                // ���� �帱
    Button _conveyor;                       // �����̾�
    Button _crossover;                      // ������
    Button _distributor;                    // �й��
    Button _outpost;                        // ���ʱ���
    Button _copper;                         // ����
    Button _water;                          // ��
    Button _lead;                           // ��
    Button _sand;                           // ��
    Button _duo;                            // ���
    Button _copperWall;                     // ���� ��
    Button _scatter;                        // ��ĳ��
    Button _coreFoundation;                 // �ھ� : ���
    Button _mechanicalPump;                 // ���� ����
    Button _graphiteCompressor;             // �濬 �����
    Button _thermalGenerator;               // ȭ�� ������
    Button _groundFactory;                  // ���� ������
    Button _frozenForest;                   // ������ ��
    Button _titan;                          // ƼŸ��
    Button _metaglass;                      // ��ȭ ����
    Button _scrapMetal;                     // ��ö
    Button _mineral;                        // ����
    Button _coal;                           // ��ź
    Button _largeCopperWall;                // ���� ���� ��
    Button _titanWall;                      // Ÿ��ź ��
    Button _hail;                           // ����
    Button _scorch;                         // ����ġ
    Button _launchPad;                      // ���� �ڿ� ���۱�
    Button _router;                         // ���� �й��
    Button _sorter;                         // ����
    Button _container;                      // �����̳�
    Button _bridgeConveyor;                 // �ٸ� �����̾�
    Button _invertedSorter;                 // ���� ����
    Button _overflowGate;                   // ��ȭ ����
    Button _titaniumConveyor;               // ƼŸ�� �����̾�
    Button _underflowGate;                  // ����ȭ ����

    /* ���� ���� ��� ������ UI (�ڷΰ���, �ھ� ������ ���̽�) */
    UIBase _goBackIdleImg;
    UIBase _goBackChoiceImg;
    Button _goBackButton;
    UIBase _coreDBIdleImg;
    UIBase _coreDBChoiceImg;
    Button _coreDBButton;
    Button _CoreSlice;

	// EnemyManager 210717 �۾� - ���� // 
	GameObject* _enemyManager;
	Prop* _core;
	//// 07/20 ���� Enemy WAve �� Player UI �۾�/////
	UIBase _wavePane;
	UIBase _playerUi;
	UIBase _playerHpUi;
	UIBase _waveSkipUi;

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

    /* SHUNG 210718 */
    void researchUpdate();
    void researchRender();
    void researchInitUI();

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

