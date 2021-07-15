#pragma once
#include "PropFactory.h"
#include <unordered_map>

using namespace std;
#define CATEGORY_NUM 4
class UIControler
{
private:
    int _selectCategoryIdx;
    int _selectPropIdx;
    vector<string> _clipArr[CATEGORY_NUM];
    unordered_map<int, ImageObject> _previewMap;
    unordered_map<int, ImageObject>::iterator _previewMapIter;
    PropFactory* _propFactory;
public:
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

    /* SHUNG 210715 */
    UIBase* choiceImg;
    void ActiveChoiceImg(Transform* menuTr, bool isActive);
};

