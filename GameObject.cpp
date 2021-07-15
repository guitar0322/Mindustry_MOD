#include "stdafx.h"
#include "Transform.h"

GameObject::GameObject()
{
	name = L"gameobject";
	transform = new Transform();
	transform->gameObject = this;
	isActive = true;
	tag = TAGMANAGER->GetTag("default");
	//autoDisable = true;
}

GameObject::~GameObject()
{
}

void GameObject::Init()
{

}
//@ void Update : 오브젝트에 있는 모든 Component의 Update함수를 호출
void GameObject::Update()
{
	if (isActive == false) return;
	for (int i = 0; i < component_num; i++) {
		if (components[i]->enable == true)
			components[i]->Update();
 	}
}
//@ void Render : 오브젝트에 있는 모든 Component의 Render함수를 호출
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

//@ Component* AddComponent : 오브젝트에 새로운 컴포넌트를 추가
Component* GameObject::AddComponent(Component* component)
{
	component->gameObject = this;
	component->transform = this->transform;
	component->enable = true;
	components.push_back(component);
	component_num = components.size();
	return component;
}

//@ void OnEnable : 오브젝트가 비활성화에서 활성화로 이전 될 때 호출
void GameObject::OnEnable()
{
	if (isActive == false) return;
	for (int i = 0; i < components.size(); i++) {
		if (components[i]->enable == true)
			components[i]->OnEnable();
	}
}

//@ void OnDisable : 오브젝트가 활성화에서 비활성화로 이전 될 때 호출
void GameObject::OnDisable()
{
	for (int i = 0; i < components.size(); i++) {
		if (components[i]->enable == true)
			components[i]->OnDisable();
	}
}

//@ OnCollision(GameObject* gameObject) : 충돌이 발생했을때 호출
// gameObject : 충돌한 대상 오브젝트 포인터, 모든 컴포넌트의 OnCollision함수 호출
void GameObject::OnCollision(GameObject* gameObject)
{
	if (isActive == false) return;
	for (int i = 0; i < components.size(); i++) {
		if (components[i]->enable == true)
			components[i]->OnCollision(gameObject);
	}
}

//@ OnTriggerEnter(GameObject* gameObject) : 겹침 이벤트가 발생했을때 한번 호출
// gameObject : 충돌영역에 들어온 대상 오브젝트 포인터, 모든 컴포넌트의 OnCollisionEnter함수 호출
void GameObject::OnTriggerEnter(GameObject* gameObject)
{
	if (isActive == false) return;
	for (int i = 0; i < components.size(); i++) {
		if (components[i]->enable == true)
			components[i]->OnTriggerEnter(gameObject);
	}
}

//@ OnTriggerStay(GameObject* gameObject) : 겹침 이벤트가 유지될때 프레임마다 호출
// gameObject : 충돌영역에 겹쳐져있는 대상 오브젝트 포인터, 모든 컴포넌트의 OnCollisionStay함수 호출
void GameObject::OnTriggerStay(GameObject* gameObject)
{
	if (isActive == false) return;
	for (int i = 0; i < components.size(); i++) {
		if (components[i]->enable == true)
			components[i]->OnTriggerStay(gameObject);
	}
}

//@ OnTriggerExit(GameObject* gameObject) : 겹침 이벤트가 종료될때 한번 호출
// gameObject : 충돌영역에서 벗어난 대상 오브젝트 포인터, 모든 컴포넌트의 OnCollisionExit함수 호출
void GameObject::OnTriggerExit(GameObject* gameObject)
{
	if (isActive == false) return;
	for (int i = 0; i < components.size(); i++) {
		if (components[i]->enable == true)
			components[i]->OnTriggerExit(gameObject);
	}
}

//@ SetActive(bool active) : 오브젝트의 활성화 여부 설정
//	false에서 true가 되면 OnEnable함수 호출
//	true에서 false가 되면 OnDisable함수 호출
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
