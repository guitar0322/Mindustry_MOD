#include "stdafx.h"
#include "DebugText.h"

void DebugText::Init()
{
	for (int i = 0; i < 3; i++) {
		ZeroMemory(debugStr[i], sizeof(debugStr[i]));
	}
	_deltaX = -30;
	_deltaY = -60;
	_term = 20;
}

void DebugText::Render()
{
	for (int i = 0; i < 3; i++) {
		//TextOut(BackBuffer, transform->GetX() + _deltaX, transform->GetY() + _deltaY - _term * i, debugStr[i], strlen(debugStr[i]));
	}
}
