#pragma once
#include "Component.h"
class Outline :
    public Component
{
private:
    COLORREF _lineColor;
    Renderer* renderer;
    int _lineWidth;
public:
    virtual void Init();
    virtual void Update();
    virtual void Render();

    void SetTargetObject(GameObject* gameObject);
    void SetColor(COLORREF color) { _lineColor = color; }
};

