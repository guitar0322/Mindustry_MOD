#pragma once
#include "Component.h"
#include <functional>
class UIRenderer;

using namespace std;

/***********************************************************
* UI Framework UIMouseEvent
* ���콺 ���ۿ� ���� UI �̺�Ʈ ���� Ŭ����
* by ȫ�뿵
* up to date : 21-07-10
* # Property @ Function
* # std::function<void()> Event : �̺�Ʈ �ݹ��Լ� ������ �ڷ���
* # bool _enterMouse : ���콺�� UI ���ο� ���Դ��� ����
* # Event OnMouseEnter : ���콺�� UI�� �������� �� �̺�Ʈ �ݹ�
* # Event OnMouseExit : ���콺�� UI�� ���������� �� �̺�Ʈ �ݹ�
* # Event OnClick : ���콺�� UI�� Ŭ������ �� �̺�Ʈ �ݹ�
* @ RegistCallback : void��ȯ ���� ���� �Լ��� �̺�Ʈ �ݹ����� ���
************************************************************/
static enum EVENT {
	ENTER,
	EXIT,
    CLICK
};

class UIMouseEvent :
    public Component
{
private:

    typedef std::function<void()> Event;

    bool _enterMouse;
    Event OnMouseEnter;
    Event OnMouseExit;
    Event OnClick;
public:
    UIMouseEvent() {};
    ~UIMouseEvent() {};
    UIRenderer* uiRenderer;
    virtual void Init();
    virtual void Update();
    void RegistCallback(Event function, EVENT event);
};

