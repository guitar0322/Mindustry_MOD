#pragma once
#include "UIBase.h"
class UIMouseEvent;
class Button :
    public UIBase
{
public:
    UIMouseEvent* uiMouseEvent;
    Button();
    ~Button();
};

