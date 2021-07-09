#include "stdafx.h"
#include "CallbackTest.h"

void CallbackTest::TestCallback()
{
	testObject->SetActive(!testObject->isActive);
}
