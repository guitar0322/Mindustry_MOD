#pragma once
#define BACKGROUND_WIDTH  1125
#define BACKGROUND_HEIGHT 875
#include "GameObject.h"

class TitleUIControler
{
public:
	ImageObject* choiceImg;
	ImageObject* choiceImg2;
	ImageObject* goBackIdleImg;
	ImageObject* goBackChoiceImg;

	void ActiveChoiceImg(Transform* menuTr, bool isActive);
	void ActiveChoiceImg2(Transform* menuTr, bool isActive);
	void ActiveGoBackImg(bool isActive);
	void SetActiveCallback(vector<GameObject*> gameObject, bool* name, bool isActive);
	void SetActiveCallback2(vector<GameObject*> gameObject, bool* name, bool* name2, bool isActive);
	void SetActiveCallback3(vector<GameObject*> gameObject, bool isActive);
	void SetActiveCallback4(vector<GameObject*> gameObject, bool* name, bool* name2, bool* name3, bool isActive);
	void ChangeScene(string SceneName);
	void GameExit();

};