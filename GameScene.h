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

	//인게임 맵
	GameMap* gameMap;

    int selectCategoryIdx;

    /* SHUNG 210715-16 */
    bool   _lockDes;
    bool   _research;                       // 연구 상태 진입
    bool   _inDetail;                       // 상세 설명 상태 진입
    UIBase _choiceImg;
    UIBase _lockImg;
    UIBase _inResearchChoiceImg;            // 연구상태 내에서 기본설명 볼 때 i에 마우스 충돌이 일어났을 경우에 나오는 회색선택창

    Button _coreSlice;                      // 코어 : 조각
    Button _coreBasicDescription;           // 코어 : 조각 기본 설명
    Button _coreDetailDescriptionButton;    // 코어 : 조각 기본 설명의 [i] 주변 버튼
    UIBase _coreDetailDescriptionImg;       // 코어 : 조각 상세 설명 이미지

    Button _mechanicalDrill;                // 기계식 드릴
    Button _conveyor;                       // 컨베이어
    Button _crossover;                      // 교차기
    Button _distributor;                    // 분배기
    Button _outpost;                        // 전초기지
    Button _copper;                         // 구리
    Button _water;                          // 물
    Button _lead;                           // 납
    Button _sand;                           // 모래
    Button _duo;                            // 듀오
    Button _copperWall;                     // 구리 벽
    Button _scatter;                        // 스캐터
    Button _coreFoundation;                 // 코어 : 기반
    Button _mechanicalPump;                 // 기계식 펌프
    Button _graphiteCompressor;             // 흑연 압축기
    Button _thermalGenerator;               // 화력 발전기
    Button _groundFactory;                  // 지상 발전기
    Button _frozenForest;                   // 얼어붙은 숲
    Button _titan;                          // 티타늄
    Button _metaglass;                      // 강화 유리
    Button _scrapMetal;                     // 고철
    Button _mineral;                        // 광재
    Button _coal;                           // 석탄
    Button _largeCopperWall;                // 대형 구리 벽
    Button _titanWall;                      // 타이탄 벽
    Button _hail;                           // 헤일
    Button _scorch;                         // 스코치
    Button _launchPad;                      // 지역 자원 수송기
    Button _router;                         // 대형 분배기
    Button _sorter;                         // 필터
    Button _container;                      // 컨테이너
    Button _bridgeConveyor;                 // 다리 컨베이어
    Button _invertedSorter;                 // 반전 필터
    Button _overflowGate;                   // 포화 필터
    Button _titaniumConveyor;               // 티타늄 컨베이어
    Button _underflowGate;                  // 불포화 필터

    /* 연구 누를 경우 나오는 UI (뒤로가기, 코어 데이터 베이스) */
    UIBase _research_goBackIdleImg;
    UIBase _research_goBackChoiceImg;
    Button _research_goBackButton;
    UIBase _coreDBIdleImg;
    UIBase _coreDBChoiceImg;
    Button _coreDBButton;

    /* UI 상세보기 누를 경우 나오는 UI (뒤로가기) */
    UIBase _detailDes_goBackIdleImg;
    UIBase _detailDes_goBackChoiceImg;
    Button _detailDes_goBackButton;

	// EnemyManager 210717 작업 - 민재 // 
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

    // EnemyManager 210717 작업 - 민재 // 
    void SetProjectileManager();
	void SetCore();
	void SetEnemyManager();
};

