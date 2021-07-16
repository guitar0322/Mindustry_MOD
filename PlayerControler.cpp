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
	if (KEYMANAGER->isStayKeyDown('A')&& KEYMANAGER->isStayKeyDown('W')) // A와 W키를 누르면 왼쪽 위 대각선으로 간다.
	{
		_isDiagonal = true;
		_targetAngle = 315.f;
		_dir = LEFT_UP;
	}
	if (KEYMANAGER->isStayKeyDown('D')&& KEYMANAGER->isStayKeyDown('S')) // D와 S키를 누르면 오른쪽 아래 대각선으로 간다.
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
	if (KEYMANAGER->isOnceKeyUp('A')||KEYMANAGER->isOnceKeyUp('D')) // 만약에 A또는 D 키를 떼면?
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

	if (KEYMANAGER->isStayKeyDown('A')) // A키를 누르면
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

		//플레이어 위치, 마우스 위치 GetAngle로 각도 구하기
		//targetAngle이 위에서 구한 Angle로 바뀌고
		//그 targetAngle로 플레이어가 회전해야된다
		//그리고 targetAngle과 플레이어 현재 angle값이 같아지면
		//그 때 총알을 발사한다.
		/*GetAngle(x1, y1, x2, y2)*/
	}


	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		SOUNDMANAGER->play("shoot", 1.0f);
		if (_isLeft == false) // 만약에 왼쪽이 발동 안할 경우
		{
				_projectileManager->FireProjectile(transform->GetX()+10, transform->GetY(),
					Math::ToRadian(transform->GetAngle()+45), PROJECTILE_TYPE::PLAYER);
		}
		else // 나머지 값
		{
			_projectileManager->FireProjectile(transform->GetX()-10, transform->GetY(),
				Math::ToRadian(transform->GetAngle()+45), PROJECTILE_TYPE::PLAYER);
		}
		_isLeft = !_isLeft; // 반복되게 하기

	}
}

void PlayerControler::PlayerDirection()
{
	float deltaAngle = _targetAngle - transform->GetAngle();

	if (deltaAngle < 0) deltaAngle += 360; // 델타 엥글이 0보다 작으면 360을 더해준다.

	if (deltaAngle > 180) // 만약에 델타엥글이 180보다 크다면?
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


