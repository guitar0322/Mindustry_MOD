#pragma once
#include "PropFactory.h"
#include <map>
#include <queue>
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
public:
    PropFactory* propFactory;
    UIControler();
    ~UIControler();
    GameObject* categorySelect;
    GameObject* propSelect;
    ImageObject* propPreview;
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
    
    /* SHUNG 210715 */
    UIBase* choiceImg;
    UIBase* lockImg;
    UIBase* inResearchChoiceImg;
    UIBase* research_goBackIdleImg;
    UIBase* research_goBackChoiceImg;
    UIBase* coreDBIdleImg;
    UIBase* coreDBChoiceImg;
    UIBase* detailDes_GoBackIdleImg;
    UIBase* detailDes_GoBackChoiceImg;

    void inResearch_ActiveChoiceImg(Transform* menuTr, bool isActive);
    void inResearch_ActiveGoBackImg(bool isActive);
    void inResearch_ReturnToGameScene(bool* name, bool isActive);
    void inResearch_ActiveCoreDBImg(bool isActive);

    // 코어 DB 화면 구성할 때 불 값으로 연결시켜주기
    void inResearch_ReturnToCoreDBScene(bool* name, bool isActive);

    /* 기본 이미지 버튼 클릭 시 */
    void inResearch_ActiveChoiceImgWithBasicDes(Transform* menuTr, UIBase* name, Button* name2, bool* name3, bool isActive);
    void inResearch_inActiveChoiceImgWithBasicDes(Transform* menuTr, UIBase* name, bool* name2, Button* name3, bool isActive);

    /* 기본 설명 이미지 클릭 시*/
    void inResearch_inBasicDes(Transform* menuTr, UIBase* name, bool* name2, bool isActive);
    void inResearch_disableInBasicDes(Transform* menuTr, UIBase* name, bool* name2, Button* name3, bool isActive);

    /* 기본 설명 [i] 버튼을 누를 때 */
    void inResearch_ActiveInResearchChoiceImg(Transform* menuTr, bool isActive);
    void inResearch_ActiveDetailImg(UIBase* name, bool* name2, bool isActive);

    /* UI 상세보기 누를 경우 나오는 [뒤로가기] 버튼 전용 함수 */
    void inDetailDes_ActiveGoBackImg(bool isActive);
    void inDetailDes_ReturnToResearch(bool* name, bool isActive);
};