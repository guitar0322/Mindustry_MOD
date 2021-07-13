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
	//�÷��̾� ȸ�� ����
	//�ޱ��� ������� �÷����� ���ϴ¹��
	//����ޱ� - ��ǥ�ޱ��� 180���� ũ�� �ٿ��ش�
	//�ޱ��� ������ �Ǹ� 360 - �������밪 ���� �ٲ��ش�
	//�ޱ��� 360���� Ŀ���� 0 + ���°����� �ٲ��ش�.
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		if (KEYMANAGER->isStayKeyDown('W'))
			_targetAngle = 315.f;
		if (KEYMANAGER->isOnceKeyUp('W')||KEYMANAGER->isOnceKeyUp('S'))
		{

		}
		else if (KEYMANAGER->isStayKeyDown('S'))
			_targetAngle = 225.f;
		else
			_targetAngle = 270.f;
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		if (KEYMANAGER->isStayKeyDown('W'))
			_targetAngle = 45.f;
		else if (KEYMANAGER->isStayKeyDown('S'))
			_targetAngle = 135.f;
		else
		_targetAngle = 90.f;
		
	}
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		if (KEYMANAGER->isStayKeyDown('A'))
			_targetAngle = 315.f;
		else if (KEYMANAGER->isStayKeyDown('D'))
			_targetAngle = 45.f;
		else
		_targetAngle = 0.f;
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		if (KEYMANAGER->isStayKeyDown('A'))
			_targetAngle = 225.f;
		else if (KEYMANAGER->isStayKeyDown('D'))
			_targetAngle = 135.f;
		else
		_targetAngle = 180.f;
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		float deltaAngle = transform->GetAngle() - _targetAngle;
		if (deltaAngle > 180)
		{
			if(transform->GetAngle() != _targetAngle)
				transform->Rotate(2.f);
			if (transform->GetAngle() > _targetAngle)
				transform->SetAngle(_targetAngle);
		}
		else
		{
			if (transform->GetAngle() != _targetAngle)
				transform->Rotate(-2.f);

			if (transform->GetAngle() < _targetAngle)
				transform->SetAngle(_targetAngle);
		}
		_dir = LEFT;
		transform->MoveX(-_speed * TIMEMANAGER->getElapsedTime());

	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		float deltaAngle = transform->GetAngle() - _targetAngle;
		if (deltaAngle < 180)
		{
			if (transform->GetAngle() != _targetAngle)
				transform->Rotate(2.f);
			if (transform->GetAngle() > _targetAngle)
				transform->SetAngle(_targetAngle);
		}
		else
		{
			if (transform->GetAngle() != _targetAngle)
				transform->Rotate(-2.f);
			if (transform->GetAngle() < _targetAngle)
				transform->SetAngle(_targetAngle);
		}
		_dir = RIGHT;
		transform->MoveX(_speed * TIMEMANAGER->getElapsedTime());

	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		float deltaAngle = transform->GetAngle() - _targetAngle;
		if (deltaAngle > 180)
		{
			if (transform->GetAngle() != _targetAngle)
				transform->Rotate(2.f);
			if (transform->GetAngle() > _targetAngle)
				transform->SetAngle(_targetAngle);
		}
		else
		{
			if (transform->GetAngle() != _targetAngle)
				transform->Rotate(-2.f);

			if (transform->GetAngle() < _targetAngle)
				transform->SetAngle(_targetAngle);
		}
		_dir = UP;
		transform->MoveY(-_speed * TIMEMANAGER->getElapsedTime());

	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		float deltaAngle = transform->GetAngle() - _targetAngle;
		if (deltaAngle < 180)
		{
			if (transform->GetAngle() != _targetAngle)
				transform->Rotate(2.f);
			if (transform->GetAngle() > _targetAngle)
				transform->SetAngle(_targetAngle);
		}
		else
		{
			if (transform->GetAngle() != _targetAngle)
				transform->Rotate(-2.f);
			if (transform->GetAngle() < _targetAngle)
				transform->SetAngle(_targetAngle);
		}
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
