#include "stdafx.h"
#include "AnimObject.h"

AnimObject::AnimObject()
{
	renderer = new Renderer();
	AddComponent(renderer);

	animator = new Animator();
	AddComponent(animator);
	animator->Init();
}

AnimObject::~AnimObject()
{
}

void AnimObject::Init()
{
}