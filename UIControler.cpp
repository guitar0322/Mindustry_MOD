#include "stdafx.h"
#include "UIControler.h"

void UIControler::Init()
{
}

void UIControler::Update()
{
}

void UIControler::ClickCategoryIcon(GameObject* clickedButton, int category)
{
	categorySelect->transform->SetPosition(clickedButton->transform->GetX(), clickedButton->transform->GetY());
	propSelect->SetActive(false);
	for (int i = 0; i < preIconV->size(); i++)
	{
		(*preIconV)[i]->SetActive(false);
	}
	switch (category)
	{
	case 0:
		preIconV = turretIconV;
		break;
	case 1:
		preIconV = drillIconV;
		break;
	case 2:
		preIconV = railIconV;
		break;
	case 3:
		preIconV = wallIconV;
		break;
	}
	for (int i = 0; i < preIconV->size(); i++)
	{
		(*preIconV)[i]->SetActive(true);
	}
}

void UIControler::ClickPropIcon(GameObject* clickedButton)
{
	if (preSelectProp == clickedButton && propSelect->isActive == true)
	{
		propSelect->SetActive(false);
	}
	else
	{
		propSelect->SetActive(true);
		propSelect->transform->SetPosition(clickedButton->transform->GetX(), clickedButton->transform->GetY());
	}
	preSelectProp = clickedButton;
}
