#include "stdafx.h"
#include "PlayerControler.h"
#include "ProjectileManager.h"
#include "PlayerLaser.h"
#include "EnemyInfo.h"
#include "TileInfo.h"

void PlayerControler::Init()
{
	_accel = 100.f;
	_armRecoverySpeed = 10;
	_targetAngle = 0.f;
	_breakTime = 0.f;
	_respawnTime = 0.f;
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
	_isSlow = false;
	_isCollecting = false;
	_isDead = false;
	_isRespawn = false;
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

	MoveHandler();
	RespawnTime();

	if (!_isDead)
	{
		KeyHandle();
		if (_isCollecting == true)
		{
			_targetAngle = ConvertAngleD2D(GetAngle(transform->GetX(), transform->GetY(), _collectTile.x * TILESIZE + 16, _collectTile.y * TILESIZE + 16));
		}
		PlayerDirection();

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
			if (_isCollecting == false)
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

		float laserStartX = transform->GetX() + cosf(ConvertAngleAPI(transform->GetAngle())) * 18;
		float laserStartY = transform->GetY() - sinf(ConvertAngleAPI(transform->GetAngle())) * 18;
		_playerLaser->SetLaserStartPoint(laserStartX, laserStartY);

		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			if (_isCollecting == false)
			{
				_collectTile.x = worldX / TILESIZE;
				_collectTile.y = worldY / TILESIZE;
				_playerLaser->SetLaserEndPoint(_collectTile.x, _collectTile.y);
				_isCollecting = true;
				_playerLaser->_collectLaserFirst->SetActive(true);
				_playerLaser->_collectLaserEnd->SetActive(true);
				_playerLaser->_collectLaser->SetActive(true);
				_playerLaser->_detectRc->SetActive(true);
			}
		}
		if (KEYMANAGER->isOnceKeyUp(VK_RBUTTON))
		{
			_playerLaser->_collectLaserFirst->SetActive(false);
			_playerLaser->_collectLaserEnd->SetActive(false);
			_playerLaser->_collectLaser->SetActive(false);
			_playerLaser->_detectRc->SetActive(false);
			_isCollecting = false;
		}
		_playerLaser->Update();
		if (_playerLaser->GetLaserDistance() >= 400)
		{
			_playerLaser->OffLaser();
			_isCollecting = false;
		}
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
		if (Math::FloatEqual(_targetAngle, transform->GetAngle()) == false)
		{
			transform->Rotate(-4.f);
			if (_targetAngle > transform->GetAngle())
			{
				transform->SetAngle(_targetAngle);
				//포신 보정 해주고
				transform->GetChild(0)->SetAngle(_targetAngle);
				transform->GetChild(1)->SetAngle(_targetAngle);
			}
		}
	}
	else
	{
		if (Math::FloatEqual(_targetAngle, transform->GetAngle()) == false)
		{
			transform->Rotate(4.f);
			if (_targetAngle < transform->GetAngle())
			{
				transform->SetAngle(_targetAngle);
				transform->GetChild(0)->SetAngle(_targetAngle);
				transform->GetChild(1)->SetAngle(_targetAngle);
			}
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

void PlayerControler::KeyHandle()
{
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			_dir = LEFT_UP;
			_targetAngle = 315.f;
		}
		else if (KEYMANAGER->isStayKeyDown('S'))
		{
			_targetAngle = 225.f;
			_dir = LEFT_DOWN;
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

	//키를 뗐을때
	if (KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D'))
	{
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			_targetAngle = 0.f;
			_dir = UP;
		}
		else if (KEYMANAGER->isStayKeyDown('S'))
		{
			_targetAngle = 180.f;
			_dir = DOWN;
		}
		else
		{
			_isSlow = true;
		}
	}

	if (KEYMANAGER->isOnceKeyUp('W') || KEYMANAGER->isOnceKeyUp('S'))
	{
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			_targetAngle = 270.f;
			_dir = LEFT;
		}
		else if (KEYMANAGER->isStayKeyDown('D'))
		{
			_targetAngle = 90.f;
			_dir = RIGHT;
		}
		else
		{
			_isSlow = true;
		}
	}

	if (KEYMANAGER->isStayKeyDown('A') || KEYMANAGER->isStayKeyDown('D') ||
		KEYMANAGER->isStayKeyDown('S') || KEYMANAGER->isStayKeyDown('W'))
	{
		_speed += _accel * TIMEMANAGER->getElapsedTime();
		if (_speed >= 250.f)
		{
			_speed = 250.f;
		}
	}
}

void PlayerControler::Hit(float damage)
{
	_hp -= damage;

	if (_hp <= 0 && _isDead == false)
	{
		Dead();
	}

	if (_isDead == true)
	{
		_isRespawn = true;
	}
}

void PlayerControler::Dead()
{
	_isDead = true;
}

void PlayerControler::Respawn()
{
	gameObject->transform->SetPosition(25 * TILESIZE + 16, 36 * TILESIZE + 16);
	_hp = 100;
	_isDead = false;
	_isRespawn = false;
}

void PlayerControler::RespawnTime()
{
	if (_isRespawn == true)
	{
		_respawnTime += TIMEMANAGER->getElapsedTime();
	}
	else if (_isRespawn == false)
	{
		_respawnTime = 0.f;
	}

	if (_respawnTime >= 3.0f)
	{
		Respawn();
	}
}

void PlayerControler::MoveHandler()
{
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
}
