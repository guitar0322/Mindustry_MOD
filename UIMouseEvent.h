#pragma once
#include "Component.h"
#include <functional>
class UIRenderer;

using namespace std;

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
    void(*mouseEnterCallback)();
    Event OnMouseEnter;
    Event OnMouseExit;
    Event OnClick;
public:
    UIMouseEvent() {};
    ~UIMouseEvent() {};
    UIRenderer* uiRenderer;
    virtual void Init();
    virtual void Update();
    virtual void Render();
    void RegistCallback(Event function, EVENT event);
};

