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
	//플레이어 회전 설계
	//앵글을 깍아줄지 늘려줄지 정하는방법
	//현재앵글 - 목표앵글이 180보다 크면 줄여준다
	//앵글이 음수가 되면 360 - 음수절대값 으로 바꿔준다
	//앵글이 360보다 커지면 0 + 남는값으로 바꿔준다.

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
	
		_speed = 160.0f;
		/*if (_speed > 300.0f)
		{
			_speed = 300.0f;
		}*/
		float deltaAngle = transform->GetAngle() - _targetAngle; //델타앵글은 겟 앵글(가져온 앵글)에 타겟앵글(목표 앵글) 값을 뺀 값
		if (deltaAngle > 180) //만약에 델타 앵글이 180도 이상이라면?
		{
			if(transform->GetAngle() != _targetAngle) // 또한 겟 앵글이 타겟 앵글과 같지 않다면?
				transform->Rotate(2.f); // 값 2만큼 시계방향으로 돌아간다.(마이너스이므로 역방향(반시계)으로 돈다)
			if (transform->GetAngle() > _targetAngle) //만약에 겟 앵글이 타겟 앵글값보다 크다면?
				transform->SetAngle(_targetAngle); // 타겟앵글값으로 세팅(더이상 돌리기 진행 불가)
		}
		else // 나머지(델타 앵글이 180보다 작다면?)
		{
			if (transform->GetAngle() != _targetAngle) // 겟 엥글 값이 타겟 앵글값과 같지 않으면? 
				transform->Rotate(-2.f); // 값 2만큼 시계 반대방향으로 돌아간다.

			if (transform->GetAngle() < _targetAngle) //겟 앵글이 목표 앵글보다 값이 작으면?
				transform->SetAngle(_targetAngle);// 타겟 앵글값 만큼 세팅(더이상 돌리기 X)
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

		//플레이어 위치, 마우스 위치 GetAngle로 각도 구하기
		//targetAngle이 위에서 구한 Angle로 바뀌고
		//그 targetAngle로 플레이어가 회전해야된다
		//그리고 targetAngle과 플레이어 현재 angle값이 같아지면
		//그 때 총알을 발사한다.
		/*GetAngle(x1, y1, x2, y2)*/
	}


	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		
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


