#include "stdafx.h"
#include "PlayerControler.h"
#include "ProjectileManager.h"
#include "PlayerLaser.h"
#include "PlayerConstructLaser.h"
#include "EnemyInfo.h"
#include "TileInfo.h"
#include "GameMap.h"

void PlayerControler::Init()
{
	PlayerUIInit();

	_accel = 150.f;
	_targetAngle = 0.f;
	_friction = 0.f;
	_respawnTime = 0.f;
	_angleSpeed = 4.f;
	_hp = 92;
	hpUI = 0;
	reduceHP = 0;
	reduceTime = 0;
	_copperAmount, _leadAmount = 0;
	_boosterTime = 0;
	_scaleFlag = 1;
	_weaponLTrackRadius = DEFAULT_WEAPON_DISTANCE;
	_weaponRTrackRadius = DEFAULT_WEAPON_DISTANCE;
	_weaponLTrackAngle = DEFAULT_WEAPON_ANGLE;
	_weaponRTrackAngle = DEFAULT_WEAPON_ANGLE;
	_barrelLength = 30.f;
	_playerLaser = new PlayerLaser;
	_playerLaser->Init();

	_playerConstructLaser = new PlayerConstructLaser;
	_playerConstructLaser->Init();

	_attackSpeed = 0;
	_correctingTIme = 0;
	_isLeft = false;
	_isSlow = false;
	_isCollecting = false;
	_isDead = false;
	_dir = IDLE;
	_isHit = false;
}

void PlayerControler::Update()
{
	PlayerUIUpdate();
	

	if (_isSlow == true)
	{
		_friction = 180.f;
		_speed -= _friction * TIMEMANAGER->getElapsedTime();

		if (_speed < 0)
		{
			_speed = 0;
			_isSlow = false;
		}
	}

	MoveHandler();
	BoosterFireScale();

	if (!_isDead)
	{
		/* === 플레이어 방향 ===*/
		KeyHandle();
		if (_isCollecting == true)
		{
			_targetAngle = ConvertAngleD2D(GetAngle(transform->GetX(), transform->GetY(), _collectTile.x * TILESIZE + 16, _collectTile.y * TILESIZE + 16));
			transform->GetChild(2)->SetAngle(_targetAngle);

		}

		PlayerDirection();

		/* === 웨폰 방향 ===*/
		{
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
		}

		//마우스 왼쪽 클릭 시
		{
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				_worldX = ScreenToWorld(_ptMouse).x;
				_worldY = ScreenToWorld(_ptMouse).y;
				if (_isCollecting == false)
				{
					
					_targetAngle = ConvertAngleD2D(GetAngle(transform->position.x, transform->position.y, _worldX, _worldY));
				}
				else
				{
					_playerLaser->_collectLaserFirst->SetActive(false);
					_playerLaser->_collectLaserEnd->SetActive(false);
					_playerLaser->_collectLaser->SetActive(false);
					_playerLaser->_detectRC->SetActive(false);
					_isCollecting = false;
				}

				_attackSpeed += TIMEMANAGER->getElapsedTime();

				if (_attackSpeed >= 0.3f)
				{
					_weaponLTrackRadius = 9.13;
					if (_isLeft == false) // 만약에 왼쪽이 발동 안할 경우
					{
						_weaponRTrackRadius = 9.13;
						_projectileManager->FireProjectile(transform->GetChild(0)->GetX(), transform->GetChild(0)->GetY(),
							transform->GetChild(0)->GetAngle() + 2, PROJECTILE_TYPE::PLAYER); _weaponRTrackRadius = 9.13;
						EFFECTMANAGER->EmissionEffect("shoot",
							transform->GetChild(0)->GetX() + cosf(ConvertAngleAPI(transform->GetAngle())) * _barrelLength,
							transform->GetChild(0)->GetY() - sinf(ConvertAngleAPI(transform->GetAngle())) * _barrelLength,
							transform->GetAngle());
					}
					else // 나머지 값
					{
						_weaponLTrackRadius = 9.13;
						_projectileManager->FireProjectile(transform->GetChild(1)->GetX(), transform->GetChild(1)->GetY(),
							transform->GetChild(1)->GetAngle() - 2, PROJECTILE_TYPE::PLAYER);
						EFFECTMANAGER->EmissionEffect("shoot",
							transform->GetChild(1)->GetX() + cosf(ConvertAngleAPI(transform->GetAngle())) * _barrelLength,
							transform->GetChild(1)->GetY() - sinf(ConvertAngleAPI(transform->GetAngle())) * _barrelLength,
							transform->GetAngle());
					}
					_isLeft = !_isLeft; // 반복되게 하기
					_attackSpeed = 0;
				}
			}
		}
		ShootResoucesLaser();
		ShootConstructLaser();

		if (_isCollecting)
		{
			ResoucesCollect();
		}
	}

	/*테스트용*/
	//float time = 0;
	//time += TIMEMANAGER->getElapsedTime();

	//if (time > 3.0f)
	//{
	//	Hit(3);
	//	time = 0;

	//}

	PlayerHpAlpha();
}

void PlayerControler::Render()
{
	transform->GetChild(0)->gameObject->Render();
	transform->GetChild(1)->gameObject->Render();
	transform->GetChild(2)->gameObject->Render();
	transform->GetChild(4)->gameObject->Render();

	_playerLaser->Render();
	_playerConstructLaser->Render();

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
		_isSlow = false;
		_speed += _accel * TIMEMANAGER->getElapsedTime();
		_isSlow = false;

		if (_speed >= 250.f)
		{
			_speed = 250.f;
		}
	}
}

void PlayerControler::PlayerDirection()
{

	float deltaAngle = _targetAngle - transform->GetAngle();

	if (deltaAngle < 0) deltaAngle += 360;

	if (deltaAngle > 180)
	{
		if (Math::FloatEqual(_targetAngle, transform->GetAngle()) == false)
		{
			transform->Rotate(-_angleSpeed);
			if (_targetAngle > transform->GetAngle())
			{
				transform->SetAngle(_targetAngle);
				//포신 보정 해주고
				transform->GetChild(0)->SetAngle(_targetAngle);
				transform->GetChild(1)->SetAngle(_targetAngle);
				transform->GetChild(2)->SetAngle(_targetAngle);
				transform->GetChild(3)->SetAngle(_targetAngle);
				transform->GetChild(4)->SetAngle(_targetAngle);

			}
		}
	}
	else
	{
		if (Math::FloatEqual(_targetAngle, transform->GetAngle()) == false)
		{
			transform->Rotate(_angleSpeed);
			if (_targetAngle < transform->GetAngle())
			{
				transform->SetAngle(_targetAngle);
				transform->GetChild(0)->SetAngle(_targetAngle);
				transform->GetChild(1)->SetAngle(_targetAngle);
				transform->GetChild(2)->SetAngle(_targetAngle);
				transform->GetChild(3)->SetAngle(_targetAngle);
				transform->GetChild(4)->SetAngle(_targetAngle);

			}
		}
	}

	transform->GetChild(3)->SetPosition(transform->GetX() + cosf(ConvertAngleAPI(transform->GetChild(3)->GetAngle())) * (-26),
		transform->GetY() - sinf(ConvertAngleAPI(transform->GetChild(3)->GetAngle())) * (-26));
	transform->GetChild(4)->SetPosition(transform->GetX() + cosf(ConvertAngleAPI(transform->GetChild(4)->GetAngle())) * (-28),
		transform->GetY() - sinf(ConvertAngleAPI(transform->GetChild(4)->GetAngle())) * (-28));

	/*******************************************************
	1. 포신의 SetPotsition(플레이어 X + cosf(ConvertAngleAPI(transform->GetAngle())) * 포신궤도의 반지름,
	   Y - sinf(각도) * 포신궤도의 반지름)
	********************************************************/
	_weaponLTrackAngle = ConvertAngleD2D(acosf(cosf(ConvertAngleAPI(DEFAULT_WEAPON_ANGLE)) * DEFAULT_WEAPON_DISTANCE / _weaponLTrackRadius));
	_weaponRTrackAngle = ConvertAngleD2D(acosf(cosf(ConvertAngleAPI(DEFAULT_WEAPON_ANGLE)) * DEFAULT_WEAPON_DISTANCE / _weaponRTrackRadius));

	float _fireAngle = ConvertAngleD2D(acosf(cosf(ConvertAngleAPI(DEFAULT_WEAPON_ANGLE)) * DEFAULT_WEAPON_DISTANCE / _weaponRTrackRadius));

	_weaponLdistanceAngle = ConvertAngleAPI(transform->GetAngle() - _weaponLTrackAngle);
	_weaponRdistanceAngle = ConvertAngleAPI(transform->GetAngle() + _weaponRTrackAngle);

	if (_weaponLdistanceAngle < 0) _weaponLdistanceAngle += 360;
	transform->GetChild(0)->SetPosition((transform->GetX() + cosf(_weaponLdistanceAngle) * _weaponLTrackRadius),
		transform->GetY() - sinf(_weaponLdistanceAngle) * _weaponLTrackRadius);

	if (_weaponRdistanceAngle > 360) _weaponLdistanceAngle -= 360;
	transform->GetChild(1)->SetPosition((transform->GetX() + cosf(_weaponRdistanceAngle) * _weaponRTrackRadius),
		transform->GetY() - sinf(_weaponRdistanceAngle) * _weaponRTrackRadius);
}

void PlayerControler::ResoucesCollect()
{

	_correctingTIme += TIMEMANAGER->getElapsedTime();

	if (_correctingTIme >= 0.2f)
	{
		if (_colletingResources == COPPER)
		{
			if (_gameInfo->GetResourceAmount(COPPER) >= 4000) return;

			_copperAmount += 3;
			_gameInfo->AddResource(COPPER, _copperAmount);
		}
		else if (_colletingResources == LEAD)
		{
			if (_gameInfo->GetResourceAmount(LEAD) >= 4000) return;

			_leadAmount += 3;
			_gameInfo->AddResource(LEAD, _leadAmount);
		}

		_correctingTIme = 0;
	}
	_copperAmount = 0;
	_leadAmount = 0;

}

void PlayerControler::ShootResoucesLaser()
{
	float laserStartX = transform->GetX() + cosf(ConvertAngleAPI(transform->GetAngle())) * 18;
	float laserStartY = transform->GetY() - sinf(ConvertAngleAPI(transform->GetAngle())) * 18;
	_playerLaser->SetLaserStartPoint(laserStartX, laserStartY);

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		if (_isCollecting == false)
		{
			if (_ptMouse.x <= MainCam->GetScreenStart().first || _ptMouse.x >= MainCam->GetScreenStart().first + MainCam->GetScreenWidth())
				return;
			float mouseWorldX = ScreenToWorld(_ptMouse).x;
			float mouseWorldY = ScreenToWorld(_ptMouse).y;
			int tileX = mouseWorldX / TILESIZE;
			int tileY = mouseWorldY / TILESIZE;

			tagTile tileInfo = _gameMap->GetTileInfo(tileY * TILENUMX + tileX);

			if (tileInfo.resources != RES_NONE)
			{
				_isCollecting = true;
				_collectTile.x = _worldX / TILESIZE;
				_collectTile.y = _worldY / TILESIZE;
				_playerLaser->SetLaserEndPoint(_collectTile.x, _collectTile.y);
				_playerLaser->_collectLaserFirst->SetActive(true);
				_playerLaser->_collectLaserEnd->SetActive(true);
				_playerLaser->_collectLaser->SetActive(true);
				_playerLaser->_detectRC->SetActive(true);

				if (tileInfo.resources < 3)
				{
					_colletingResources = COPPER;
				}
				else if (tileInfo.resources > 3 && tileInfo.resources < 6)
				{
					_colletingResources = LEAD;
				}

			}
		}
	}
	
	if (KEYMANAGER->isOnceKeyUp(VK_RBUTTON))
	{
		_playerLaser->_collectLaserFirst->SetActive(false);
		_playerLaser->_collectLaserEnd->SetActive(false);
		_playerLaser->_collectLaser->SetActive(false);
		_playerLaser->_detectRC->SetActive(false);
		_isCollecting = false;
	}
	_playerLaser->Update();
	_playerConstructLaser->Update();

	if (_playerLaser->GetLaserDistance() >= 400)
	{
		_playerLaser->OffLaser();
		_isCollecting = false;
	}
}

void PlayerControler::ShootConstructLaser()
{
	float constructLaserStartX = transform->GetX() + cosf(ConvertAngleAPI(transform->GetAngle())) * 25;
	float constructLaserStartY = transform->GetY() - sinf(ConvertAngleAPI(transform->GetAngle())) * 25;
	_playerConstructLaser->SetLaserStartPoint(constructLaserStartX, constructLaserStartY);






}

void PlayerControler::BoosterFireScale()
{
	_boosterTime += TIMEMANAGER->getElapsedTime();

	if (_boosterTime >= 0.1f)
	{
		float scaleX = transform->GetChild(4)->GetScaleX() + 0.05f * _scaleFlag;
		float scaleY = transform->GetChild(4)->GetScaleY() + 0.05f * _scaleFlag;
		transform->GetChild(4)->SetScale(scaleX, scaleY);
		if (scaleX >= 1.f)
			_scaleFlag *= -1;
		if (scaleX <= 0.7f)
			_scaleFlag *= -1;
		_boosterTime = 0;
	}
}

void PlayerControler::Hit(float damage)
{
	_hp -= damage;
	_damage = damage;
	_isHit = true;
	//playerHpUIAlpha.SetActive(true);

	if (_hp <= 0 && _isDead == false)
	{
		Dead();
	}
}

void PlayerControler::Dead()
{
	EFFECTMANAGER->EmissionEffect("explosion", transform->GetX(), transform->GetY(), 0);
	EFFECTMANAGER->ActiveSmokeParticle(transform->GetX(), transform->GetY());
	gameObject->SetActive(false);
	transform->GetChild(3)->gameObject->SetActive(false);
	transform->GetChild(4)->gameObject->SetActive(false);
	_playerLaser->OffLaser();
	_isDead = true;
}

void PlayerControler::Respawn()
{
	gameObject->transform->SetPosition(25 * TILESIZE + 16, 36 * TILESIZE + 16);
	transform->GetChild(2)->SetPosition(25 * TILESIZE + 16, 36 * TILESIZE + 16);
	gameObject->SetActive(true);
	transform->GetChild(3)->gameObject->SetActive(true);
	transform->GetChild(4)->gameObject->SetActive(true);
	_hp = 100;
	_isDead = false;
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

void PlayerControler::PlayerUIInit()
{
	//클립~
	{
		CLIPMANAGER->AddClip("playerui", "sprites/ingameui/playerui.png", 70, 70);
		CLIPMANAGER->AddClip("playerhpui", "sprites/ingameui/playerhpui.png", 133, 92);
		CLIPMANAGER->AddClip("playerhpui_alpha", "sprites/ingameui/playerhpui_alpha.png", 133, 92);
		CLIPMANAGER->AddClip("playerhpui_pane", "sprites/ingameui/playerhpui_pane.png", 133, 92);
	}

	playerUI.Init();
	playerUI.uiRenderer->Init("playerui");
	playerUI.transform->SetPosition(65, 45);


	playerHpUIPane.Init();
	playerHpUIPane.uiRenderer->Init("playerhpui_pane");
	playerHpUIPane.transform->SetPosition(65, 50);

	playerHpUI.Init();
	playerHpUI.uiRenderer->Init("playerhpui");
	playerHpUI.transform->SetPosition(65, 50);
	playerHpUI.uiRenderer->SetClipY(hpUI);


	playerHpUIAlpha.Init();
	playerHpUIAlpha.uiRenderer->Init("playerhpui_alpha");
	playerHpUIAlpha.transform->SetPosition(65, 50);
	playerHpUIAlpha.uiRenderer->SetClipY(hpUI);
	playerHpUIAlpha.SetActive(false);

}

void PlayerControler::PlayerUIUpdate()
{
	playerUI.Update();
	playerHpUI.Update();
	playerHpUIAlpha.Update();
	playerHpUIPane.Update();
	playerHpUIAlpha.uiRenderer->SetClipY(hpUI);
	playerHpUI.uiRenderer->SetClipY(hpUI);
}

void PlayerControler::PlayerHpAlpha()
{
	float reduceHP = 0;
	float standNum = 1;
	
	if (_isHit)
	{
		if (reduceHP > _damage)
		{
			reduceHP = 0;
			hpUI = abs(_hp - 92 - _damage);

		}
		else
		{
			reduceHP += standNum * 0.05f;
			hpUI += reduceHP;
		}

	}
}
