#pragma once
#include "Component.h"
#include <functional>
class UIRenderer;

using namespace std;

/***********************************************************
* UI Framework UIMouseEvent
* 마우스 동작에 따른 UI 이벤트 동작 클래스
* by 홍대영
* up to date : 21-07-10
* # Property @ Function
* # std::function<void()> Event : 이벤트 콜백함수 포인터 자료형
* # bool _enterMouse : 마우스가 UI 내부에 들어왔는지 여부
* # Event OnMouseEnter : 마우스가 UI에 진입했을 때 이벤트 콜백
* # Event OnMouseExit : 마우스가 UI를 빠져나갔을 때 이벤트 콜백
* # Event OnClick : 마우스가 UI를 클릭했을 때 이벤트 콜백
* @ RegistCallback : void반환 형을 가진 함수를 이벤트 콜백으로 등록
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

