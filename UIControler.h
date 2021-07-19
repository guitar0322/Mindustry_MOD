#pragma once
#include "PropFactory.h"
#include <map>
#include <queue>
#include "PropInfo.h"
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
    /* SHUNG 210715 */
    UIBase* choiceImg;
    UIBase* lockImg;
    void ActiveChoiceImg(Transform* menuTr, bool isActive);
};

