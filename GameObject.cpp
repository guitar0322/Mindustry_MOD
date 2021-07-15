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
//@ void Update : ������Ʈ�� �ִ� ��� Component�� Update�Լ��� ȣ��
void GameObject::Update()
{
	if (isActive == false) return;
	for (int i = 0; i < component_num; i++) {
		if (components[i]->enable == true)
			components[i]->Update();
 	}
}
//@ void Render : ������Ʈ�� �ִ� ��� Component�� Render�Լ��� ȣ��
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

//@ Component* AddComponent : ������Ʈ�� ���ο� ������Ʈ�� �߰�
Component* GameObject::AddComponent(Component* component)
{
	component->gameObject = this;
	component->transform = this->transform;
	component->enable = true;
	components.push_back(component);
	component_num = components.size();
	return component;
}

//@ void OnEnable : ������Ʈ�� ��Ȱ��ȭ���� Ȱ��ȭ�� ���� �� �� ȣ��
void GameObject::OnEnable()
{
	if (isActive == false) return;
	for (int i = 0; i < components.size(); i++) {
		if (components[i]->enable == true)
			components[i]->OnEnable();
	}
}

//@ void OnDisable : ������Ʈ�� Ȱ��ȭ���� ��Ȱ��ȭ�� ���� �� �� ȣ��
void GameObject::OnDisable()
{
	for (int i = 0; i < components.size(); i++) {
		if (components[i]->enable == true)
			components[i]->OnDisable();
	}
}

//@ OnCollision(GameObject* gameObject) : �浹�� �߻������� ȣ��
// gameObject : �浹�� ��� ������Ʈ ������, ��� ������Ʈ�� OnCollision�Լ� ȣ��
void GameObject::OnCollision(GameObject* gameObject)
{
	if (isActive == false) return;
	for (int i = 0; i < components.size(); i++) {
		if (components[i]->enable == true)
			components[i]->OnCollision(gameObject);
	}
}

//@ OnTriggerEnter(GameObject* gameObject) : ��ħ �̺�Ʈ�� �߻������� �ѹ� ȣ��
// gameObject : �浹������ ���� ��� ������Ʈ ������, ��� ������Ʈ�� OnCollisionEnter�Լ� ȣ��
void GameObject::OnTriggerEnter(GameObject* gameObject)
{
	if (isActive == false) return;
	for (int i = 0; i < components.size(); i++) {
		if (components[i]->enable == true)
			components[i]->OnTriggerEnter(gameObject);
	}
}

//@ OnTriggerStay(GameObject* gameObject) : ��ħ �̺�Ʈ�� �����ɶ� �����Ӹ��� ȣ��
// gameObject : �浹������ �������ִ� ��� ������Ʈ ������, ��� ������Ʈ�� OnCollisionStay�Լ� ȣ��
void GameObject::OnTriggerStay(GameObject* gameObject)
{
	if (isActive == false) return;
	for (int i = 0; i < components.size(); i++) {
		if (components[i]->enable == true)
			components[i]->OnTriggerStay(gameObject);
	}
}

//@ OnTriggerExit(GameObject* gameObject) : ��ħ �̺�Ʈ�� ����ɶ� �ѹ� ȣ��
// gameObject : �浹�������� ��� ��� ������Ʈ ������, ��� ������Ʈ�� OnCollisionExit�Լ� ȣ��
void GameObject::OnTriggerExit(GameObject* gameObject)
{
	if (isActive == false) return;
	for (int i = 0; i < components.size(); i++) {
		if (components[i]->enable == true)
			components[i]->OnTriggerExit(gameObject);
	}
}

//@ SetActive(bool active) : ������Ʈ�� Ȱ��ȭ ���� ����
//	false���� true�� �Ǹ� OnEnable�Լ� ȣ��
//	true���� false�� �Ǹ� OnDisable�Լ� ȣ��
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
