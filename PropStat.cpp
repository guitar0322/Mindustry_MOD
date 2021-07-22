#include "stdafx.h"
#include "PropStat.h"

void PropStat::Init()
{
}

void PropStat::Hit(int damage)
{
	_hp -= damage;
	if (_hp <= 0)
	{
		Broken();
	}
}

void PropStat::Broken()
{
	gameObject->SetActive(false);

	for (int i = 0; i < gameObject->transform->GetChildCount(); i++)
	{
		gameObject->transform->GetChild(i)->gameObject->SetActive(false);
	}
}
