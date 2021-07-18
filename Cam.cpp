#include "stdafx.h"
#include "Cam.h"
#include "Camera.h"

Cam::Cam()
{
	camera = new Camera();
	AddComponent(camera);
	camera->Init();
}

Cam::~Cam()
{
}
