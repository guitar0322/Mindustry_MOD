#include "stdafx.h"
#include "EnemyGroundControler.h"
#include "ProjectileManager.h"
#include "EnemyInfo.h"
#include "Astar.h"
#include "TileInfo.h"
EnemyGroundControler::EnemyGroundControler()
{
}

EnemyGroundControler::~EnemyGroundControler()
{
}

void EnemyGroundControler::Init()
{
	_enemyInfo = gameObject->GetComponent<EnemyInfo>();
	_speed = _enemyInfo->GetSpeed();
	_testCoreTransform = _enemyInfo->GetCoreTransform();
	_angle = 0.f;
	_speedX = 0.f;
	_speedY = 0.f;
	_barrelLength = 50.f;
	_barrelAngle = Math::PI / 10.f;
	_deltaX = 0.f;
	_deltaY = 0.f;
	_deltaAngle = 0.f;

	_attackSpeed = 0.f;
	_enemyRadius = 57.f;
	_pathFindTime = 5.f;

	_chaseCore = true;
	_isAttack = false;

	_leftFire = true;
}

void EnemyGroundControler::Update()
{
	_pathFindTime += TIMEMANAGER->getElapsedTime();
	if (_pathFindTime >= 3.f)
	{
		_tileIdx = 1;
		int mTileX = transform->GetX() / TILESIZE;
		int mTileY = transform->GetY() / TILESIZE;
		int coreTileX = _enemyInfo->GetCoreTransform()->GetX() / TILESIZE;
		int coreTileY = _enemyInfo->GetCoreTransform()->GetY() / TILESIZE;
		_pathFindTime = 0;
		_corePath = _aStar->PathFind(mTileX, mTileY, coreTileX, coreTileY);
		if (_corePath.empty() == false)
		{
			_targetX = _corePath[_corePath.size() - _tileIdx].first * TILESIZE + 16;
			_targetY = _corePath[_corePath.size() - _tileIdx].second * TILESIZE + 16;
		}
	}

	transform->SetAngle(ConvertAngleD2D(_angle));

	if (GetDistance(transform->position, _enemyInfo->GetCoreTransform()->position) >= 600)
	{
		_angle = GetAngle(transform->GetX(), transform->GetY(), _targetX, _targetY);
		MoveTowardTo(transform, _targetX, _targetY, _enemyInfo->GetSpeed() * TIMEMANAGER->getElapsedTime());
		if (GetDistance(transform->position, Vector2(_targetX, _targetY)) <= 2 && _corePath.empty() == false) {
			_tileIdx++;
			_targetX = _corePath[_corePath.size() - _tileIdx].first * TILESIZE + 16;
			_targetY = _corePath[_corePath.size() - _tileIdx].second * TILESIZE + 16;
		}
	}
	else
	{
		_angle = GetAngle(transform->position, _enemyInfo->GetCoreTransform()->position);
		_attackSpeed += TIMEMANAGER->getElapsedTime();
		if (_attackSpeed >= 1.f && _leftFire == false)
		{
			_projectileManager->FireProjectile(transform->GetX() + cosf(_angle + _barrelAngle) * _barrelLength, transform->GetY() - sinf(_angle + _barrelAngle) * _barrelLength,
				ConvertAngleD2D(_angle), PROJECTILE_TYPE::ENEMYGROUND);
			_leftFire = true;
			_attackSpeed = 0.f;
		}

		if (_attackSpeed >= 1.f && _leftFire == true)
		{
			_projectileManager->FireProjectile(transform->GetX() + cosf(_angle - _barrelAngle) * _barrelLength, transform->GetY() - sinf(_angle - _barrelAngle) * _barrelLength,
				ConvertAngleD2D(_angle), PROJECTILE_TYPE::ENEMYGROUND);
			_leftFire = false;
			_attackSpeed = 0.f;
		}
	}


	//_testCoreTransform = _enemyInfo->GetCoreTransform();
	//_speed = _enemyInfo->GetSpeed();

	//if (_chaseCore)
	//{
	//	_deltaAngle = _angle;
	//	_isAttack = false;
	//}

	//if (GetDistance(transform->position, _enemyInfo->GetCoreTransform()->position) >= 600)
	//{
	//	_chaseCore = false;
	//	_isAttack = true;
	//}

	//if (GetDistance(transform->position, _testCoreTransform->position) > 1000 && !_chaseCore)			//700
	//{
	//	_chaseCore = true;
	//}

	//if (_isAttack)	
	//{
	//	_attackSpeed += TIMEMANAGER->getElapsedTime();

	//	_deltaX = cosf(_deltaAngle) * _enemyRadius;
	//	_deltaY = -sinf(_deltaAngle) * _enemyRadius;

	//	if (_attackSpeed >= 1.f && _leftFire == false)
	//	{
	//		_projectileManager->FireProjectile(transform->GetX() + _deltaX + 50, transform->GetY() + _deltaY, ConvertAngleD2D(_deltaAngle), PROJECTILE_TYPE::ENEMYGROUND);
	//		_leftFire = true;	
	//		_attackSpeed = 0.f;
	//	}

	//	if (_attackSpeed >= 1.f && _leftFire == true)
	//	{
	//		_projectileManager->FireProjectile(transform->GetX() + _deltaX - 50, transform->GetY() + _deltaY, ConvertAngleD2D(_deltaAngle), PROJECTILE_TYPE::ENEMYGROUND);
	//		_leftFire = false;
	//		_attackSpeed = 0.f;
	//	}
	//}

	//_speedX = cosf(_deltaAngle) * _speed * TIMEMANAGER->getElapsedTime();
	//_speedY = -sinf(_deltaAngle) * _speed * TIMEMANAGER->getElapsedTime();

	//transform->Move(_speedX, _speedY);
}

void EnemyGroundControler::Render()
{
	//Rect pathRect = RectMakePivot(Vector2(_corePath[_corePath.size() - _tileIdx].first * TILESIZE + 16, 
	//	_corePath[_corePath.size() - _tileIdx].second * TILESIZE + 16), Vector2(TILESIZE, TILESIZE), Pivot::Center);
	//D2DRENDERER->FillRectangleBack(pathRect);
	//for (int i = 0; i < _corePath.size(); i++)
	//{
	//	Rect pathRect = RectMakePivot(Vector2(_corePath[i].first * TILESIZE + 16, _corePath[i].second * TILESIZE + 16), Vector2(TILESIZE, TILESIZE), Pivot::Center);
	//	D2DRENDERER->FillRectangleBack(pathRect);
	//}
}
