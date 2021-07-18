#pragma once
#include "GameObject.h"
class Camera;
class Cam :
    public GameObject
{
public:
    Camera* camera;
    Cam();
    ~Cam();

};

