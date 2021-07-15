#include "stdafx.h"
#include "PlayerControler.h"
#include "PlayerScene.h"
#include "ProjectileManager.h"

void PlayerControler::Init()
{
	_speed = 160.f;
	_armRecoverySpeed = 10;
	_targetAngle = 0.f;
	_breakTime = 0.f;
	_angleSpeed = 60.f;
	_isLeft = false;
	_shootLeft = false;
	_shootRight = false;
	_isSlow = false;
	_isDiagonal = false;
	_isGathering = false;
	_dir = IDLE;
}

void PlayerControler::Update()
{

	if (_isSlow == true)
	{
		_breakTime = 60.f;
		_speed -= _breakTime * TIMEMANAGER->getElapsedTime();
		
		//������ �ð� ���� �ϳ� ���� float
		//�ش� ������ elapseTie ����
		//�ð��� 0.1f���� Ŀ����
		//0���� �ٽ� �ʱ�ȭ�ϰ�
		//speed--���ش�
		if (_speed < 0)
		{
			_speed = 0;
			_isSlow = false;
		}
	}
	//�÷��̾� ȸ�� ����
	//�ޱ��� ������� �÷����� ���ϴ¹��
	//����ޱ� - ��ǥ�ޱ��� 180���� ũ�� �ٿ��ش�
	//�ޱ��� ������ �Ǹ� 360 - �������밪 ���� �ٲ��ش�
	//�ޱ��� 360���� Ŀ���� 0 + ���°����� �ٲ��ش�.

	switch (_dir)
	{
	case LEFT: // �� ��ġ�� �����̴� ���� �Ÿ�
		transform->MoveX(-_speed * TIMEMANAGER->getElapsedTime()); // X ���� ������ ���ǵ� * �ð� ��ŭ ���Ѱ� �� ��ġ ���� ��.
		break;
	case RIGHT:
		transform->MoveX(_speed * TIMEMANAGER->getElapsedTime());
		break;
	case UP:
		transform->MoveY(-_speed * TIMEMANAGER->getElapsedTime());
		break;
	case DOWN:
		transform->MoveY(_speed * TIMEMANAGER->getElapsedTime());
		break;
	case LEFT_UP:
		transform->Move(-_speed * TIMEMANAGER->getElapsedTime(), -_speed * TIMEMANAGER->getElapsedTime());
		break;
	case LEFT_DOWN:
		transform->Move(-_speed * TIMEMANAGER->getElapsedTime(), _speed * TIMEMANAGER->getElapsedTime());
		break;
	case RIGHT_UP:
		transform->Move(_speed * TIMEMANAGER->getElapsedTime(), -_speed * TIMEMANAGER->getElapsedTime());
		break;
	case RIGHT_DOWN:
		transform->Move(_speed * TIMEMANAGER->getElapsedTime(), _speed * TIMEMANAGER->getElapsedTime());
		break;
	case IDLE:
		break;
	}

	if (KEYMANAGER->isStayKeyDown('A') && KEYMANAGER->isStayKeyDown('S')) // A�� SŰ�� ������ ���� �Ʒ� �밢������ ����.
	{
		_isDiagonal = true;
		_targetAngle = 225.f;
		_dir = LEFT_DOWN;
	}
	if (KEYMANAGER->isStayKeyDown('A')&& KEYMANAGER->isStayKeyDown('W')) // A�� WŰ�� ������ ���� �� �밢������ ����.
	{
		_isDiagonal = true;
		_targetAngle = 315.f;
		_dir = LEFT_UP;
	}
	if (KEYMANAGER->isStayKeyDown('D')&& KEYMANAGER->isStayKeyDown('S')) // D�� SŰ�� ������ ������ �Ʒ� �밢������ ����.
	{
		_isDiagonal = true;
		_targetAngle = 135.f;
		_dir = RIGHT_DOWN;
	}
	if (KEYMANAGER->isStayKeyDown('D') && KEYMANAGER->isStayKeyDown('W')) // D�� SŰ�� ������ ������ �� �밢������ ����.
	{
		_isDiagonal = true;
		_targetAngle = 45.f;
		_dir = RIGHT_UP;
	}


	if (KEYMANAGER->isOnceKeyUp('W') || KEYMANAGER->isOnceKeyUp('S')) // ���࿡ W�Ǵ� SŰ�� ����?
	{
		_isSlow = true;
		if(KEYMANAGER->isStayKeyDown('A'))
		{
			_isDiagonal = false;
			_dir = LEFT;
			_targetAngle = 270;
		}
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			_isDiagonal = false;
			_dir = RIGHT;
			_targetAngle = 90.0f;
		}
	}
	if (KEYMANAGER->isOnceKeyUp('A')||KEYMANAGER->isOnceKeyUp('D')) // ���࿡ A�Ǵ� D Ű�� ����?
	{
		_isSlow = true;
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			_isDiagonal = false;
			_targetAngle = 0.f;
			_dir = UP;
		}
		if (KEYMANAGER->isStayKeyDown('S'))
		{
			_isDiagonal = false;
			_targetAngle = 180.f;
			_dir = DOWN;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			_dir = UP;
			_targetAngle = 0.f;
		}
		else if (KEYMANAGER->isStayKeyDown('S'))
		{
			_targetAngle = 225.f;
			_dir = DOWN;
		}
		else
		{
			_targetAngle = 270.f; //���� �Ÿ� ���
			_dir = LEFT;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			_targetAngle = 45.f;
			_dir = RIGHT_UP;
		}
		else if (KEYMANAGER->isStayKeyDown('S'))
		{
			_targetAngle = 135.f;
			_dir = RIGHT_DOWN;
		}
		else
		{
			_targetAngle = 90.f; // ������ �Ÿ� ���
			_dir = RIGHT;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			_targetAngle = 315.f;
			_dir = LEFT_UP;
		}
		else if (KEYMANAGER->isStayKeyDown('D'))
		{
			_targetAngle = 45.f;
			_dir = RIGHT_UP;
		}
		else
		{
			_targetAngle = 0.f; //���� �Ÿ� ���
			_dir = UP;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			_targetAngle = 225.f;
			_dir = LEFT_DOWN;
		}
		else if (KEYMANAGER->isStayKeyDown('D'))
		{
			_targetAngle = 135.f;
			_dir = RIGHT_DOWN;
		}
		else
		{
			_targetAngle = 180.f; //�Ʒ��� �Ÿ� ���
			_dir = DOWN;
		}
	}


	if (KEYMANAGER->isStayKeyDown('A')) // AŰ�� ������
	{
	
		_speed = 160.0f;
		/*if (_speed > 300.0f)
		{
			_speed = 300.0f;
		}*/
		float deltaAngle = transform->GetAngle() - _targetAngle; //��Ÿ�ޱ��� �� �ޱ�(������ �ޱ�)�� Ÿ�پޱ�(��ǥ �ޱ�) ���� �� ��
		if (deltaAngle > 180) //���࿡ ��Ÿ �ޱ��� 180�� �̻��̶��?
		{
			if(transform->GetAngle() != _targetAngle) // ���� �� �ޱ��� Ÿ�� �ޱ۰� ���� �ʴٸ�?
				transform->Rotate(2.f); // �� 2��ŭ �ð�������� ���ư���.(���̳ʽ��̹Ƿ� ������(�ݽð�)���� ����)
			if (transform->GetAngle() > _targetAngle) //���࿡ �� �ޱ��� Ÿ�� �ޱ۰����� ũ�ٸ�?
				transform->SetAngle(_targetAngle); // Ÿ�پޱ۰����� ����(���̻� ������ ���� �Ұ�)
		}
		else // ������(��Ÿ �ޱ��� 180���� �۴ٸ�?)
		{
			if (transform->GetAngle() != _targetAngle) // �� ���� ���� Ÿ�� �ޱ۰��� ���� ������? 
				transform->Rotate(-2.f); // �� 2��ŭ �ð� �ݴ�������� ���ư���.

			if (transform->GetAngle() < _targetAngle) //�� �ޱ��� ��ǥ �ޱۺ��� ���� ������?
				transform->SetAngle(_targetAngle);// Ÿ�� �ޱ۰� ��ŭ ����(���̻� ������ X)
		}
	}

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_speed = 160.0f;

		/*_speed += 3.0f;
		if (_speed > 300.0f)
		{
			_speed = 300.0f;
		}*/
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
	}


	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_speed = 160.0f;

		//_speed += 3.0f;
		//if (_speed > 300.0f)
		//{
		//	_speed = 300.0f;
		//}
		float deltaAngle = transform->GetAngle() - _targetAngle;
		if (deltaAngle > 360)
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
	}

	if (KEYMANAGER->isStayKeyDown('S'))
	{
		_speed = 160.0f;

	/*	_speed += 3.0f;
		if (_speed > 300.0f)
		{
			_speed = 300.0f;
		}*/
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
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		float worldX = ScreenToWorld(_ptMouse).x;
		float worldY = ScreenToWorld(_ptMouse).y;
		_targetAngle = ConvertAngleD2D(GetAngle(transform->position.x, transform->position.y, worldX, worldY));
		float deltaAngle = transform->GetAngle() - _targetAngle;

		if (deltaAngle > 180 )
		{
			if (transform->GetAngle() != _targetAngle)
			{
				transform->Rotate(2.0f);
			}

		}
		else
		{
			if (transform->GetAngle() != _targetAngle)
			{
				transform->Rotate(-2.0f);
			}
		}

		//�÷��̾� ��ġ, ���콺 ��ġ GetAngle�� ���� ���ϱ�
		//targetAngle�� ������ ���� Angle�� �ٲ��
		//�� targetAngle�� �÷��̾ ȸ���ؾߵȴ�
		//�׸��� targetAngle�� �÷��̾� ���� angle���� ��������
		//�� �� �Ѿ��� �߻��Ѵ�.
		/*GetAngle(x1, y1, x2, y2)*/
	}


	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		
		if (_isLeft == false) // ���࿡ ������ �ߵ� ���� ���
		{
				_projectileManager->FireProjectile(transform->GetX()+10, transform->GetY(),
					Math::ToRadian(transform->GetAngle()+45), PROJECTILE_TYPE::PLAYER);
		}
		else // ������ ��
		{
			_projectileManager->FireProjectile(transform->GetX()-10, transform->GetY(),
				Math::ToRadian(transform->GetAngle()+45), PROJECTILE_TYPE::PLAYER);
		}
		_isLeft = !_isLeft; // �ݺ��ǰ� �ϱ�

	}
}


