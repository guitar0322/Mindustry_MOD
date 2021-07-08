#pragma once
#include "Transform.h"
class GameObject;
class Component
{
public:
	Component();
	Component(GameObject* gameObject);
	~Component();
	GameObject* gameObject;
	Transform* transform;
	bool enable;
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();
	virtual void OnEnable();
	virtual void OnDisable();
	virtual void OnCollision(GameObject* gameObject);
	virtual void OnTriggerEnter(GameObject* gameObject);
	virtual void OnTriggerStay(GameObject* gameObject);
	virtual void OnTriggerExit(GameObject* gameObject);
};