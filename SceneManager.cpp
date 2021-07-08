#include "stdafx.h"
SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

HRESULT SceneManager::Init()
{
    return S_OK;
}

void SceneManager::Update()
{
    _curScene->Update();
}

void SceneManager::Render()
{
    _curScene->Render();
}

void SceneManager::Release()
{
}

void SceneManager::AddScene(string sceneName, Scene* scene)
{
    sceneMap.insert(pair<string, Scene*>(sceneName, scene));
}

void SceneManager::LoadScene(string sceneName)
{
    if(_curScene != nullptr)
        _curScene->Release();
    sceneIter = sceneMap.find(sceneName);
    if (sceneIter != sceneMap.end()) {
        _curScene = sceneIter->second;
        _curScene->Init();
    }
}

Scene* SceneManager::GetScene(string sceneName)
{
    sceneIter = sceneMap.find(sceneName);
    if (sceneIter != sceneMap.end()) {
        return sceneIter->second;
    }
    return nullptr;
}

Scene* SceneManager::GetCurScene()
{
    return _curScene;
}
/************************************************
sceneName : 검사 대상 씬 이름
return int : sceneName의 인덱스 번호
************************************************/
int SceneManager::GetSceneIdx(string sceneName)
{
    int idx = 0;
    for (sceneIter = sceneMap.begin(); sceneIter != sceneMap.end(); sceneIter++)
    {
        if (sceneIter->first == sceneName)
        {
            return idx;
        }
        idx++;
    }
    return -1;
}

/************************************************
sceneName : 현재 씬인지 검사할 대상 씬 이름
return bool : 현재 씬이 sceneName과 같으면 true
************************************************/
bool SceneManager::IsCurScene(string sceneName)
{
    sceneIter = sceneMap.find(sceneName);
    if (sceneIter != sceneMap.end())
    {
		if (sceneIter->second == _curScene)
			return true;
    }
    return false;
}


/************************************************
return int : 현재 씬의 씬 인덱스를 반환
************************************************/
int SceneManager::GetCurSceneIdx()
{
    int idx = 0;
    for (sceneIter = sceneMap.begin(); sceneIter != sceneMap.end(); sceneIter++)
    {
        if (sceneIter->second == _curScene)
            return idx;
        idx++;
    }
    return -1;
}
