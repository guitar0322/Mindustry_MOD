#pragma once
#include "GameObject.h"
#include "Camera.h"
class Cam :
    public GameObject
{
public:
    Camera* camera;
    Cam();
    ~Cam();

};

