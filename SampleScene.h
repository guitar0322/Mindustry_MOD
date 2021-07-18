#pragma once
#include "Scene.h"
#include "AnimObject.h"
#include "Button.h"
class SampleScene :
    public Scene
{
private:
    float _time;
	GameObject* testParticleSystem;
    Button* testEditText;
    AnimObject testAnimObj;
    AnimObject testAnimObj2;
    float _stayTime;
    ImageObject background;
    ImageObject testNoClipObj;
    UIBase testUIObj;
    UIBase testNoClipUI;
    float _sceneChangeTime;
    int testInt;
    wstring debugWstring;
    Button testButton;
public:
    virtual HRESULT Init();
    virtual void Update();
    virtual void Render();
    virtual void Release();
};

