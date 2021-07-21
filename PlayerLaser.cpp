#include "stdafx.h"
#include "PlayerLaser.h"

PlayerLaser::PlayerLaser()
{
}

PlayerLaser::~PlayerLaser()
{
}

void PlayerLaser::Init()
{
	SetImage();

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
	_collectLaser->renderer->Init("laser");
	_collectLaser->SetActive(false);


	_detectRc = new ImageObject;
	_detectRc->Init();
	_detectRc->renderer->Init("laser_rc");
	_detectRc->SetActive(false);
}

void PlayerLaser::Update()
{
}

void PlayerLaser::Render()
{
	_collectLaserFirst->Render();
	_collectLaserEnd->Render();
	//_collectLaser->Render();
	_detectRc->Render();

}

void PlayerLaser::ShootLaser()
{
	float laserDistance = GetDistance(_laserStartX, _laserStartY, _laserX, _laserY);
	float deltaX = _laserX + _laserStartX;
	float deltaY = _laserY + _laserStartY;
	float laserX = deltaX / 2;
	float laserY = deltaY / 2;

	_collectLaserEnd->transform->SetPosition(Vector2(_laserEndX * 32 + 16, _laserEndY * 32 + 16));
	_detectRc->transform->SetPosition(Vector2(_laserEndX * 32 + 16, _laserEndY * 32 + 16));
	_collectLaserFirst->transform->SetPosition(Vector2(_laserStartX, _laserStartY));
	_collectLaser->transform->SetPosition(Vector2(laserX, laserY));
	_collectLaser->transform->SetScaleX(laserDistance / 7);
}

void PlayerLaser::SetImage()
{
	CLIPMANAGER->AddClip("laser_end", "sprites/effects/laser-end.png", 72, 72);
	CLIPMANAGER->AddClip("laser", "sprites/effects/laser.png", 4, 48);
	CLIPMANAGER->AddClip("laser_rc", "player/laser_rc.png", 35, 35);

}
