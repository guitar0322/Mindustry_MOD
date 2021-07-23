#pragma once
#include "Component.h"
#include "TileInfo.h"
#include "PropInfo.h"
#include "GameInfo.h"

class ResourceManager;
class Transport;

class Production :
    public Component
{
private:
    RESOURCE _targetResource;
    Transport* _linkTransport[8];
    ResourceManager* _resourceManager;
    float _distributionTime;
    float _productTime;
    int _resourceTileNum;
    int _resourceAmount;
    int _transportIdx;
public:
    virtual void Init();
    virtual void Update();

    void LinkResourceManager(ResourceManager* resourceManager) { _resourceManager = resourceManager; }
    void SetTargetResource(RESOURCE resource);
    void Link(int tileX, int tileY, Transport* transport);
};

