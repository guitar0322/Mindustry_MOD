#pragma once
#include "singletonBase.h"
#include "Scene.h"

class SceneManager : public singletonBase<SceneManager>
{
private:
	map<string, Scene*> sceneMap;
	map<string, Scene*>::iterator sceneIter;
	Scene* _curScene;
public:
	SceneManager();
	~SceneManager();
	virtual HRESULT Init();
	void Update();
	void Render();
	void Release();
	void AddScene(string sceneName, Scene* scene);
	void LoadScene(string sceneName);
	Scene* GetScene(string sceneName);
	Scene* GetCurScene();
	int GetSceneIdx(string sceneName);
	bool IsCurScene(string sceneName);
	int GetCurSceneIdx();
};

