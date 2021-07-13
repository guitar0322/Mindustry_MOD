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
	//���콺�� UI�� ����������
	if (Vector2InRect(&uiRenderer->GetRc(), &_ptMouse))
	{
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			if (OnClick != NULL)
				OnClick();
		}
		if (_enterMouse == false)
		{
			_enterMouse = true;
			if(OnMouseEnter != NULL)
				OnMouseEnter();
			//if (OnMouseEnterParam != NULL)
			//	OnMouseEnterParam(mouseEnterParam);
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
			//if (OnMouseExitParam != NULL)
			//	OnMouseExitParam(mouseExitParam);
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

//void UIMouseEvent::RegistParamCallback(EventParam function, void* param, EVENT event)
//{
//	switch (event) {
//	case ENTER:
//		OnMouseEnterParam = std::move(function);
//		mouseEnterParam = param;
//		break;
//	case EXIT:
//		OnMouseExitParam = std::move(function);
//		mouseExitParam = param;
//		break;
//	case CLICK:
//		OnClickParam = std::move(function);
//		clickParam = param;
//		break;
//	}
//}
