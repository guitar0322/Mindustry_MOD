#include "stdafx.h"
#include "PlayerControler.h"
#include "PlayerScene.h"
#include "ProjectileManager.h"
#include "PlayerLaser.h"
#include "EnemyInfo.h"

void PlayerControler::Init()
{
	_speed = 250.f;
	_armRecoverySpeed = 10;
	_targetAngle = 0.f;
	_breakTime = 0.f;
	_angleSpeed = 60.f;
	_hp = 100;

	_weaponLTrackRadius = DEFAULT_WEAPON_DISTANCE;
	_weaponRTrackRadius = DEFAULT_WEAPON_DISTANCE;
	_weaponLTrackAngle = DEFAULT_WEAPON_ANGLE;
	_weaponRTrackAngle = DEFAULT_WEAPON_ANGLE;

	_playerLaser = new PlayerLaser;
	_playerLaser->Init();

	_attackSpeed = 0;
	_isLeft = false;
	_shootLeft = false;
	_shootRight = false;
	_isSlow = false;
	_isDiagonal = false;
	_isGathering = false;
	_isDead = false;
	_dir = IDLE;
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
	if (KEYMANAGER->isStayKeyDown('A') && KEYMANAGER->isStayKeyDown('W')) // A�� WŰ�� ������ ���� �� �밢������ ����.
	{
		_isDiagonal = true;
		_targetAngle = 315.f;
		_dir = LEFT_UP;
	}
	if (KEYMANAGER->isStayKeyDown('D') && KEYMANAGER->isStayKeyDown('S')) // D�� SŰ�� ������ ������ �Ʒ� �밢������ ����.
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
		if (KEYMANAGER->isStayKeyDown('A'))
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
	if (KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D')) // ���࿡ A�Ǵ� D Ű�� ����?
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
	PlayerDirection();
	if (KEYMANAGER->isStayKeyDown('A')) // AŰ�� ������
	{
		_speed = 250.f;
	}

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_speed = 250.f;
	}

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_speed = 250.f;
	}

	if (KEYMANAGER->isStayKeyDown('S'))
	{
		_speed = 250.f;
	}

	if (_weaponLTrackRadius < DEFAULT_WEAPON_DISTANCE)
	{
		_weaponLTrackRadius += 3.f * TIMEMANAGER->getElapsedTime();
		if (_weaponLTrackRadius > DEFAULT_WEAPON_DISTANCE)
			_weaponLTrackRadius = DEFAULT_WEAPON_DISTANCE;
	}

	if (_weaponRTrackRadius < DEFAULT_WEAPON_DISTANCE)
	{
		_weaponRTrackRadius += 3.f * TIMEMANAGER->getElapsedTime();
		if (_weaponRTrackRadius > DEFAULT_WEAPON_DISTANCE)
			_weaponRTrackRadius = DEFAULT_WEAPON_DISTANCE;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		worldX = ScreenToWorld(_ptMouse).x;
		worldY = ScreenToWorld(_ptMouse).y;
		_targetAngle = ConvertAngleD2D(GetAngle(transform->position.x, transform->position.y, worldX, worldY));
	
		_attackSpeed += TIMEMANAGER->getElapsedTime();
	
		if (_attackSpeed >= 0.3f)
		{
			if (_isLeft == false) // ���࿡ ������ �ߵ� ���� ���
			{
				_weaponRTrackRadius = 9.41f;
				_projectileManager->FireProjectile(transform->GetChild(0)->GetX(), transform->GetChild(0)->GetY(),
					transform->GetChild(0)->GetAngle() + 2, PROJECTILE_TYPE::PLAYER);
			}
			else // ������ ��
			{
				_weaponLTrackRadius = 9.41f;
				_projectileManager->FireProjectile(transform->GetChild(1)->GetX(), transform->GetChild(1)->GetY(),
					transform->GetChild(1)->GetAngle() - 2, PROJECTILE_TYPE::PLAYER);
			}
			_isLeft = !_isLeft; // �ݺ��ǰ� �ϱ�
			_attackSpeed = 0;
		}
	}

	float laserStartX = (transform->GetX() + cosf(ConvertAngleAPI(transform->GetAngle())) * 18);
	float laserStartY = (transform->GetY() - sinf(ConvertAngleAPI(transform->GetAngle())) * 18);

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		worldX = ScreenToWorld(_ptMouse).x;
		worldY = ScreenToWorld(_ptMouse).y;
		
		_playerLaser->SetLaserEndPoint(worldX / 32, worldY / 32);
		_playerLaser->SetLaserStartPoint(worldX, worldY);
	
	
		_playerLaser->_collectLaserFirst->SetActive(true);
		_playerLaser->_collectLaserEnd->SetActive(true);
		_playerLaser->_collectLaser->SetActive(true);
		_playerLaser->_detectRc->SetActive(true);
	
	}
	_playerLaser->ShootLaser();
	_playerLaser->SetLaserStartPoint(laserStartX, laserStartY);
	if (KEYMANAGER->isOnceKeyUp(VK_RBUTTON))
	{
		_playerLaser->_collectLaserFirst->SetActive(false);
		_playerLaser->_collectLaserEnd->SetActive(false);
		_playerLaser->_collectLaser->SetActive(false);
		_playerLaser->_detectRc->SetActive(false);
	}
}

void PlayerControler::Render()
{
	transform->GetChild(0)->gameObject->Render();
	transform->GetChild(1)->gameObject->Render();

	_playerLaser->Render();
}

void PlayerControler::PlayerDirection()
{
	float deltaAngle = _targetAngle - transform->GetAngle();

	if (deltaAngle < 0) deltaAngle += 360;

	if (deltaAngle > 180)
	{
		if (transform->GetAngle() != _targetAngle)
		{
			transform->Rotate(-4.f);
		}
		if (Math::FloatEqual(_targetAngle, transform->GetAngle()))
		{
			transform->SetAngle(_targetAngle);
			//���� ���� ���ְ�
			transform->GetChild(0)->SetAngle(_targetAngle);
			transform->GetChild(1)->SetAngle(_targetAngle);
		}
	}
	else
	{
		if (transform->GetAngle() != _targetAngle)
			transform->Rotate(4.f);
		if (Math::FloatEqual(_targetAngle, transform->GetAngle()))
		{
			transform->SetAngle(_targetAngle);
			transform->GetChild(0)->SetAngle(_targetAngle);
			transform->GetChild(1)->SetAngle(_targetAngle);
		}

	}
	/*******************************************************
	1. ������ SetPotsition(�÷��̾� X + cosf(ConvertAngleAPI(transform->GetAngle())) * ���ű˵��� ������,
		Y - sinf(����) * ���ű˵��� ������)
	********************************************************/
	_weaponLTrackAngle = ConvertAngleD2D(acosf(cosf(ConvertAngleAPI(DEFAULT_WEAPON_ANGLE)) * DEFAULT_WEAPON_DISTANCE / _weaponLTrackRadius));
	_weaponRTrackAngle = ConvertAngleD2D(acosf(cosf(ConvertAngleAPI(DEFAULT_WEAPON_ANGLE)) * DEFAULT_WEAPON_DISTANCE / _weaponRTrackRadius));

	_weaponLdistanceAngle = ConvertAngleAPI(transform->GetAngle() - _weaponLTrackAngle);
	_weaponRdistanceAngle = ConvertAngleAPI(transform->GetAngle() + _weaponRTrackAngle);

	if (_weaponLdistanceAngle < 0) _weaponLdistanceAngle += 360;
	transform->GetChild(0)->SetPosition((transform->GetX() + cosf(_weaponLdistanceAngle) * _weaponLTrackRadius),
		transform->GetY() - sinf(_weaponLdistanceAngle) * _weaponLTrackRadius);

	if (_weaponRdistanceAngle > 360) _weaponLdistanceAngle -= 360;
	transform->GetChild(1)->SetPosition((transform->GetX() + cosf(_weaponRdistanceAngle) * _weaponRTrackRadius),
		transform->GetY() - sinf(_weaponRdistanceAngle) * _weaponRTrackRadius);
}

void PlayerControler::Hit(float damage)
{
	_hp -= damage;
	if (_hp < 0 && _isDead == false)
	{
		_isDead = true;
	}
}

void PlayerControler::Dead()
{
}
