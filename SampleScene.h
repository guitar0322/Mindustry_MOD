#pragma once
#include "Scene.h"
#include "AnimObject.h"
class SampleScene :
    public Scene
{
private:
    AnimObject testAnimObj;
    AnimObject testAnimObj2;
    ImageObject background;
    UIBase testUIObj;
    float _sceneChangeTime;
public:
    virtual HRESULT Init();
    virtual void Update();
    virtual void Render();
    virtual void Release();
};

