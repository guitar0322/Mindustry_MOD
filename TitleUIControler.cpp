#include "stdafx.h"
#include "TitleUIControler.h"


void TitleUIControler::ActiveChoiceImg(Transform* menuTr, bool isActive)
{
	choiceImg->transform->SetPosition(menuTr->GetX() - 49, menuTr->GetY());
	choiceImg->SetActive(isActive);
}

void TitleUIControler::ActiveChoiceImg2(Transform* menuTr, bool isActive)
{
	choiceImg2->transform->SetPosition(menuTr->GetX() - 113, menuTr->GetY());
	choiceImg2->SetActive(isActive);
}

void TitleUIControler::ActiveGoBackImg(bool isActive)
{
	goBackChoiceImg->SetActive(isActive);
}


void TitleUIControler::SetActiveCallback(vector<GameObject*> gameObject, bool* name, bool isActive)
{
	*name = isActive;

	for (int i = 0; i < gameObject.size(); i++)
	{
		gameObject[i]->SetActive(isActive);
	}
}

void TitleUIControler::SetActiveCallback2(vector<GameObject*> gameObject, bool* name, bool* name2, bool isActive)
{
	*name = isActive;
	*name2 = isActive;

	for (int i = 0; i < gameObject.size(); i++)
	{
		gameObject[i]->SetActive(isActive);
	}
}

void TitleUIControler::SetActiveCallback3(vector<GameObject*> gameObject, bool isActive)
{
	for (int i = 0; i < gameObject.size(); i++)
	{
		gameObject[i]->SetActive(isActive);
	}
}

void TitleUIControler::SetActiveCallback4(vector<GameObject*> gameObject, bool* name, bool* name2, bool* name3, bool isActive)
{
	*name = isActive;
	*name2 = isActive;
	*name3 = isActive;

	for (int i = 0; i < gameObject.size(); i++)
	{
		gameObject[i]->SetActive(isActive);
	}
}

void TitleUIControler::ChangeScene(string SceneName) 
{
	SOUNDMANAGER->stop("mainbgm");
	SCENEMANAGER->LoadScene(SceneName);
}

void TitleUIControler::GameExit()
{
	PostQuitMessage(0);
}