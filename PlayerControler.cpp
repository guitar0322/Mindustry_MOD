#include "stdafx.h"
#include "PlayerControler.h"
#include "PlayerScene.h"
#include "ProjectileManager.h"

void PlayerControler::Init()
{
	_speed = 0.f;
	_armRecoverySpeed = 10;
	_targetAngle = 0.f;
	_breakTime = 0.f;
	_angleSpeed = 60.f;
	_isLeft = false;
	_shootLeft = false;
	_shootRight = false;
	_isSlow = false;
}

void PlayerControler::Update()
{
	if (_isSlow == true)
	{
		_breakTime += TIMEMANAGER->getElapsedTime();
		if (_breakTime > 0.1f)
		{
			_breakTime = 0.f;
			_speed-= 5.0f;
		}

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
	case LEFT:
		transform->MoveX(-_speed * TIMEMANAGER->getElapsedTime()); // X ���� ������ ���ǵ� * �ð� ��ŭ ���ϱ�
		break;
	case RIGHT:
		transform->MoveX(_speed * TIMEMANAGER->getElapsedTime()); // X ���� ������ ���ǵ� * �ð� ��ŭ ���ϱ�
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
		transform->Move(-_speed * TIMEMANAGER->getElapsedTime(), _speed*TIMEMANAGER->getElapsedTime());
		break;
	case RIGHT_UP:
		transform->Move(_speed*TIMEMANAGER->getElapsedTime(), -_speed * TIMEMANAGER->getElapsedTime());
		break;
	case RIGHT_DOWN:
		transform->Move(_speed*TIMEMANAGER->getElapsedTime(), _speed*TIMEMANAGER->getElapsedTime());
		break;
	}

	if (KEYMANAGER->isOnceKeyUp('W') || KEYMANAGER->isOnceKeyUp('S'))
	{
		_isSlow = true;
		if(KEYMANAGER->isStayKeyDown('A'))
		{
			_dir = LEFT;
			_targetAngle = 270.f;
		}
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			_dir = RIGHT;
			_targetAngle = 90.0f;
		}
	}
	if (KEYMANAGER->isOnceKeyUp('A')||KEYMANAGER->isOnceKeyUp('D'))
	{
		_isSlow = true;
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			_targetAngle = 0.f;
			_dir = UP;
		}
		if (KEYMANAGER->isStayKeyDown('S'))
		{
			_targetAngle = 180.f;
			_dir = DOWN;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		if (KEYMANAGER->isStayKeyDown('W'))
			{
			_targetAngle = 315.f;
			_dir = LEFT_UP;
			}
		else if (KEYMANAGER->isStayKeyDown('S'))
		{
			_targetAngle = 225.f;
			_dir = LEFT_DOWN;
		}
		else
		{
			_targetAngle = 270.f;
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
			_targetAngle = 90.f;
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
			_targetAngle = 0.f;
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
			_targetAngle = 180.f;
			_dir = DOWN;
		}
	}

	if (KEYMANAGER->isStayKeyDown('A')) // AŰ�� ������
	{
		_speed++;
		if (_speed > 200.0f)
		{
			_speed = 200.0f;
		}
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
			_dir = LEFT;
		}
	}

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_speed++;
		if (_speed > 200.0f)
		{
			_speed = 200.0f;
		}
		//���ǵ� bool���� �ֱ������� Ű �����µ��� ���ǵ带 ���������� �����̰��Ѵ�. �ٸ� ���� ���ǵ常 �����̰� �Ѵ�.
		//Ű�� ������ bool����  \true�� �ٲ۴�
		//update���� bool���� true�� speed�� ��´�
		//speed�� 0���ϰ� �Ǹ� speed�� 0���� �ٲٰ� bool���� false�� �Ѵ�
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
	}


	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_speed++;
		if (_speed > 200.0f)
		{
			_speed = 200.0f;
		}
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
	}

	if (KEYMANAGER->isStayKeyDown('S'))
	{
		_speed++;
		if (_speed > 200.0f)
		{
			_speed = 200.0f;
		}
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
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		float worldX = ScreenToWorld(_ptMouse).x;
		float worldY = ScreenToWorld(_ptMouse).y;
		_targetAngle = ConvertAngleD2D(GetAngle(transform->position.x, transform->position.y, worldX, worldY));
		float deltaAngle = transform->GetAngle() - _targetAngle;

		if (deltaAngle > 360 )
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
					Math::ToRadian(transform->GetAngle() + 90), PROJECTILE_TYPE::PLAYER);
		}
		else // ������ ��
		{
			_projectileManager->FireProjectile(transform->GetX()-10, transform->GetY(),
				Math::ToRadian(transform->GetAngle() + 90), PROJECTILE_TYPE::PLAYER);
		}
		_isLeft = !_isLeft; // �ݺ��ǰ� �ϱ�
	}
}


