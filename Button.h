#pragma once
#include "UIBase.h"
class UIMouseEvent;
class Button :
    public UIBase
{
private:
    UIMouseEvent* _uiMouseEvent;
public:
    Button();
    ~Button();
};

