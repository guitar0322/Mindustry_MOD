#include "stdafx.h"
#include "Button.h"
#include "UIMouseEvent.h"
Button::Button()
{
	if (uiMouseEvent == nullptr)
	{
		uiMouseEvent = new UIMouseEvent();
		AddComponent(uiMouseEvent);
		uiMouseEvent->Init();
	}
}

Button::~Button()
{
}
