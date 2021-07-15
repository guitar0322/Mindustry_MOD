#pragma once
#include "Component.h"
class EditText :
    public Component
{
private:
    UIRenderer* _uiRenderer;
    UIMouseEvent* _uiMouseEvent;
    wstring _text;
    wstring _hint;
    D2D1_COLOR_F _textColor;
    D2D1_COLOR_F _hintColor;
    int _fontSize;
public:
    virtual void Init();
    virtual void Update();
    virtual void Render();
    virtual void Release();
    void InputChar(WCHAR input);
    void SetHint(wstring hint);
    void SetFontSize(int size) { _fontSize = size; }
};

