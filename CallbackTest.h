#pragma once
#include "Component.h"
class CallbackTest :
    public Component
{
public:
    GameObject* testObject;
    void TestCallback();
};

