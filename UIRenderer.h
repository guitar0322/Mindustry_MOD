#pragma once
#include "Component.h"
class UIRenderer :
    public Component
{
private:
    ID2D1Bitmap* _targetBitmap;
    float _frameWidth;
    float _frameHeight;
    float _alpha;
    int _curFrameX;
    int _curFrameY;
    Rect _rc;
public:
    UIRenderer();
    ~UIRenderer();
    virtual void Init(string clipName);
    virtual void Update();
    virtual void Render();
    void SetAlpha(float alpha) { _alpha = alpha; }
    float GetFrameWidth() const { return _frameWidth; }
    float GetFrameHeight() const { return _frameHeight; }
    float GetAlpha() const { return _alpha; }
    Rect GetRc() const { return _rc; }
};

