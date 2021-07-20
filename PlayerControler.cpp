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

		//감속할 시간 변수 하나 생성 float
		//해당 변수에 elapseTie 더함
		//시간이 0.1f보다 커지면
		//0으로 다시 초기화하고
		//speed--해준다
		if (_speed < 0)
		{
			_speed = 0;
			_isSlow = false;
		}
	}
	/***************************************************************
	1. 타겟앵글에서 플레이어 앵글을 빼준다
	2. 결과가 음수일 경우 360을 더한다.
	3. 그 결과는 타겟앵글과 플레이어 앵글의 시계방향 각도차이
	4. 시계방향 각도차이가 180도 보다 작다면 시계방향으로 움직인다.
	5. 아니라면 반시계방향으로 움직인다.
	 ****************************************************************/

	switch (_dir)
	{
	case LEFT: // 각 위치의 움직이는 방향 거리
		transform->MoveX(-_speed * TIMEMANAGER->getElapsedTime()); // X 값을 설정한 스피드 * 시간 만큼 곱한것 각 위치 길이 값.
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

	if (KEYMANAGER->isStayKeyDown('A') && KEYMANAGER->isStayKeyDown('S')) // A와 S키를 누르면 왼쪽 아래 대각선으로 간다.
	{
		_isDiagonal = true;
		_targetAngle = 225.f;
		_dir = LEFT_DOWN;
	}
	if (KEYMANAGER->isStayKeyDown('A') && KEYMANAGER->isStayKeyDown('W')) // A와 W키를 누르면 왼쪽 위 대각선으로 간다.
	{
		_isDiagonal = true;
		_targetAngle = 315.f;
		_dir = LEFT_UP;
	}
	if (KEYMANAGER->isStayKeyDown('D') && KEYMANAGER->isStayKeyDown('S')) // D와 S키를 누르면 오른쪽 아래 대각선으로 간다.
	{
		_isDiagonal = true;
		_targetAngle = 135.f;
		_dir = RIGHT_DOWN;
	}
	if (KEYMANAGER->isStayKeyDown('D') && KEYMANAGER->isStayKeyDown('W')) // D와 S키를 누르면 오른쪽 위 대각선으로 간다.
	{
		_isDiagonal = true;
		_targetAngle = 45.f;
		_dir = RIGHT_UP;
	}

	if (KEYMANAGER->isOnceKeyUp('W') || KEYMANAGER->isOnceKeyUp('S')) // 만약에 W또는 S키를 떼면?
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
	if (KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D')) // 만약에 A또는 D 키를 떼면?
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
			_targetAngle = 270.f; //왼쪽 거리 잡기
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
			_targetAngle = 90.f; // 오른쪽 거리 잡기
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
			_targetAngle = 0.f; //위쪽 거리 잡기
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
			_targetAngle = 180.f; //아래쪽 거리 잡기
			_dir = DOWN;
		}
	}
	PlayerDirection();
	if (KEYMANAGER->isStayKeyDown('A')) // A키를 누르면
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
			if (_isLeft == false) // 만약에 왼쪽이 발동 안할 경우
			{
				_weaponRTrackRadius = 9.41f;
				_projectileManager->FireProjectile(transform->GetChild(0)->GetX(), transform->GetChild(0)->GetY(),
					transform->GetChild(0)->GetAngle() + 2, PROJECTILE_TYPE::PLAYER);
			}
			else // 나머지 값
			{
				_weaponLTrackRadius = 9.41f;
				_projectileManager->FireProjectile(transform->GetChild(1)->GetX(), transform->GetChild(1)->GetY(),
					transform->GetChild(1)->GetAngle() - 2, PROJECTILE_TYPE::PLAYER);
			}
			_isLeft = !_isLeft; // 반복되게 하기
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
			//포신 보정 해주고
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
	1. 포신의 SetPotsition(플레이어 X + cosf(ConvertAngleAPI(transform->GetAngle())) * 포신궤도의 반지름,
		Y - sinf(각도) * 포신궤도의 반지름)
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
