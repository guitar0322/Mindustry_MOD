#pragma once
#include "Component.h"
class Text :
    public Component
{
public:
    Text();
    ~Text();
    DWORD fontStyle;
    DWORD characterSet;
    LOGFONT font;
    HFONT hFont, oFont;
    char fontPath[128];
    char fontName[128];
    char text[128];
    int fontSize;
    int fontWidth;
    virtual void Init();
    virtual void Init(const char* fontName, int fontSize, const char* text);
    virtual void Update();
    virtual void Render();
};

