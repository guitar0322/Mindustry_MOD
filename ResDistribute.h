#pragma once
#include "Component.h"
#include "PropInfo.h"

#define RESOURCE_NUM 3
class Transport;

class ResDistribute :
    public Component
{
private:
    int _resourceNum[RESOURCE_NUM];
public:
    ResDistribute();
    ~ResDistribute();

    Transport* linkTransport[4];
    void Link(PROPDIR dir);
};

