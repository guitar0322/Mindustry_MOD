#include "stdafx.h"
#include "Camera.h"

Camera::Camera()
{
	CAMERAMANAGER->AddCamera(this);
}

Camera::~Camera()
{
}

void Camera::ResizeScreen(int screenWidth, int screenHeight)
{
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
}

void Camera::Init()
{
	ResizeScreen(WINSIZEX, WINSIZEY);
	_renderWidth = _screenWidth;
	_renderHeight = _screenHeight;
	_screenStartX = 0;
	_screenStartY = 0;
	_isShake = false;
	_shakeWeight = 0;
	_shakeNum = 0;
	_shakeMode = 0;
	_shakeAngle = 0;
	_shakeDir = 1;
	_zoomScale = 1;
}

void Camera::Render()
{
	int startX = transform->GetX() - _renderWidth / _zoomScale / 2;
	int startY = transform->GetY() - _renderHeight / _zoomScale / 2;
	if (startX < 0) {
		startX = 0;
		transform->SetX(_renderWidth / _zoomScale / 2);
	}

	if (transform->GetX() + _renderWidth / _zoomScale / 2 > MAPWIDTH) {
		startX = MAPWIDTH - _renderWidth / _zoomScale;
		transform->SetX(MAPWIDTH - _renderWidth / _zoomScale / 2);
	}

	if (startY < 0) {
		startY = 0;
		transform->SetY(_renderHeight / _zoomScale / 2);
	}

	if (transform->GetY() + _renderHeight / _zoomScale / 2 > MAPHEIGHT) {
		startY = MAPHEIGHT - _renderHeight / _zoomScale;
		transform->SetY(MAPHEIGHT - _renderHeight / _zoomScale / 2);
	}

	D2DRENDERER->DrawBackBuffer(startX, startY, startX + _renderWidth / _zoomScale, startY + _renderHeight / _zoomScale);
}

void Camera::Update()
{
	if (_isShake == true) {
		int nextX = _shakeStart.first;
		int nextY = _shakeStart.second;
		switch (_shakeMode) {
		case 0:
			nextX += _shakeWeight * _shakeDir;
			break;
		case 1:
			nextY += _shakeWeight * _shakeDir;
			break;
		case 2:
			_shakeAngle = RND->getFloat(Math::PI2);
			nextX += _shakeWeight * cosf(_shakeAngle);
			nextY += _shakeWeight * sinf(_shakeAngle);
			break;
		}
		transform->position.x = nextX;
		transform->position.y = nextY;
		_shakeDir *= -1;
	}
}

void Camera::Shake(int weight, int mode)
{
	_shakeWeight = weight;
	_isShake = true;
	_shakeNum = 0;
	_shakeMode = mode;
	_shakeStart = { transform->GetX(), transform->GetY() };
	_shakeDir = 1;
}

void Camera::ShakeOff()
{
	_isShake = false;
	transform->position.x = _shakeStart.first;
	transform->position.y = _shakeStart.second;
}

