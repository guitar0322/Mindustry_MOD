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
	//���콺�� UI�� ����������
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
	//���콺�� UI�� ����������
	else
	{
		if (_enterMouse == true)
		{
			_enterMouse = false;
			if(OnMouseExit != NULL)
				OnMouseExit();
		}
	}
	//���콺�� UI�� Ŭ������ ��

}

/*******************************************************************
* RegistCallback(Event function, EVENT event)
* # EVENT : �̺�Ʈ ���� Enum �ڷ���
* # Event function : �̺�Ʈ �ݹ� �Լ�
* 
* **�ڼ��� ������� SampleScene.cpp ����
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
