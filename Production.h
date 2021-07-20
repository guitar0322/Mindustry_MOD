#pragma once
#include "Component.h"
#include "TileInfo.h"
#include "PropInfo.h"
#include "GameInfo.h"

class Production :
    public Component
{
private:
    RESOURCE _targetResource;
    LINK _linkInfo[8];
public:
    virtual void Init();
    virtual void Update();

    void SetTargetResource(RESOURCE resource) { _targetResource = resource; }
    void Link(int tileX, int tileY);
};

