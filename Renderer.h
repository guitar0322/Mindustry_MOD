 #pragma once
#include "Component.h"
/**********************************
Framework Renderer Component For D2D
By 홍대영
Date 21-07-06
**********************************/
class Renderer :
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
    Renderer();
    ~Renderer();
    virtual void Init(string clipName);
    virtual void Render();
    virtual void Update();
    virtual void Release();
    virtual void OnEnable();
    virtual void OnDisable();

    void SetAlpha(float alpha) { _alpha = alpha;}//알파값 설정
    float GetAlpha() const { return _alpha; }
    int GetWidth() const { return _frameWidth; }
    int GetHeight() const { return _frameHeight; }
    Rect GetRc() { return _rc; }

    void ChangeTargetBitmap(ID2D1Bitmap* newBitmap, float frameWidth, float frameHeight);
    void ChangeTargetBitmap(ID2D1Bitmap* newBitmap, float frameWidth, float frameHeight, bool isInitFrame);
    void SetFrameX(int frameX) { _curFrameX = frameX; }
    void SetFrameY(int frameY) { _curFrameY = frameY; }
};

