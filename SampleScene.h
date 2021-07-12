#pragma once
#include "Scene.h"
#include "AnimObject.h"
class SampleScene :
    public Scene
{
private:

    ImageObject _background;
    ImageObject _logo;
    
    //AnimObject testAnimObj;
    //AnimObject testAnimObj2;
        
    //UIBase _playButtonImage;
    //UIBase _terrainButtonImage;
    //UIBase _playButtonImage;
    //UIBase _playButtonImage;

    float _sceneChangeTime;
public:
    virtual HRESULT Init();
    virtual void Update();
    virtual void Render();
    virtual void Release();
};

