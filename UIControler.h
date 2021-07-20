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

    // �ھ� DB ȭ�� ������ �� �� ������ ��������ֱ�
    void inResearch_ReturnToCoreDBScene(bool* name, bool isActive);

    /* �⺻ �̹��� ��ư Ŭ�� �� */
    void inResearch_ActiveChoiceImgWithBasicDes(Transform* menuTr, UIBase* name, Button* name2, bool* name3, bool isActive);
    void inResearch_inActiveChoiceImgWithBasicDes(Transform* menuTr, UIBase* name, bool* name2, Button* name3, bool isActive);

    /* �⺻ ���� �̹��� Ŭ�� ��*/
    void inResearch_inBasicDes(Transform* menuTr, UIBase* name, bool* name2, bool isActive);
    void inResearch_disableInBasicDes(Transform* menuTr, UIBase* name, bool* name2, Button* name3, bool isActive);

    /* �⺻ ���� [i] ��ư�� ���� �� */
    void inResearch_ActiveInResearchChoiceImg(Transform* menuTr, bool isActive);
    void inResearch_ActiveDetailImg(UIBase* name, bool* name2, bool isActive);

    /* UI �󼼺��� ���� ��� ������ [�ڷΰ���] ��ư ���� �Լ� */
    void inDetailDes_ActiveGoBackImg(bool isActive);
    void inDetailDes_ReturnToResearch(bool* name, bool isActive);
};