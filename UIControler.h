#pragma once
#include "PropFactory.h"
#include <map>
#include <queue>
#include "PropInfo.h"
#define CATEGORY_NUM 4

using namespace std;
class GameMap;
class Button;
class EnemyManager;
class PlayerControler;

class UIControler
{
private:
    int _selectCategoryIdx;
    int _selectPropIdx;
    int _previewNum;
    Vector2 _deleteStart;
    bool _previewDir;
    Vector2 _worldStartPtMouse;
    vector<string> _clipArr[CATEGORY_NUM];
    vector<ImageObject> _previewV;
    PROPDIR _dir;
    Rect _deleteRc;
    PlayerControler* _playerControler;
public:
    GameMap* gameMap;
    PropFactory* propFactory;
    PropContainer* propContainer;
    UIControler();
    ~UIControler();
    GameObject* categorySelect;
    GameObject* propSelect;
    ImageObject* propPreview;
    ImageObject conveyorArrow;
    vector<GameObject*>* wallIconV;
    vector<GameObject*>* drillIconV;
    vector<GameObject*>* turretIconV;
    vector<GameObject*>* railIconV;
    vector<GameObject*>* preIconV;
    void Init();
    void Update();
    void Release();
    void Render();
    void ClickCategoryIcon(GameObject* clickedButton, int category);
    void ClickPropIcon(GameObject* clickedButton, int propIdx);
    void RefreshPreview();
    void SetPreview(float deltaX, float deltaY);
    void SetPreviewTwo(float deltaX, float deltaY);
    void CheckValidTile();
    void LinkPlayerControler(PlayerControler* playerControler) { _playerControler = playerControler; }

    /* 시영 */
    bool* isMineral;

    /* 아이콘 */
    UIBase* coreDBIcon;                         // 코어 데이터베이스 아이콘
    UIBase* researchIcon;                       // 연구 아이콘
    UIBase* inGame_TouchToIcon;                 // 게임화면 내에서 카테고리 아이콘에 ENTER 됐을 경우 나오는 회색 이미지

    // 연구
    /* 전체 자원 버튼 (회색) */
    int     all_Resources_Count;

    UIBase* all_Resources_Open1_Img;            // 전체 자원 [열림] 1개
    UIBase* all_Resources_Open2_Img;            // 전체 자원 [열림] 2개
    UIBase* all_Resources_Open3_Img;            // 전체 자원 [열림] 3개
    UIBase* all_Resources_Close_Img;            // 전체 자원 [닫힘]
    UIBase* all_Resources_Img;                  // 전체 자원 버튼 (회색)
    UIBase* all_Resources_Text;                 // 전체 자원 텍스트

    /* ? */
    UIBase* choiceImg;
    UIBase* lockImg;
    UIBase* inResearchChoiceImg;

    /* 연구 */
    UIBase* research_goBackIdleImg;             // 연구 [뒤로가기] 기본 상태 이미지
    UIBase* research_goBackChoiceImg;           // 연구 [뒤로가기] 선택 상태 이미지
    UIBase* coreDBIdleImg;                      // 연구 [코어 데이터베이스] 기본 상태 이미지
    UIBase* coreDBChoiceImg;                    // 연구 [코어 데이터베이스] 선택 상태 이미지

    /* 상세보기 */
    UIBase* detailDes_GoBackIdleImg;            // 연구 - 상세보기 [뒤로가기] 기본 상태 이미지
    UIBase* detailDes_GoBackChoiceImg;          // 연구 - 상세보기 [뒤로가기] 선택 상태 이미지

    // 메뉴
    UIBase* menu_GoBackIdleImg;                 // 메뉴 [돌아가기] 기본 상태 이미지
    UIBase* menu_GoBackChoiceImg;               // 메뉴 [돌아가기] 선택 상태 이미지
    UIBase* menu_SettingIdleImg;                // 메뉴 [설정] 기본 상태 이미지
    UIBase* menu_SettingChoiceImg;              // 메뉴 [설정] 선택 상태 이미지
    UIBase* menu_SaveAndExitIdleImg;            // 메뉴 [저장 후 나가기] 기본 상태 이미지
    UIBase* menu_SaveAndExitChoiceImg;          // 메뉴 [저장 후 나가기] 선택 상태 이미지
    Button* menu_SaveAndExitButton;             // 메뉴 [저장 후 나가기] 버튼

    /* 정말로 종료? */
    UIBase* menu_ReallyEnd_Img;                 // 정말로 종료하시겠습니까? 이미지
    UIBase* menu_ReallyEnd_Check_Idle;          // 정말로 종료하시겠습니까? [확인] 기본 상태 이미지
    UIBase* menu_ReallyEnd_Check_Choice;        // 정말로 종료하시겠습니까? [확인] 선택 상태 이미지
    UIBase* menu_ReallyEnd_Cancle_Idle;         // 정말로 종료하시겠습니까? [취소] 기본 상태 이미지b
    UIBase* menu_ReallyEnd_Cancle_Choice;       // 정말로 종료하시겠습니까? [취소] 선택 상태 이미지

    /* 커서 (광물) 전용 함수 */
    void inGame_Crash_To_Mineral_Cursor();

    /* 게임 상태에서 [아이콘] ENTERT, EXIT */
    void inGame_Acitve_Choice_Img(GameObject* clickedButton, bool isAcitve);

    /* 게임 상태에서 [연구 아이콘] CLICK */
    void inGame_Acitve_State(bool* name, bool isAcitve);

    void inResearch_ActiveChoiceImg(Transform* menuTr, bool isActive);

    /* 연구 상태에서 [전체자원] 버튼 EVENT */
    void inResearch_Active_Choice_Img(bool* name);
    /* 연구 상태에서 [전체자원] 버튼 CLICK*/
    void inResearch_Active_all_Resources_Click_Event(bool* name);
    /* 연구 상태에서 [전체자원] 버튼 EXIT */
    void inResearch_InActive_Choice_Img();
    
    /* 연구 상태에서 [돌아가기] 버튼 ENTER, EXIT */
    void inResearch_ActiveGoBackImg(bool isActive);
    /* 연구 상태에서 [돌아가기] 버튼 CLICK */
    void inResearch_ReturnToGameScene(bool* name, bool isActive);

    /* 연구 상태에서 [코어 DB] 버튼 ENTER, EXIT */
    void inResearch_ActiveCoreDBImg(bool isActive);
    /* 연구 상태에서 [코어 DB] 버튼 CLICK */
    void inResearch_ReturnToCoreDBScene(bool* name, bool isActive);
    
    /* 연구 상태에서 [개개인의 객체] 버튼 ENTER */
    void inResearch_ActiveChoiceImgWithBasicDes(Transform* menuTr, UIBase* name, Button* name2, bool* name3, bool isActive);
    /* 연구 상태에서 [개개인의 객체] 버튼 EXIT */
    void inResearch_inActiveChoiceImgWithBasicDes(Transform* menuTr, UIBase* name, bool* name2, Button* name3, bool isActive);

    /* 연구 상태에서 [기본 설명] 버튼 ENTER */
    void inResearch_inBasicDes(Transform* menuTr, UIBase* name, bool* name2, bool isActive);
    /* 연구 상태에서 [기본 설명] 버튼 EXIT */
    void inResearch_disableInBasicDes(Transform* menuTr, UIBase* name, bool* name2, Button* name3, bool isActive);

    /* 연구 상태에서 [상세 설명] 버튼 ENTER, EXIT */
    void inResearch_ActiveInResearchChoiceImg(Transform* menuTr, bool isActive);
    /* 연구 상태에서 [상세 설명] 버튼 CLICK */
    void inResearch_ActiveDetailImg(UIBase* name, bool* name2, bool isActive);

    /* 상세 설명 상태에서 [돌아가기] 버튼 ENTER */
    void inDetailDes_ActiveGoBackImg(bool* name, bool isActive);
    /* 상세 설명 상태에서 [돌아가기] 버튼 CLICK */
    void inResearch_ReturnToResearchScene(bool* name, UIBase* name2, bool isActive);
    /* 상세 설명 상태에서 [돌아가기] 버튼 EXIT */
    void inDetailDes_ReturnToResearch(bool isActive);

    /* 메뉴 상태에서 [돌아가기] 버튼 ENTERT, EXIT */
    void inMenu_ActiveChoiceImg_GoBack(bool isActive);
    /* 메뉴 상태에서 [돌아가기] 버튼 CLICK */
    void inMenu_ReturnToGameScene(bool* name, bool isActive);

    /* 설정 여기다가 추가하세요 */
    /* 메뉴 상태에서 [설정] 버튼 ENTERT, EXIT */
    /* 메뉴 상태에서 [설정] 버튼 CLICK */

    /* 메뉴 상태에서 [저장 후 나가기] 버튼 ENTER, EXIT */
    void inMenu_AcitveChoiceImg_SaveAndExit(bool isActive);
    /* 메뉴 상태에서 [저장 후 나가기] 버튼 CLICK */
    void inMenu_AcitveRellayEnd(bool* name, bool isAcitve);

    /* 정말로 종료하시겠습니까? 상태에서 [취소] 버튼 ENTERT, EXIT */
    void inReallyEnd_Active_CancleImg(bool* name, bool isActive);
    /* 정말로 종료하시겠습니까? 상태에서 [취소] 버튼 CLICK */
    void inReallyEnd_Return_To_MenuState(bool* name, bool isAcitve);

    /* 정말로 종료하시겠습니까? 상태에서 [확인] 버튼 ENTERT, EXIT */
    void inReallyEnd_Active_CheckImg(bool* name, bool isActive);
    /* 정말로 종료하시겠습니까? 상태에서 [확인] 버튼 CLICK */
    void inReallyEnd_Return_To_TilteScene(bool* isQuit);

    //민재콩//
    UIBase* enemyWaveSkip;
    UIBase* enemyWaveSkipClick;
    Button* enemyWaveSkipButton;
    
    /* 민재 Enemy Wave Skip ENTER ,EXIT */
    void EnemyWaveSkip();
    void EnemyWaveSkipExit();
    
    EnemyManager* enemyManager;
    void SetEnemyManager(EnemyManager* enemymanager) { enemyManager = enemymanager; }
    
    /* 민재 Enemy Wave Skip CLICK*/
    void EnemyWaveSkipClick();
};