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
	_constructLaserRC->renderer->SetAlpha(0.2f);
	_constructLaserRC->transform->SetScale(0.8f, 0.8f);
	_constructLaserRC->SetActive(false);

	_constuctLaserSizeS = new ImageObject;
	_constuctLaserSizeS->Init();
	_constuctLaserSizeS->renderer->Init("construct_laser_small");
	_constuctLaserSizeS->renderer->SetAlpha(0.2f);
	_constuctLaserSizeS->SetActive(false);

	_constuctLaserSizeL = new ImageObject;
	_constuctLaserSizeL->Init();
	_constuctLaserSizeL->renderer->Init("construct_laser_large");
	_constuctLaserSizeL->renderer->SetAlpha(0.2f);
	_constuctLaserSizeL->SetActive(false);

	//삭제
	_deleteLaserRC = new ImageObject;
	_deleteLaserRC->Init();
	_deleteLaserRC->renderer->Init("delete_rc");
	_deleteLaserRC->renderer->SetAlpha(0.2f);
	_deleteLaserRC->SetActive(false);

	_deleteLaserSizeS = new ImageObject;
	_deleteLaserSizeS->Init();
	_deleteLaserSizeS->renderer->Init("delete_laser_small");
	_deleteLaserSizeS->renderer->SetAlpha(0.2f);
	_deleteLaserSizeS->SetActive(false);

	_deleteLaserSizeL = new ImageObject;
	_deleteLaserSizeL->Init();
	_deleteLaserSizeL->renderer->Init("construct_laser_large");
	_deleteLaserSizeL->renderer->SetAlpha(0.2f);
	_deleteLaserSizeL->SetActive(false);

}

void PlayerConstructLaser::Update()
{
	ShootLaser();

	if (_isDelete == false)
	{
		_constructLaserRC->Update();
		if (_isLaserSizeL == false)
			_constuctLaserSizeS->Update();
		else
			_constuctLaserSizeL->Update();
	}
	else
	{
		_deleteLaserRC->Update();
		if (_isLaserSizeL == false)
			_deleteLaserSizeS->Update();
		else
			_deleteLaserSizeL->Update();
	}
}

void PlayerConstructLaser::Render()
{
	if (_isDelete == false)
	{
		if (_isLaserSizeL == false)
			_constuctLaserSizeS->Render();
		else
			_constuctLaserSizeL->Render();
	}
	else
	{
		_deleteLaserRC->Render();
		if (_isLaserSizeL == false)
			_deleteLaserSizeS->Render();
		else
			_deleteLaserSizeL->Render();
	}
}

void PlayerConstructLaser::ShootLaser()
{
	_constructAngle = ConvertAngleD2D(GetAngle(_constructStartX, _constructStartY, _constructEndX, _constructEndY));
	_constructDistance = GetDistance(_constructStartX, _constructStartY, _constructEndX, _constructEndY);
	float constructCenterX = (_constructEndX + _constructStartX) / 2.f;
	float constructCenterY = (_constructEndY + _constructStartY) / 2.f;
	if (_isDelete == false)
	{
		_constuctLaserSizeS->transform->SetPosition(Vector2(constructCenterX, constructCenterY));
		_constuctLaserSizeS->transform->SetAngle(_constructAngle);
		_constuctLaserSizeS->transform->SetScale(0.65f, (_constructDistance / 274.f));

		_constuctLaserSizeL->transform->SetPosition(Vector2(constructCenterX, constructCenterY));
		_constuctLaserSizeL->transform->SetAngle(_constructAngle);
		_constuctLaserSizeL->transform->SetScale(0.55f, (_constructDistance / 438.f));
	}
	else
	{
		_deleteLaserSizeS->transform->SetPosition(Vector2(constructCenterX, constructCenterY));
		_deleteLaserSizeS->transform->SetAngle(_constructAngle);
		_deleteLaserSizeS->transform->SetScale(0.65f, (_constructDistance / 274.f));

		_deleteLaserSizeL->transform->SetPosition(Vector2(constructCenterX, constructCenterY));
		_deleteLaserSizeL->transform->SetAngle(_constructAngle);
		_deleteLaserSizeL->transform->SetScale(0.55f, (_constructDistance / 438.f));
	}
}

void PlayerConstructLaser::SetImage()
{
	//건축용
	CLIPMANAGER->AddClip("construct_laser_small", "player/construct_laser_small.png", 91, 290);
	CLIPMANAGER->AddClip("construct_laser_large", "player/construct_laser_large.png", 114, 457);
	CLIPMANAGER->AddClip("construct_rc", "player/construct_rc.png", 43, 43);

	//삭제용
	CLIPMANAGER->AddClip("delete_laser_small", "player/delete_laser_small.png", 91, 290);
	CLIPMANAGER->AddClip("delete_laser_large", "player/delete_laser_large.png", 114, 457);
	CLIPMANAGER->AddClip("delete_rc", "player/delete_rc.png", 43, 43);
}

void PlayerConstructLaser::OnConstructLaser()
{
	if (_isDelete == false)
	{
		_constructLaserRC->SetActive(true);
		_constuctLaserSizeS->SetActive(true);
		_constuctLaserSizeL->SetActive(true);
	}
	else
	{
		_deleteLaserRC->SetActive(true);
		_deleteLaserSizeS->SetActive(true);
		_deleteLaserSizeL->SetActive(true);
	}
}

void PlayerConstructLaser::OffConstructLaser()
{
	if (_isDelete == false)
	{
		_constructLaserRC->SetActive(false);
		_constuctLaserSizeS->SetActive(false);
		_constuctLaserSizeL->SetActive(false);
	}
	else
	{
		_deleteLaserRC->SetActive(false);
		_deleteLaserSizeS->SetActive(false);
		_deleteLaserSizeL->SetActive(false);
	}
}
