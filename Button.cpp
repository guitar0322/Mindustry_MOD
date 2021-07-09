#include "stdafx.h"
#include "Button.h"
#include "UIMouseEvent.h"
Button::Button()
{
	_uiMouseEvent = new UIMouseEvent();
	AddComponent(_uiMouseEvent);
	_uiMouseEvent->Init();
}

Button::~Button()
{
}
