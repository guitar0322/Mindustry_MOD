#include "stdafx.h"
#include "GameObject.h"
#include "Transform.h"

Component::Component()
{

}

Component::Component(GameObject* gameObject)
{
	this->gameObject = gameObject;
	transform = gameObject->transform;
}

Component::~Component()
{
}

void Component::Init()
{
	sprintf_s(debug[0], "%d", 1);

}

void Component::Update()
{

}

void Component::Render()
{
}

void Component::Release()
{
}

void Component::OnEnable()
{
}

void Component::OnDisable()
{
}

void Component::OnCollision(GameObject* gameObject)
{
}

void Component::OnTriggerEnter(GameObject* gameObject)
{
}

void Component::OnTriggerStay(GameObject* gameObject)
{
}

void Component::OnTriggerExit(GameObject* gameObject)
{
}

