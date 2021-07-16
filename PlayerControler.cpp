#include "stdafx.h"
#include "PlayerControler.h"
#include "PlayerScene.h"
#include "ProjectileManager.h"

void PlayerControler::Init()
{
	_speed = 250.f;
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
	SOUNDMANAGER->addSound("shoot", "sounds/shoot.ogg", false, false);

}

void PlayerControler::Update()
{

	if (_isSlow == true)
	{
		_breakTime = 180.f;
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
	/***************************************************************
	1. Ÿ�پޱۿ��� �÷��̾� �ޱ��� ���ش�
	2. ����� ������ ��� 360�� ���Ѵ�.
	3. �� ����� Ÿ�پޱ۰� �÷��̾� �ޱ��� �ð���� ��������
	4. �ð���� �������̰� 180�� ���� �۴ٸ� �ð�������� �����δ�.
	5. �ƴ϶�� �ݽð�������� �����δ�.
	 ****************************************************************/

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
		_speed = 250.f;
		PlayerDirection();
	}

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_speed = 250.f;
		PlayerDirection();
	}

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_speed = 250.f;
		PlayerDirection();
	}

	if (KEYMANAGER->isStayKeyDown('S'))
	{
		_speed = 250.f;
		PlayerDirection();
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		float worldX = ScreenToWorld(_ptMouse).x;
		float worldY = ScreenToWorld(_ptMouse).y;
		_targetAngle = ConvertAngleD2D(GetAngle(transform->position.x, transform->position.y, worldX, worldY));
		PlayerDirection();

		//�÷��̾� ��ġ, ���콺 ��ġ GetAngle�� ���� ���ϱ�
		//targetAngle�� ������ ���� Angle�� �ٲ��
		//�� targetAngle�� �÷��̾ ȸ���ؾߵȴ�
		//�׸��� targetAngle�� �÷��̾� ���� angle���� ��������
		//�� �� �Ѿ��� �߻��Ѵ�.
		/*GetAngle(x1, y1, x2, y2)*/
	}


	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		SOUNDMANAGER->play("shoot", 1.0f);
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

void PlayerControler::PlayerDirection()
{
	float deltaAngle = _targetAngle - transform->GetAngle();

	if (deltaAngle < 0) deltaAngle += 360; // ��Ÿ ������ 0���� ������ 360�� �����ش�.

	if (deltaAngle > 180) // ���࿡ ��Ÿ������ 180���� ũ�ٸ�?
	{
		if (transform->GetAngle() != _targetAngle)
			transform->Rotate(-2.f);
		if (Math::FloatEqual(_targetAngle, transform->GetAngle()))
			transform->SetAngle(_targetAngle);
	}
	else
	{
		if (transform->GetAngle() != _targetAngle)
			transform->Rotate(2.f);
		if (Math::FloatEqual(_targetAngle, transform->GetAngle()))
			transform->SetAngle(_targetAngle);
	}
}


