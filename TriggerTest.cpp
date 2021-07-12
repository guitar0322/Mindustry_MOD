#include "stdafx.h"
#include "TriggerTest.h"

void TriggerTest::Init()
{
	_stayTime = 0;
}

void TriggerTest::OnTriggerEnter(GameObject* gameObject)
{
	if (testObject == nullptr)
		return;
	testObject->SetActive(true);
}

void TriggerTest::OnTriggerStay(GameObject* gameObject)
{
	if (testObject == nullptr)
		return;
	_stayTime += TIMEMANAGER->getElapsedTime();
	if (_stayTime >= 0.3f)
	{
		_stayTime = 0;
		//testObject->SetActive(!testObject->isActive);
	}
}

void TriggerTest::OnTriggerExit(GameObject* gameObject)
{
	if (testObject == nullptr)
		return;
	testObject->SetActive(false);
}
