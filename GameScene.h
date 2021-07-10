#pragma once
#include "Scene.h"
class GameScene :
    public Scene
{
public:
    virtual HRESULT Init();
    virtual void Update();
    virtual void Render();
    virtual void Release();
};

