#pragma once
#include "UIBase.h"
class EditableText :
    public UIBase
{
public:
    EditableText();
    ~EditableText();
    EditText* editText;
};

