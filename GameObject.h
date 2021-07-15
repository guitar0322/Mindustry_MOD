#pragma once
class GameObject;
class Transform;
class Component;

/************************************************************************************
* Component Pattern Framework - class GameObject
* Component���� �����̳� ���� �� ����� �����Ű�� ��ü
* by ȫ�뿵
* up to date : 21-07-09
* 
* # Property @ Function
* # Transform* transform : ���忡�� ������ ������ ����ִ� Ŭ����(ȸ��, ��ǥ, ũ�� ��)
* # bool isActive : Ȱ��ȭ ����. false�� ��� Component�� ����� �������� ����
* # int tag : ������Ʈ ������ �����ϱ� ���� int�� ����. TAGMANAGER�� ���� ����
* # vector<Component*> components : ������Ʈ�� �߰��Ǿ� �ִ� Component ���
* @ Function�� .cpp�� ����
************************************************************************************/
class GameObject
{
private:
	int component_num;
	//bool autoDisable;
	vector<Component*> components;
public:
	GameObject();
	~GameObject();
	Transform* transform;
	wstring name;
	bool isActive;
	int tag;
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();
	Component* AddComponent(Component* component);
	template <typename T>
	T* GetComponent();
	void MoveX(float x);
	void MoveY(float y);
	void Move(float x, float y);
	void OnEnable();
	void OnDisable();
	void OnCollision(GameObject* gameObject);
	void OnTriggerEnter(GameObject* gameObject);
	void OnTriggerStay(GameObject* gameObject);
	void OnTriggerExit(GameObject* gameObject);
	void SetActive(bool active);
};

//T* GetComponent : ������Ʈ�� �ִ� ������Ʈ�� ���ø��� ������Ʈ �����͸� ��ȯ
//	Dynamic_cast�� ���� ������Ʈ�� �ش� ������Ʈ�� �ִ��� �˻�.
//	�ش� ������Ʈ�� ���� ��� nullptr�� ��ȯ
template<typename T>
inline T* GameObject::GetComponent()
{
	for (int i = 0; i < component_num; i++) {
		T* result = dynamic_cast<T*>(components[i]);
		if (result != nullptr) {
			return result;
		}
	}
	return nullptr;
}
