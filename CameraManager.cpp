#include "stdafx.h"
#include "CameraManager.h"

CameraManager::CameraManager()
{
}

CameraManager::~CameraManager()
{
}

void CameraManager::Init()
{
}

void CameraManager::Release()
{
}

void CameraManager::AddCamera(Camera* newCamera)
{
	if (_cameraList.size() == 0) {
		_mainCam = newCamera;
	}
	_cameraList.push_back(newCamera);
}

void CameraManager::SetMainCam(Camera* mainCam)
{
	_mainCam = mainCam;
}
