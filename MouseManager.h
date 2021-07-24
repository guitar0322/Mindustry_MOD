#pragma once
#include "singletonBase.h"
class MouseManager : public singletonBase<MouseManager>
{
private:
	UIBase* _mouseCursor;
public:
	MouseManager();
	~MouseManager();

	HRESULT Init();
	void Update();
	void Render();
	void Release();

	UIBase* GetMouseCursor() const { return _mouseCursor; }
};

