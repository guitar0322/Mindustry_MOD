#pragma once
#include "PropFactory.h"
#include <map>
#include <queue>
#include "PropInfo.h"
#define CATEGORY_NUM 4

using namespace std;
class Button;

class UIControler
{
private:
    int _selectCategoryIdx;
    int _selectPropIdx;
    int _previewNum;
    bool _previewDir;
    Vector2 _worldStartPtMouse;
    vector<string> _clipArr[CATEGORY_NUM];
    vector<ImageObject> _previewV;
    PROPDIR _dir;
public:
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

    /* 시영 */
    /* 연구 */
    UIBase* choiceImg;
    UIBase* lockImg;
    UIBase* inResearchChoiceImg;
    UIBase* research_goBackIdleImg;
    UIBase* research_goBackChoiceImg;
    UIBase* coreDBIdleImg;
    UIBase* coreDBChoiceImg;
    UIBase* detailDes_GoBackIdleImg;
    UIBase* detailDes_GoBackChoiceImg;

    /* 메뉴 */
    UIBase* menu_GoBackIdleImg;            // 메뉴 [돌아가기] 기본 상태 이미지
    UIBase* menu_GoBackChoiceImg;          // 메뉴 [돌아가기] 선택 상태 이미지
    UIBase* menu_SettingIdleImg;           // 메뉴 [설정] 기본 상태 이미지
    UIBase* menu_SettingChoiceImg;         // 메뉴 [설정] 선택 상태 이미지
    UIBase* menu_SaveAndExitIdleImg;       // 메뉴 [저장 후 나가기] 기본 상태 이미지
    UIBase* menu_SaveAndExitChoiceImg;     // 메뉴 [저장 후 나가기] 선택 상태 이미지

    void inResearch_ActiveChoiceImg(Transform* menuTr, bool isActive);
    
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

    /* 메뉴 상태에서 [저장 후 나가기] 버튼 ENTER, EXIT */
    void inMenu_AcitveChoiceImg_SaveAndExit(bool isActive);
};