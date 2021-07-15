#include "stdafx.h"
#include "UIManager.h"
#include "EditText.h"
HRESULT UIManager::Init()
{
    return E_NOTIMPL;
}

void UIManager::Release()
{
}

void UIManager::OnKeyDown(WCHAR input)
{
    if (_focusUI == nullptr)
        return;

    if (_focusUI->GetComponent<EditText>() != nullptr)
    {
        _focusUI->GetComponent<EditText>()->InputChar(input);
    }
}

void UIManager::SetFocusUI(UIBase* focusUI)
{
    _focusUI = focusUI;
}
