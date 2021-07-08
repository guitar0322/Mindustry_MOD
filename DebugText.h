#pragma once
#include "Component.h"
class DebugText :
    public Component
{
private:
    int _deltaX;
    int _deltaY;
    int _term;
public:
    char debugStr[3][64];
    virtual void Init();
    virtual void Render();

    void SetDelta(int deltaX, int deltaY) { _deltaX = deltaX; _deltaY = deltaY; }
};

