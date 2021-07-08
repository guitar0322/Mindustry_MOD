#pragma once
class GameObject;
class Transform;
class Component;
extern char debug[3][128];
extern char error[128];

class GameObject
{
private:
	int component_num;
	bool autoDisable;
	vector<Component*> components;
public:
	GameObject();
	~GameObject();
	Transform* transform;
	string name;
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

template<typename T>
inline T* GameObject::GetComponent()
{
	for (int i = 0; i < component_num; i++) {
		const char* inputClass = typeid(T*).name();
		T* result = dynamic_cast<T*>(components[i]);
		if (result != nullptr) {
			return result;
		}
	}
	return nullptr;
}
