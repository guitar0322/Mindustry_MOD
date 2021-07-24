#pragma once
#include "Component.h"
#include "PropInfo.h"
#include <queue>
#define RESOURCE_NUM 3
class Prop;
class ResourceManager;

class ResDistribute :
    public Component
{
private:
    queue<int> _resQue;
    float _distributeTime;
    int _distributeDir;
    ResourceManager* _resourceManager;

public:
    ResDistribute();
    ~ResDistribute();

    virtual void Update();
    virtual void OnTriggerEnter(GameObject* gameObject);
    void AddResource(int resourceType);
    Prop* linkProp[4];
    void Link(PROPDIR dir, Prop* linkProp);
    void LinkResourceManager(ResourceManager* resourceManager) { _resourceManager = resourceManager; }
};

