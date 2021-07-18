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
	D2DRENDERER->DrawBackBuffer(_cameraStartX, _cameraStartY, 
		_cameraStartX + GetRenderWidth(), _cameraStartY + GetRenderHeight(),
		_screenStartX, _screenStartY, _screenStartX + _screenWidth, _screenStartY + _screenHeight);
}

void Camera::Update()
{
	_cameraStartX = transform->GetX() - GetRenderWidth() / 2;
	_cameraStartY = transform->GetY() - GetRenderHeight() / 2;
	if (_cameraStartX < 0) {
		_cameraStartX = 0;
		transform->SetX(GetRenderWidth() / 2);
	}

	if (transform->GetX() + GetRenderWidth() / 2 > MAPWIDTH) {
		_cameraStartX = MAPWIDTH - GetRenderWidth();
		transform->SetX(MAPWIDTH - GetRenderWidth() / 2);
	}

	if (_cameraStartY < 0) {
		_cameraStartY = 0;
		transform->SetY(GetRenderHeight() / 2);
	}

	if (transform->GetY() + GetRenderHeight() / 2 > MAPHEIGHT) {
		_cameraStartY = MAPHEIGHT - GetRenderHeight();
		transform->SetY(MAPHEIGHT - GetRenderHeight() / 2);
	}
	_renderRc = RectMakeCenter(Vector2(transform->GetX(), transform->GetY()), Vector2(GetRenderWidth(), GetRenderHeight()));

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

void Camera::StaticToBackBuffer()
{
	D2DRENDERER->DrawStaticBuffer(_cameraStartX, _cameraStartY,
		_cameraStartX + GetRenderWidth(), _cameraStartY + GetRenderHeight());
}

