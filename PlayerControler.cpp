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
	case LEFT:
		transform->MoveX(-_speed * TIMEMANAGER->getElapsedTime()); // X 값을 설정한 스피드 * 시간 만큼 곱하기
		break;
	case RIGHT:
		transform->MoveX(_speed * TIMEMANAGER->getElapsedTime()); // X 값을 설정한 스피드 * 시간 만큼 곱하기
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

	if (KEYMANAGER->isStayKeyDown('A')) // A키를 누르면
	{
		_speed++;
		if (_speed > 200.0f)
		{
			_speed = 200.0f;
		}
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
		//스피드 bool값을 주기전에는 키 누르는동안 스피드를 지속적으로 움직이게한다. 다만 일정 스피드만 움직이게 한다.
		//키를 뗐을때 bool값을  \true로 바꾼다
		//update에서 bool값이 true면 speed를 깎는다
		//speed가 0이하가 되면 speed를 0으로 바꾸고 bool값을 false로 한다
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
					Math::ToRadian(transform->GetAngle() + 90), PROJECTILE_TYPE::PLAYER);
		}
		else // 나머지 값
		{
			_projectileManager->FireProjectile(transform->GetX()-10, transform->GetY(),
				Math::ToRadian(transform->GetAngle() + 90), PROJECTILE_TYPE::PLAYER);
		}
		_isLeft = !_isLeft; // 반복되게 하기
	}
}


