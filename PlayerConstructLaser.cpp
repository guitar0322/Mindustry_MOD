#include "stdafx.h"
#include "PlayerConstructLaser.h"
#include "TileInfo.h"


PlayerConstructLaser::PlayerConstructLaser()
{
}

PlayerConstructLaser::~PlayerConstructLaser()
{
}

void PlayerConstructLaser::Init()
{
	SetImage();
	_isLaserSizeL = false;

	//건축
	_constructLaserRC = new ImageObject;
	_constructLaserRC->Init();
	_constructLaserRC->renderer->Init("construct_rc");
	_constructLaserRC->renderer->SetAlpha(0.5f);
	_constructLaserRC->transform->SetScale(0.8f, 0.8f);
	_constructLaserRC->SetActive(false);

	_constuctLaserSizeS = new ImageObject;
	_constuctLaserSizeS->Init();
	_constuctLaserSizeS->renderer->Init("construct_laser_small");
	_constuctLaserSizeS->renderer->SetAlpha(0.5f);
	_constuctLaserSizeS->SetActive(false);

	_constuctLaserSizeL = new ImageObject;
	_constuctLaserSizeL->Init();
	_constuctLaserSizeL->renderer->Init("construct_laser_large");
	_constuctLaserSizeL->renderer->SetAlpha(0.5f);
	_constuctLaserSizeL->SetActive(false);

	//삭제
	_deleteLaserRC = new ImageObject;
	_deleteLaserRC->Init();
	_deleteLaserRC->renderer->Init("delete_rc");
	_deleteLaserRC->renderer->SetAlpha(0.5f);
	_deleteLaserRC->SetActive(false);

	_deleteLaserSizeS = new ImageObject;
	_deleteLaserSizeS->Init();
	_deleteLaserSizeS->renderer->Init("delete_laser_small");
	_deleteLaserSizeS->renderer->SetAlpha(0.5f);
	_deleteLaserSizeS->SetActive(false);

	_deleteLaserSizeL = new ImageObject;
	_deleteLaserSizeL->Init();
	_deleteLaserSizeL->renderer->Init("construct_laser_large");
	_deleteLaserSizeL->renderer->SetAlpha(0.5f);
	_deleteLaserSizeL->SetActive(false);

}

void PlayerConstructLaser::Update()
{
	ShootLaser();
	_constructLaserRC->Update();
	if (_isLaserSizeL == false)
		_constuctLaserSizeS->Update();
	else
		_constuctLaserSizeL->Update();

	_deleteLaserRC->Update();
	_deleteLaserSizeS->Update();
	_deleteLaserSizeL->Update();
}

void PlayerConstructLaser::Render()
{
	if(_isLaserSizeL == false)
		_constuctLaserSizeS->Render();
	else
		_constuctLaserSizeL->Render();
	_deleteLaserRC->Render();
	_deleteLaserSizeS->Render();
	_deleteLaserSizeL->Render();
}

void PlayerConstructLaser::ShootLaser()
{
	_constructAngle = ConvertAngleD2D(GetAngle(_constructStartX, _constructStartY, _constructEndX, _constructEndY));
	_constructDistance = GetDistance(_constructStartX, _constructStartY, _constructEndX, _constructEndY);
	float constructCenterX = (_constructEndX + _constructStartX) / 2.f;
	float constructCenterY = (_constructEndY + _constructStartY) / 2.f;

	_constuctLaserSizeS->transform->SetPosition(Vector2(constructCenterX, constructCenterY));
	_constuctLaserSizeS->transform->SetAngle(_constructAngle);
	_constuctLaserSizeS->transform->SetScale(0.65f, (_constructDistance / 274.f));

	_constuctLaserSizeL->transform->SetPosition(Vector2(constructCenterX, constructCenterY));
	_constuctLaserSizeL->transform->SetAngle(_constructAngle);
	_constuctLaserSizeL->transform->SetScale(1.f, (_constructDistance / 323.f));

}

void PlayerConstructLaser::SetImage()
{
	//건축용
	CLIPMANAGER->AddClip("construct_laser_small", "player/construct_laser_small.png", 91, 290);
	CLIPMANAGER->AddClip("construct_laser_large", "player/construct_laser_large.png", 100, 375);
	CLIPMANAGER->AddClip("construct_rc", "player/construct_rc.png", 43, 43);

	//삭제용
	CLIPMANAGER->AddClip("delete_laser_small", "player/delete_laser_small.png", 91, 290);
	CLIPMANAGER->AddClip("delete_laser_large", "player/delete_laser_large.png", 137, 953);
	CLIPMANAGER->AddClip("delete_rc", "player/delete_rc.png", 30, 30);
}

void PlayerConstructLaser::OnConstructLaser()
{
	_constructLaserRC->SetActive(true);
	_constuctLaserSizeS->SetActive(true);
	_constuctLaserSizeL->SetActive(true);
}

void PlayerConstructLaser::OffConstructLaser()
{
	_constructLaserRC->SetActive(false);
	_constuctLaserSizeS->SetActive(false);
	_constuctLaserSizeL->SetActive(false);
}
