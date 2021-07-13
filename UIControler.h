#pragma once
#include "Component.h"
class UIControler :
    public Component
{
private:
public:
    GameObject* categorySelect;
    GameObject* propSelect;
    GameObject* preSelectProp;

    vector<GameObject*>* wallIconV;
    vector<GameObject*>* drillIconV;
    vector<GameObject*>* turretIconV;
    vector<GameObject*>* railIconV;

    vector<GameObject*>* preIconV;
    virtual void Init();
    virtual void Update();
    void ClickCategoryIcon(GameObject* clickedButton, int category);
    void ClickPropIcon(GameObject* clickedButton);
};

