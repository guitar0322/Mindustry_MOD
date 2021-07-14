#include "stdafx.h"
#include "EditableText.h"

EditableText::EditableText()
{
	editText = new EditText();
	AddComponent(editText);
	editText->Init();
}

EditableText::~EditableText()
{
}
