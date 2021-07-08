#include "stdafx.h"
#include "ZOrder.h"

void ZOrder::Init()
{
	_z = transform->GetY();
	_x = transform->GetX();
	ZORDER->AddZOrder(this);
}

void ZOrder::OnEnable()
{
	ZORDER->AddZOrder(this); //오브젝트가 켜질때 매니저에 추가
}

void ZOrder::OnDisable()
{
	ZORDER->EraseZOrder(this); //오브젝트가 꺼지면 매니저에서 제거
}

void ZOrder::MoveZ(float z)
{
	transform->MoveY(z);
	_z += z;
}

void ZOrder::Render()
{
	if (!KEYMANAGER->isToggleKey(VK_TAB))
	{
		//_rc = RectMakeCenter(transform->GetX(), _z, 5, 5);
		//Rectangle(BackBuffer, _rc);
	}
}