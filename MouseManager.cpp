#include "stdafx.h"
#include "MouseManager.h"

MouseManager::MouseManager()
{
}

MouseManager::~MouseManager()
{
}

HRESULT MouseManager::Init()
{
    // 마우스 클립
    CLIPMANAGER->AddClip("cursor_cursor", "sprites/game/cursor/cursor.png", 64, 64);
    CLIPMANAGER->AddClip("cursor_drill", "sprites/game/cursor/drill.png", 64, 64);
    CLIPMANAGER->AddClip("cursor_hand", "sprites/game/cursor/hand.png", 64, 64);

    _mouseCursor = new UIBase();
    _mouseCursor->Init();
    _mouseCursor->uiMouseEvent->enable = false;
    _mouseCursor->uiRenderer->Init("cursor_cursor");

    return S_OK;
}

void MouseManager::Update()
{
    _mouseCursor->transform->SetPosition(_ptMouse);
}

void MouseManager::Render()
{
    _mouseCursor->Render();
}

void MouseManager::Release()
{
    NEW_SAFE_RELEASE(_mouseCursor);
    SAFE_DELETE(_mouseCursor);
}
