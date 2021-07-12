#pragma once
#include "Transform.h"
class GameObject;
/***************************************************************************
* Component pattern Framework
* by ȫ�뿵
* up to date : 21-07-09
* # Property @Function
* # GameObject* gameObject : Component�� �����ϰ� �ִ� GameObject �ν��Ͻ�
* # Transform* transform : gameObject�� transform�ν��Ͻ�
* 
* @ void Render : �������� ���õ� �ڵ带 �� �����Ӹ��� ����
* 
* @ void Update : ����� ���õ� �ڵ带 �� �����Ӹ��� ����
* 
* @ OnEnable : gameObject�� Ȱ��ȭ ������ �ѹ� ȣ��
* 
* @ OnDisable : gameObject�� ��Ȱ��ȭ ������ �ѹ� ȣ��
* 
* @ OnCollision(GameObject* gameObject) : �浹�� �߻������� ȣ��
*	gameObject : �浹�� ��� ������Ʈ ������
* 
* @ OnTriggerEnter(GameObject* gameObject) : ��ħ �̺�Ʈ�� �߻������� �ѹ� ȣ��
*	gameObject : �浹������ ���� ��� ������Ʈ ������
* 
* @ OnTriggerStay(GameObject* gameObject) : ��ħ �̺�Ʈ�� �����ɶ� �����Ӹ��� ȣ��
*	gameObject : �浹������ �������ִ� ��� ������Ʈ ������
* 
* @ OnTriggerExit(GameObject* gameObject) : ��ħ �̺�Ʈ�� ����ɶ� �ѹ� ȣ��
*	gameObject : �浹�������� ��� ��� ������Ʈ ������
*****************************************************************************/
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