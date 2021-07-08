#pragma once
#include "Scene.h"
class SampleScene2 :
    public Scene
{
private:
    ImageObject background;
public:
    virtual HRESULT Init();
    virtual void Update();
    virtual void Render();
    virtual void Release();
};

