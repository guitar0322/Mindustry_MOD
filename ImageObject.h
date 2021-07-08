#pragma once
#include "GameObject.h"
class ImageObject :
    public GameObject
{
public:
    ImageObject();
    ~ImageObject();
    Renderer* renderer;

};

