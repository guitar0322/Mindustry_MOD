#include "stdafx.h"
#include "Button.h"
#include "UIMouseEvent.h"
Button::Button()
{
	uiMouseEvent = new UIMouseEvent();
	AddComponent(uiMouseEvent);
	uiMouseEvent->Init();
}

Button::~Button()
{
}
