#pragma once
#include "Scene.h"
#define LOADINGMAX 80

/* SHUNG 21.07.12 */

class IntroScene : public Scene
{

private:

public:
    
    IntroScene();
    ~IntroScene();

    ImageObject introImg;
    int currentCount;

    virtual HRESULT Init();
    virtual void Update();
    virtual void Render();
    virtual void Release();
};

static DWORD CALLBACK threadFunction(LPVOID lpParameter);