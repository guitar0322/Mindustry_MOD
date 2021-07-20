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

	//�ΰ��� ��
	GameMap* gameMap;

    int selectCategoryIdx;

    /* SHUNG 210715-16 */
    bool   _lockDes;
    bool   _research;                       // ���� ���� ����
    bool   _inDetail;                       // �� ���� ���� ����
    UIBase _choiceImg;
    UIBase _lockImg;
    UIBase _inResearchChoiceImg;            // �������� ������ �⺻���� �� �� i�� ���콺 �浹�� �Ͼ�� ��쿡 ������ ȸ������â

    Button _coreSlice;                      // �ھ� : ����
    Button _coreBasicDescription;           // �ھ� : ���� �⺻ ����
    Button _coreDetailDescriptionButton;    // �ھ� : ���� �⺻ ������ [i] �ֺ� ��ư
    UIBase _coreDetailDescriptionImg;       // �ھ� : ���� �� ���� �̹���

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
    UIBase _research_goBackIdleImg;
    UIBase _research_goBackChoiceImg;
    Button _research_goBackButton;
    UIBase _coreDBIdleImg;
    UIBase _coreDBChoiceImg;
    Button _coreDBButton;

    /* UI �󼼺��� ���� ��� ������ UI (�ڷΰ���) */
    UIBase _detailDes_goBackIdleImg;
    UIBase _detailDes_goBackChoiceImg;
    Button _detailDes_goBackButton;

	// EnemyManager 210717 �۾� - ���� // 
	GameObject* _enemyManager;
	Prop* _core;

public:
    virtual HRESULT Init();
    virtual void Update();
    virtual void Render();
    virtual void Release();
    void InitClip();
    void InitCategoryUI();
    void InitPropUI();

    /* SHUNG 210718 */
    void researchUpdate();
    void researchRender();
    void researchInitUI();

    // EnemyManager 210717 �۾� - ���� // 
    void SetProjectileManager();
	void SetCore();
	void SetEnemyManager();
};

