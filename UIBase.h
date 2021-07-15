#pragma once
#include "GameObject.h"
class UIBase :
    public GameObject
{
public:
    UIBase();
    ~UIBase();
    UIRenderer* uiRenderer;
    UIMouseEvent* uiMouseEvent;
    virtual void Init();
    virtual void Update();
    virtual void Render();
};

