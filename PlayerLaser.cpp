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
	_collectLaser->renderer->Init("laser_center");
	_collectLaser->SetActive(false);

	_detectRC = new ImageObject;
	_detectRC->Init();
	_detectRC->renderer->Init("laser_rc");
	_detectRC->SetActive(false);
}

void PlayerLaser::Update()
{
	ShootLaser();
	LaserAlpha();
	RcRotate();
	_collectLaserFirst->Update();
	_collectLaserEnd->Update();
	_collectLaser->Update();
	_detectRC->Update();
}

void PlayerLaser::Render()
{
	_collectLaserFirst->Render();
	_collectLaser->Render();
	_collectLaserEnd->Render();
	_detectRC->Render();
}

void PlayerLaser::ShootLaser()
{
	_laserX = _laserEndX * TILESIZE + 16;
	_laserY = _laserEndY * TILESIZE + 16;
	_laserAngle = ConvertAngleD2D(GetAngle(_laserStartX, _laserStartY, _laserX, _laserY));
	_laserDistance = GetDistance(_laserStartX, _laserStartY, _laserX, _laserY);
	float laserCenterX = (_laserX + _laserStartX) / 2.f;
	float laserCenterY = (_laserY + _laserStartY) / 2.f;

	_collectLaserEnd->transform->SetPosition(Vector2(_laserX, _laserY));
	_detectRC->transform->SetPosition(Vector2(_laserX, _laserY));
	_collectLaserFirst->transform->SetPosition(Vector2(_laserStartX, _laserStartY));
	_collectLaser->transform->SetPosition(Vector2(laserCenterX, laserCenterY));
	_collectLaser->transform->SetScale((_laserDistance / 280.f), 0.8f);
	_collectLaser->transform->SetAngle(_laserAngle + 90);
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

	_detectRC->transform->Rotate(_rcRotate);

}

void PlayerLaser::SetImage()
{
	//자원추출용
	CLIPMANAGER->AddClip("laser_end", "sprites/effects/laser-end.png", 72, 72);
	CLIPMANAGER->AddClip("laser_rc", "player/laser_rc.png", 35, 35);
	CLIPMANAGER->AddClip("laser_center", "player/laser_center.png", 280, 48);

}

void PlayerLaser::OffLaser()
{
	_collectLaserFirst->SetActive(false);
	_collectLaserEnd->SetActive(false);
	_collectLaser->SetActive(false);
	_detectRC->SetActive(false);
}
