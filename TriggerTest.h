#pragma once
#include "Component.h"
class TriggerTest :
    public Component
{
private:
    float _stayTime;
public:
    GameObject* testObject;
    virtual void Init();
    virtual void OnTriggerEnter(GameObject* gameObject);
    virtual void OnTriggerStay(GameObject* gameObject);
    virtual void OnTriggerExit(GameObject* gameObject);
};

