#pragma once
#include "Scene.h"
#include "AnimObject.h"
class SampleScene :
    public Scene
{
private:
    AnimObject testAnimObj;
    AnimObject testAnimObj2;
    float _stayTime;
    ImageObject background;
    UIBase testUIObj;
    float _sceneChangeTime;
    int testInt;
    wstring debugWstring;
public:
    virtual HRESULT Init();
    virtual void Update();
    virtual void Render();
    virtual void Release();
};

