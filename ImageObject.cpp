#include "stdafx.h"
#include "ImageObject.h"

ImageObject::ImageObject()
{
	renderer = new Renderer();
	AddComponent(renderer);
}

ImageObject::~ImageObject()
{
}
