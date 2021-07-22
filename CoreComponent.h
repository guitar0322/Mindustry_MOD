#pragma once
#include "Component.h"
class ResourceManager;
class GameInfo;

class CoreComponent :
    public Component
{
private:
    ResourceManager* _resourceManager;
    GameInfo* _gameInfo;
public:

    virtual void Init();
    virtual void OnTriggerEnter(GameObject* gameObject);
    void LinkResourceManager(ResourceManager* resourceManager) { _resourceManager = resourceManager; }
    void LinkGameInfo(GameInfo* gameInfo) { _gameInfo = gameInfo; }
};

