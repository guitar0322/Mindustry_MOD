#pragma once
class GameObject;
class Transform;
class Component;

/************************************************************************************
* Component Pattern Framework - class GameObject
* Component들의 컨테이너 역할 및 기능을 실행시키는 주체
* by 홍대영
* up to date : 21-07-09
* 
* # Property @ Function
* # Transform* transform : 월드에서 기하학 정보를 담고있는 클래스(회전, 좌표, 크기 등)
* # bool isActive : 활성화 여부. false일 경우 Component의 기능을 수행하지 않음
* # int tag : 오브젝트 종류를 구분하기 위한 int형 변수. TAGMANAGER를 통해 관리
* # vector<Component*> components : 오브젝트에 추가되어 있는 Component 목록
* @ Function은 .cpp를 참고
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

//T* GetComponent : 오브젝트에 있는 컴포넌트중 템플릿형 컴포넌트 포인터를 반환
//	Dynamic_cast를 통해 오브젝트에 해당 컴포넌트가 있는지 검사.
//	해당 컴포넌트가 없을 경우 nullptr을 반환
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
