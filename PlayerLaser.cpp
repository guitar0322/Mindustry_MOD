#include "stdafx.h"
#include "PlayerLaser.h"
#include "TileInfo.h"
PlayerLaser::PlayerLaser()
{
}

PlayerLaser::~PlayerLaser()
{
}

void PlayerLaser::Init()
{
	SetImage();

	_laserAlphaTime = 0;

	//플레이어 광물 채취용 레이저
	_collectLaserFirst = new ImageObject;
	_collectLaserFirst->Init();
	_collectLaserFirst->renderer->Init("laser_end");
	_collectLaserFirst->transform->SetScale(0.8f, 0.8f);
	_collectLaserFirst->SetActive(false);


	_collectLaserEnd = new ImageObject;
	_collectLaserEnd->Init();
	_collectLaserEnd->renderer->Init("laser_end");
	_collectLaserEnd->transform->SetScale(0.8f, 0.8f);
	_collectLaserEnd->SetActive(false);

	_collectLaser = new ImageObject;
	_collectLaser->Init();
	//_collectLaser->renderer->Init("laser");
	_collectLaser->renderer->Init("laser_center");
	_collectLaser->SetActive(false);


	_detectRc = new ImageObject;
	_detectRc->Init();
	_detectRc->renderer->Init("laser_rc");
	_detectRc->SetActive(false);

}

void PlayerLaser::Update()
{
	ShootLaser();
	LaserAlpha();
	RcRotate();
	_collectLaserFirst->Update();
	_collectLaserEnd->Update();
	_collectLaser->Update();
	_detectRc->Update();
}

void PlayerLaser::Render()
{
	_collectLaserFirst->Render();
	_collectLaser->Render();
	_collectLaserEnd->Render();
	_detectRc->Render();

}

void PlayerLaser::ShootLaser()
{
	_laserX = _laserEndX * TILESIZE + 16;
	_laserY = _laserEndY * TILESIZE + 16;
	_laserAngle = ConvertAngleD2D(GetAngle(_laserStartX, _laserStartY, _laserX, _laserY));
	float laserDistance = GetDistance(_laserStartX, _laserStartY, _laserX, _laserY);
	float laserCenterX = (_laserX + _laserStartX) / 2.f;
	float laserCenterY = (_laserY + _laserStartY) / 2.f;

	_collectLaserEnd->transform->SetPosition(Vector2(_laserX, _laserY));
	_detectRc->transform->SetPosition(Vector2(_laserX, _laserY));
	_collectLaserFirst->transform->SetPosition(Vector2(_laserStartX, _laserStartY));
	_collectLaser->transform->SetPosition(Vector2(laserCenterX, laserCenterY));
	_collectLaser->transform->SetScale((laserDistance / 280.f), 0.8f);
	//_collectLaser->transform->SetScale(5.f, 1.f);
	//_collectLaser->transform->SetScale(5.f, 1.f);
	_collectLaser->transform->SetAngle(_laserAngle + 90);

	if (laserDistance >= 400)
	{
		_collectLaserFirst->SetActive(false);
		_collectLaserEnd->SetActive(false);
		_collectLaser->SetActive(false);
		_detectRc->SetActive(false);
	}
}

void PlayerLaser::LaserAlpha()
{
	_laserAlphaTime += TIMEMANAGER->getElapsedTime();

	if (_laserAlphaTime >= 0.1f)
	{
		_collectLaserFirst->renderer->SetAlpha(0.7f);
		_collectLaserEnd->renderer->SetAlpha(0.7f);
		_collectLaser->renderer->SetAlpha(0.7f);
		_laserAlphaTime = 0;
	}
	else
	{
		_collectLaserFirst->renderer->SetAlpha(1.f);
		_collectLaserEnd->renderer->SetAlpha(1.f);
		_collectLaser->renderer->SetAlpha(1.f);
	}
}

void PlayerLaser::RcRotate()
{
	_rcRotateTime += TIMEMANAGER->getElapsedTime();

	if (_rcRotateTime >= 0.1f)
	{
		_rcRotate -= TIMEMANAGER->getElapsedTime();
		_rcRotateTime = 0;
	}

	_detectRc->transform->Rotate(_rcRotate);

}

void PlayerLaser::SetImage()
{
	CLIPMANAGER->AddClip("laser_end", "sprites/effects/laser-end.png", 72, 72);
	//CLIPMANAGER->AddClip("laser", "sprites/effects/laser.png", 4, 48);
	CLIPMANAGER->AddClip("laser_rc", "player/laser_rc.png", 35, 35);
	CLIPMANAGER->AddClip("laser_center", "player/laser_center.png", 280, 48);

}
