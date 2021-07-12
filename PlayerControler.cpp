#include "stdafx.h"
#include "PlayerControler.h"
#include "PlayerScene.h"

void PlayerControler::Init()
{
	_speed = 100.f;
	_armRecoverySpeed = 10;
	_targetAngle = 0.f;
	_angleSpeed = 60.f;
	_isLeft = false;
	_shootLeft = false;
	_shootRight = false;
}

void PlayerControler::Update()
{
	
	if (_shootRight == true) // 오른쪽이 발동한 경우
	{
		transform->GetChild(2)->MoveY(-_armRecoverySpeed * TIMEMANAGER->getElapsedTime());
		if (transform->GetChild(2)->GetY() < transform->GetY() - 4) // 윗의 값이 현재 값보다 위에 올라갈때
		{
			_shootRight = false; 
			transform->GetChild(2)->SetY(transform->GetY() - 4); // 진행을 멈추고 원래 상태로 되돌린다.
		}
	}
	if (_shootLeft == true)
	{
		transform->GetChild(1)->MoveY(-_armRecoverySpeed * TIMEMANAGER->getElapsedTime());
		if (transform->GetChild(1)->GetY() < transform->GetY() - 4)
		{
			_shootLeft = false;
			transform->GetChild(1)->SetY(transform->GetY() - 4);
		}
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_dir = LEFT;
		transform->MoveX(-_speed * TIMEMANAGER->getElapsedTime());


	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_dir = RIGHT;
		transform->MoveX(_speed * TIMEMANAGER->getElapsedTime());

	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_dir = UP;
		transform->MoveY(-_speed * TIMEMANAGER->getElapsedTime());

	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		_dir = DOWN;
		transform->MoveY(_speed * TIMEMANAGER->getElapsedTime());

	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_isLeft == false) // 만약에 왼쪽이 발동 안할 경우
		{
			_shootRight = true; // 오른쪽이 발동한다.
			transform->GetChild(2)->MoveY(5); // 상속된 자식함수 2번(playerRight)의 Y값 5만큼 움직인다.
		}
		else // 나머지 값
		{
			_shootLeft = true; // 왼쪽이 발동한다.
			transform->GetChild(1)->MoveY(5); // 상속된 자식함수 1번(playerLeft)의 Y값 5만큼 움직인다.
		}
		_isLeft = !_isLeft; // 반복되게 하기
	}
}
