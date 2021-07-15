#include "stdafx.h"
#include "UIMouseEvent.h"

void UIMouseEvent::Init()
{
	focusable = false;
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
	//마우스가 UI에 진입했을때
	if (Vector2InRect(&uiRenderer->GetRc(), &_ptMouse))
	{
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			if (OnClick != NULL)
				OnClick();
			if(focusable == true)
				UIMANAGER->SetFocusUI((UIBase*)gameObject);
		}
		if (_enterMouse == false)
		{
			_enterMouse = true;
			if(OnMouseEnter != NULL)
				OnMouseEnter();
		}
	}
	//마우스가 UI를 빠져나갈때
	else
	{
		if (_enterMouse == true)
		{
			_enterMouse = false;
			if(OnMouseExit != NULL)
				OnMouseExit();
		}
	}
	//마우스가 UI를 클릭했을 때

}

/*******************************************************************
* RegistCallback(Event function, EVENT event)
* # EVENT : 이벤트 종류 Enum 자료형
* # Event function : 이벤트 콜백 함수
* 
* **자세한 사용방법은 SampleScene.cpp 참고
********************************************************************/
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
