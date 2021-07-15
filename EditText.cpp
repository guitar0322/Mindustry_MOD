#include "stdafx.h"
#include "EditText.h"
void EditText::Init()
{
	_text = L"";
	_hint = L"input text.";
	_fontSize = 25;
	_uiRenderer = gameObject->GetComponent<UIRenderer>();
	_uiMouseEvent = gameObject->GetComponent<UIMouseEvent>();
	_uiMouseEvent->focusable = true;
}

void EditText::Update()
{
}

void EditText::Render()
{
	D2DRENDERER->RenderText(transform->GetX() - _uiRenderer->GetFrameWidth() / 2, transform->GetY(), _text, _fontSize);
}

void EditText::Release()
{
}

void EditText::InputChar(WCHAR input)
{
	WCHAR wInput[2];
	swprintf_s(wInput, L"%c", input);
	_text.append(wInput);
}

void EditText::SetHint(wstring hint)
{
}
