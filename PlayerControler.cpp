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
	
	if (_shootRight == true) // �������� �ߵ��� ���
	{
		transform->GetChild(2)->MoveY(-_armRecoverySpeed * TIMEMANAGER->getElapsedTime());
		if (transform->GetChild(2)->GetY() < transform->GetY() - 4) // ���� ���� ���� ������ ���� �ö󰥶�
		{
			_shootRight = false; 
			transform->GetChild(2)->SetY(transform->GetY() - 4); // ������ ���߰� ���� ���·� �ǵ�����.
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
		if (_isLeft == false) // ���࿡ ������ �ߵ� ���� ���
		{
			_shootRight = true; // �������� �ߵ��Ѵ�.
			transform->GetChild(2)->MoveY(5); // ��ӵ� �ڽ��Լ� 2��(playerRight)�� Y�� 5��ŭ �����δ�.
		}
		else // ������ ��
		{
			_shootLeft = true; // ������ �ߵ��Ѵ�.
			transform->GetChild(1)->MoveY(5); // ��ӵ� �ڽ��Լ� 1��(playerLeft)�� Y�� 5��ŭ �����δ�.
		}
		_isLeft = !_isLeft; // �ݺ��ǰ� �ϱ�
	}
}
