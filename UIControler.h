#pragma once
#include "PropFactory.h"
#include <map>
#include <queue>

using namespace std;
#define CATEGORY_NUM 4
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
    UIBase* goBackIdleImg;
    UIBase* goBackChoiceImg;
    UIBase* coreDBIdleImg;
    UIBase* coreDBChoiceImg;
    void inResearch_ActiveChoiceImg(Transform* menuTr, bool isActive);
    void inResearch_ActiveGoBackImg(bool isActive);
    void inResearch_ReturnToGameScene(bool* name, bool isActive);
    void inResearch_ActiveCoreDBImg(bool isActive);
    // �ھ� DB ȭ�� ������ �� �� ������ ��������ֱ�
    void inResearch_ReturnToCoreDBScene(bool* name, bool isActive);
    // �׽�Ʈ��
    void inResearch_ActiveChoiceImgWithBasicDes(Transform* menuTr, UIBase* name, bool isActive);
};