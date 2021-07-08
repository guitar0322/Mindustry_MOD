#include "stdafx.h"
#include "Cam.h"
Cam::Cam()
{
	camera = new Camera();
	AddComponent(camera);
	camera->Init();
}

Cam::~Cam()
{
}
