#include "stdafx.h"
#include "Transform.h"

GameObject::GameObject()
{
	name = "gameobject";
	transform = new Transform();
	transform->gameObject = this;
	isActive = true;
	tag = TAGMANAGER->GetTag("default");
	autoDisable = true;
}

GameObject::~GameObject()
{
}

void GameObject::Init()
{

}

void GameObject::Update()
{
	if (isActive == false) return;
	for (int i = 0; i < component_num; i++) {
		if (components[i]->enable == true)
			components[i]->Update();
	}

}

void GameObject::Render()
{
	if (isActive == false) return;
	for (int i = 0; i < component_num; i++) {
		if(components[i]->enable == true)
			components[i]->Render();
	}
}

void GameObject::Release()
{
	for (int i = 0; i < components.size(); i++) {
		if (components[i] != nullptr)
			components[i]->Release();
	}
	SAFE_DELETE(transform);
}

Component* GameObject::AddComponent(Component* component)
{
	component->gameObject = this;
	component->transform = this->transform;
	component->enable = true;
	components.push_back(component);
	component_num = components.size();
	return component;
}

void GameObject::OnEnable()
{
	if (isActive == false) return;
	for (int i = 0; i < components.size(); i++) {
		if (components[i]->enable == true)
			components[i]->OnEnable();
	}
}

void GameObject::OnDisable()
{
	for (int i = 0; i < components.size(); i++) {
		if (components[i]->enable == true)
			components[i]->OnDisable();
	}
}

void GameObject::OnCollision(GameObject* gameObject)
{
	if (isActive == false) return;
	for (int i = 0; i < components.size(); i++) {
		if (components[i]->enable == true)
			components[i]->OnCollision(gameObject);
	}
}

void GameObject::OnTriggerEnter(GameObject* gameObject)
{
	if (isActive == false) return;
	for (int i = 0; i < components.size(); i++) {
		if (components[i]->enable == true)
			components[i]->OnTriggerEnter(gameObject);
	}
}

void GameObject::OnTriggerStay(GameObject* gameObject)
{
	if (isActive == false) return;
	for (int i = 0; i < components.size(); i++) {
		if (components[i]->enable == true)
			components[i]->OnTriggerStay(gameObject);
	}
}

void GameObject::OnTriggerExit(GameObject* gameObject)
{
	if (isActive == false) return;
	for (int i = 0; i < components.size(); i++) {
		if (components[i]->enable == true)
			components[i]->OnTriggerExit(gameObject);
	}
}

void GameObject::SetActive(bool active)
{
	if (isActive == false && active == true) {
		isActive = active;
		OnEnable();
	}
	else if(isActive == true && active == false){
		isActive = active;
		OnDisable();
	}
}

void GameObject::MoveX(float x) 
{ 
	transform->MoveX(x); 
}
void GameObject::MoveY(float y) 
{ 
	transform->MoveY(y);
}
void GameObject::Move(float x, float y)
{ 
	transform->Move(x, y); 
}
