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
	/* =========== 플레이어 부분 -> 유림 ============*/

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

	//인게임 맵 -> 유림
	GameMap* _gameMap;

	//인게임 자원UI 관련 -> 유림
	Rect _resoucesUIBackGround;
	UIBase _resourcesUI[2];
	int test;

    int selectCategoryIdx;

    /* 시영 - 연구부분 */
    bool    _lockDes;
    bool    _research;                       // 연구 상태
    bool    _inDetail;                       // 상세 설명 상태
    bool    _all_Resources_State;            // 전체 자원 [열림], [닫힘] 상태

    int     _all_Resources_Count;            // 전체 자원 개수
    UIBase  _all_Resources_Open1_Img;        // 전체 자원 [열림] 1개
    UIBase  _all_Resources_Open2_Img;        // 전체 자원 [열림] 2개
    UIBase  _all_Resources_Open3_Img;        // 전체 자원 [열림] 3개
    UIBase  _all_Resources_Close_Img;        // 전체 자원 [닫힘]
    UIBase  _all_Resources_Img;              // 전체 자원 이미지 (충돌 - 회색)
    UIBase  _all_Resources_Text;             // 전체 자원 텍스트
    Button  _all_Resources_Button;           // 전체 자원 버튼
    UIBase  _all_Resources_Mineral[3];       // 전체 자원 광물 이미지 
    wstring _all_Resources_Copper_Count;
    wstring _all_Resources_Lead_Count;
    wstring _all_Resources_Scrap_Count;

    UIBase  _choiceImg;
    UIBase  _lockImg;                        // 연구 상태 자물쇠 이미지
    UIBase  _inResearchChoiceImg;            // 연구상태 내 기본설명 볼 때 i에 마우스 충돌이 일어났을 경우에 나오는 회색선택창

    Button  _coreSlice;                      // 코어 : 조각
    Button  _coreBasicDescription;           // 코어 : 조각 기본 설명
    Button  _coreDetailDescriptionButton;    // 코어 : 조각 기본 설명의 [i] 주변 버튼
    UIBase  _coreDetailDescriptionImg;       // 코어 : 조각 상세 설명 이미지

    Button  _mechanicalDrill;                // 기계식 드릴
    Button  _conveyor;                       // 컨베이어
    Button  _crossover;                      // 교차기
    Button  _distributor;                    // 분배기
    Button  _outpost;                        // 전초기지
    Button  _copper;                         // 구리
    Button  _water;                          // 물
    Button  _lead;                           // 납
    Button  _sand;                           // 모래
    Button  _duo;                            // 듀오
    Button  _copperWall;                     // 구리 벽
    Button  _scatter;                        // 스캐터
    Button  _coreFoundation;                 // 코어 : 기반
    Button  _mechanicalPump;                 // 기계식 펌프
    Button  _graphiteCompressor;             // 흑연 압축기
    Button  _thermalGenerator;               // 화력 발전기
    Button  _groundFactory;                  // 지상 발전기
    Button  _frozenForest;                   // 얼어붙은 숲
    Button  _titan;                          // 티타늄
    Button  _metaglass;                      // 강화 유리
    Button  _scrapMetal;                     // 고철
    Button  _mineral;                        // 광재
    Button  _coal;                           // 석탄
    Button  _largeCopperWall;                // 대형 구리 벽
    Button  _titanWall;                      // 타이탄 벽
    Button  _hail;                           // 헤일
    Button  _scorch;                         // 스코치
    Button  _launchPad;                      // 지역 자원 수송기
    Button  _router;                         // 대형 분배기
    Button  _sorter;                         // 필터
    Button  _container;                      // 컨테이너
    Button  _bridgeConveyor;                 // 다리 컨베이어
    Button  _invertedSorter;                 // 반전 필터
    Button  _overflowGate;                   // 포화 필터
    Button  _titaniumConveyor;               // 티타늄 컨베이어
    Button  _underflowGate;                  // 불포화 필터

    /* 연구 누를 경우 나오는 UI (뒤로가기, 코어 데이터 베이스) */
    UIBase  _research_goBackIdleImg;
    UIBase  _research_goBackChoiceImg;
    Button  _research_goBackButton;
    UIBase  _coreDBIdleImg;
    UIBase  _coreDBChoiceImg;
    Button  _coreDBButton;

    /* UI 상세보기 누를 경우 나오는 UI (뒤로가기) */
    UIBase  _detailDes_goBackIdleImg;
    UIBase  _detailDes_goBackChoiceImg;
    Button  _detailDes_goBackButton;

    /* 시영 - 메뉴부분 */
    bool    _menu;                          // 메뉴 상태

    UIBase  _menuImg;                       // 메뉴 이미지

    UIBase  _menu_GoBackIdleImg;            // 메뉴 [돌아가기] 기본 상태 이미지
    UIBase  _menu_GoBackChoiceImg;          // 메뉴 [돌아가기] 선택 상태 이미지
    Button  _menu_GoBackButton;             // 메뉴 [돌아가기] 버튼

    UIBase  _menu_SettingIdleImg;           // 메뉴 [설정] 기본 상태 이미지
    UIBase  _menu_SettingChoiceImg;         // 메뉴 [설정] 선택 상태 이미지
    Button  _menu_SettingButton;            // 메뉴 [설정] 버튼

    UIBase  _menu_SaveAndExitIdleImg;       // 메뉴 [저장 후 나가기] 기본 상태 이미지
    UIBase  _menu_SaveAndExitChoiceImg;     // 메뉴 [저장 후 나가기] 선택 상태 이미지
    Button  _menu_SaveAndExitButton;        // 메뉴 [저장 후 나가기] 버튼

    bool    _menu_ReallyEnd;                // 정말로 종료하시겠습니까 상태

    UIBase  _menu_ReallyEnd_Img;            // 정말로 종료하시겠습니까? 이미지

    UIBase  _menu_ReallyEnd_Cancle_Idle;    // 정말로 종료하시겠습니까? [취소] 기본 상태 이미지
    UIBase  _menu_ReallyEnd_Cancle_Choice;  // 정말로 종료하시겠습니까? [취소] 선택 상태 이미지
    Button  _menu_ReallyEnd_Cancle_Button;  // 정말로 종료하시겠습니까? [취소] 버튼

    UIBase  _menu_ReallyEnd_Check_Idle;     // 정말로 종료하시겠습니까? [확인] 기본 상태 이미지
    UIBase  _menu_ReallyEnd_Check_Choice;   // 정말로 종료하시겠습니까? [확인] 선택 상태 이미지
    Button  _menu_ReallyEnd_Check_Button;   // 정말로 종료하시겠습니까? [확인] 버튼

	// EnemyManager 210717 작업 - 민재 // 
	GameObject* _enemyManager;
	Core* _core;
	//// 07/20 민재 Enemy WAve 및 Player UI 작업/////
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

	/*유림 210719*/
	//플레이어
	void PlayerClip();
	void PlayerInit();
	//자원
	void ResourcesInit();
	void ResourcesUpdate();
	void ResourcesRender();

    /* 시영 */
    // 연구
    void researchInitUI();
    void researchUpdate();
    void researchRender();
    // 메뉴
    void menuInitUI();
    void menuUpdate();
    void menuRender();

    // EnemyManager 210717 작업 - 민재 // 
    void SetProjectileManager();
	void SetCore();
	void SetEnemyManager();
	void SetCameraControler();
	void SetGameUI();
	void InGameUIUpdate();
	void InGameUIRender();

	/* 화면에 문자 띄울 때 여기 쓰세요 - 유림 (210719)*/
	void StringRender();

};

