#include "stdafx.h"
#include "UIMouseEvent.h"

void UIMouseEvent::Init()
{
	uiRenderer = gameObject->GetComponent<UIRenderer>();
	if (uiRenderer == nullptr)
	{
		uiRenderer = new UIRenderer();
		gameObject->AddComponent(uiRenderer);
	}
	_enterMouse = false;
}

void UIMouseEvent::Update()
{
	if (Vector2InRect(&uiRenderer->GetRc(), &_ptMouse))
	{
		if (_enterMouse == false)
		{
			_enterMouse = true;
			if(OnMouseEnter != NULL)
				OnMouseEnter();
		}
	}
	else
	{
		if (_enterMouse == true)
		{
			_enterMouse = false;
			if(OnMouseExit != NULL)
				OnMouseExit();
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		if (Vector2InRect(&uiRenderer->GetRc(), &_ptMouse))
		{
			if(OnClick != NULL)
				OnClick();
		}
	}
}

void UIMouseEvent::Render()
{
}

void UIMouseEvent::RegistCallback(Event function, EVENT event)
{
	switch (event) {
	case ENTER:
		OnMouseEnter = std::move(function);
		break;
	case EXIT:
		OnMouseExit = std::move(function);
		break;
	case CLICK:
		OnClick = std::move(function);
		break;
	}
}
