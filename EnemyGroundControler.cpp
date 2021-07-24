#include "stdafx.h"
#include "EnemyGroundControler.h"
#include "ProjectileManager.h"
#include "EnemyInfo.h"
#include "Astar.h"
#include "TileInfo.h"
#include "Prop.h"

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
	_barrelRRadius = DEFAULT_WEAPON_RADIUS;
	_barrelLRadius = DEFAULT_WEAPON_RADIUS;
	_barrelLDeltaAngle = DEFAULT_WEAPON_ANGLE;
	_barrelRDeltaAngle = DEFAULT_WEAPON_ANGLE;

	_barrelAngle = DEFAULT_WEAPON_ANGLE;

	_deltaX = 0.f;
	_deltaY = 0.f;
	_deltaAngle = 0.f;

	_attackSpeed = 0.f;
	_enemyRadius = 57.f;
	_pathFindTime = 5.f;
	_attackRange = 400.f;

	_chaseCore = true;
	_isAttack = false;

	_leftFire = true;
	SetGroundWeapon();
}

void EnemyGroundControler::Update()
{
	SetGroundWeaponUpdate();


	_pathFindTime += TIMEMANAGER->getElapsedTime();
	if (_pathFindTime >= 3.f)
	{
		_tileIdx = 1;
		int mTileX = transform->GetX() / TILESIZE;
		int mTileY = transform->GetY() / TILESIZE;
		int coreTileX = _enemyInfo->GetCoreTransform()->GetX() / TILESIZE;
		int coreTileY = _enemyInfo->GetCoreTransform()->GetY() / TILESIZE;
		_pathFindTime = 0;
		_corePath = _aStar->PathFind(mTileX, mTileY, coreTileX, coreTileY, gameObject);
		_curPropV = _aStar->GetPropIdxV();

		if (_corePath.empty() == false)
		{
			_targetX = _corePath[_corePath.size() - _tileIdx].first * TILESIZE + 16;
			_targetY = _corePath[_corePath.size() - _tileIdx].second * TILESIZE + 16;
		}
	}

	transform->SetAngle(ConvertAngleD2D(_angle));

	if (GetDistance(transform->position, _enemyInfo->GetCoreTransform()->position) >= _attackRange)
	{
		_angle = GetAngle(transform->GetX(), transform->GetY(), _targetX, _targetY);
		MoveTowardTo(transform, _targetX, _targetY, _enemyInfo->GetSpeed() * TIMEMANAGER->getElapsedTime());
		gameObject->GetComponent<Animator>()->Resume();
		if (GetDistance(transform->position, Vector2(_targetX, _targetY)) <= 2 && _corePath.empty() == false) {
			_tileIdx++;
			_targetX = _corePath[_corePath.size() - _tileIdx].first * TILESIZE + 16;
			_targetY = _corePath[_corePath.size() - _tileIdx].second * TILESIZE + 16;
		}

		_targetIdx = -1;
		for (int i = 0; i < _curPropV.size(); i++)
		{
			if (_curPropV[i]->isActive == false) continue;
			float distance = GetDistance(transform->position, _curPropV[i]->transform->position);
			if (distance < _attackRange)
			{
				_targetIdx = i;
				break;
			}
		}
		if (_targetIdx != -1)
		{
			_angle = GetAngle(transform->position, _curPropV[_targetIdx]->transform->position);
			Attack();
		}
	}
	else
	{
		gameObject->GetComponent<Animator>()->Pause();
		_angle = GetAngle(transform->position, _enemyInfo->GetCoreTransform()->position);
		Attack();
	}





	//1. 포신의 SetPotsition(플레이어 X + cosf(ConvertAngleAPI(transform->GetAngle())) * 포신궤도의 반지름,
	//	Y - sinf(각도) * 포신궤도의 반지름)

	//transform->GetChild(0)->SetPosition(transform->GetX() + cosf(ConvertAngleAPI(transform->GetAngle() + _)) * _barrelLength,
	//	transform->GetY() - sinf(ConvertAngleAPI(transform->GetAngle()) * _barrelLength));

	//transform->GetChild(1)->SetPosition(transform->GetX() + cosf(ConvertAngleAPI(transform->GetAngle())) * _barrelLength,
	//	transform->GetY() - sinf(ConvertAngleAPI(transform->GetAngle()) * _barrelLength));

	//transform->GetChild(0)->SetAngle(ConvertAngleD2D(transform->GetAngle()));
	//transform->GetChild(1)->SetAngle(ConvertAngleD2D(transform->GetAngle()));
	//SetGroundWeaponUpdate();


}

void EnemyGroundControler::Render()
{
	transform->GetChild(0)->gameObject->Render();
	transform->GetChild(1)->gameObject->Render();

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < _corePath.size(); i++)
		{
			Rect pathRect = RectMakePivot(Vector2(_corePath[i].first * TILESIZE + 16, _corePath[i].second * TILESIZE + 16), Vector2(TILESIZE, TILESIZE), Pivot::Center);
			D2DRENDERER->FillRectangleBack(pathRect);
		}
	}
}

void EnemyGroundControler::SetGroundWeapon()
{
	_groundWeaponL = new ImageObject();
	_groundWeaponR = new ImageObject();

	_groundWeaponL->Init();
	_groundWeaponR->Init();

	_groundWeaponL->renderer->Init("dagger_weapon_left");
	_groundWeaponL->transform->SetScale(1.5f, 1.5f);
	_groundWeaponR->renderer->Init("dagger_weapon_right");
	_groundWeaponR->transform->SetScale(1.5f, 1.5f);

	transform->AddChild(_groundWeaponL->transform);
	transform->AddChild(_groundWeaponR->transform);
	//1. 포신의 SetPotsition(플레이어 X + cosf(ConvertAngleAPI(transform->GetAngle())) * 포신궤도의 반지름,
	//	Y - sinf(각도) * 포신궤도의 반지름)
}

void EnemyGroundControler::SetGroundWeaponUpdate()
{
	_groundWeaponR->Update();
	_groundWeaponL->Update();
	if (_barrelLRadius < DEFAULT_WEAPON_RADIUS)
	{
		_barrelLRadius += 3.f * TIMEMANAGER->getElapsedTime();
		if (_barrelLRadius > DEFAULT_WEAPON_RADIUS)
			_barrelLRadius = DEFAULT_WEAPON_RADIUS;
	}
	if (_barrelRRadius < DEFAULT_WEAPON_RADIUS)
	{
		_barrelRRadius += 3.f * TIMEMANAGER->getElapsedTime();
		if (_barrelRRadius > DEFAULT_WEAPON_RADIUS)
			_barrelRRadius = DEFAULT_WEAPON_RADIUS;
	}

	_barrelLDeltaAngle = ConvertAngleD2D(acosf(cosf(ConvertAngleAPI(DEFAULT_WEAPON_ANGLE)) * DEFAULT_WEAPON_RADIUS / _barrelLRadius));
	_barrelRDeltaAngle = ConvertAngleD2D(acosf(cosf(ConvertAngleAPI(DEFAULT_WEAPON_ANGLE)) * DEFAULT_WEAPON_RADIUS / _barrelRRadius));

	float _fireAngle;
	if(_leftFire == true)
		_fireAngle = ConvertAngleD2D(acosf(cosf(ConvertAngleAPI(DEFAULT_WEAPON_ANGLE)) * DEFAULT_WEAPON_RADIUS / _barrelLRadius));
	else
		_fireAngle = ConvertAngleD2D(acosf(cosf(ConvertAngleAPI(DEFAULT_WEAPON_ANGLE)) * DEFAULT_WEAPON_RADIUS / _barrelRRadius));

	float _barrelLAngle = ConvertAngleAPI(transform->GetAngle() - _barrelLDeltaAngle);
	float _barrelRAngle = ConvertAngleAPI(transform->GetAngle() + _barrelRDeltaAngle);

	if (_barrelLAngle < 0) _barrelLAngle += 360;

	transform->GetChild(0)->SetPosition(transform->GetX() + cosf(_barrelLAngle) * _barrelLRadius,
		transform->GetY() - sinf(_barrelLAngle) * _barrelLRadius);

	if (_barrelRAngle > 360) _barrelRAngle -= 360;

	transform->GetChild(1)->SetPosition(transform->GetX() + cosf(_barrelRAngle) * _barrelRRadius,
		transform->GetY() - sinf(_barrelRAngle) * _barrelRRadius);

	//transform->GetChild(0)->SetPosition(transform->GetX() + cosf(_angle - _barrelAngle) * _barrelLength, transform->GetY() - sinf(_angle - _barrelAngle) * _barrelLength);
	//transform->GetChild(1)->SetPosition(transform->GetX() + cosf(_angle + _barrelAngle) * _barrelLength, transform->GetY() - sinf(_angle + _barrelAngle) * _barrelLength);

	transform->GetChild(0)->SetAngle(transform->GetAngle());
	transform->GetChild(1)->SetAngle(transform->GetAngle());


}

void EnemyGroundControler::Attack()
{
	_attackSpeed += TIMEMANAGER->getElapsedTime();

	float _barrelLAngle = ConvertAngleAPI(transform->GetAngle() - _barrelLDeltaAngle);
	float _barrelRAngle = ConvertAngleAPI(transform->GetAngle() + _barrelRDeltaAngle);

	if (_attackSpeed >= 0.3f && _leftFire == false)
	{
		_projectileManager->FireProjectile(transform->GetChild(1)->GetX() + cosf(_angle) * 30, transform->GetChild(1)->GetY() - sinf(_angle) * 30,
			ConvertAngleD2D(_angle), PROJECTILE_TYPE::ENEMYGROUND);

		EFFECTMANAGER->EmissionEffect("shoot", transform->GetChild(1)->GetX() + cosf(_angle) * 30, transform->GetChild(1)->GetY() - sinf(_angle) * 30,
			ConvertAngleD2D(_angle));

		_barrelRRadius = ATTACK_WEAPON_RADIUS;
		_leftFire = true;
		_attackSpeed = 0.f;
	}

	if (_attackSpeed >= 0.3f && _leftFire == true)
	{
		_projectileManager->FireProjectile(transform->GetChild(0)->GetX() + cosf(_angle) * 30, transform->GetChild(0)->GetY() - sinf(_angle) * 30,
			ConvertAngleD2D(_angle), PROJECTILE_TYPE::ENEMYGROUND);

		EFFECTMANAGER->EmissionEffect("shoot", transform->GetChild(0)->GetX() + cosf(_angle) * 30, transform->GetChild(0)->GetY() - sinf(_angle) * 30,
			ConvertAngleD2D(_angle));

		_barrelLRadius = ATTACK_WEAPON_RADIUS;
		_leftFire = false;
		_attackSpeed = 0.f;
	}
}
