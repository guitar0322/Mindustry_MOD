#pragma once
#include "Transform.h"
class GameObject;
/***************************************************************************
* Component pattern Framework
* by 홍대영
* up to date : 21-07-09
* # Property @Function
* # GameObject* gameObject : Component를 소유하고 있는 GameObject 인스턴스
* # Transform* transform : gameObject의 transform인스턴스
* 
* @ void Render : 렌더링과 관련된 코드를 매 프레임마다 실행
* 
* @ void Update : 연산과 관련된 코드를 매 프레임마다 실행
* 
* @ OnEnable : gameObject가 활성화 됐을때 한번 호출
* 
* @ OnDisable : gameObject가 비활성화 됐을때 한번 호출
* 
* @ OnCollision(GameObject* gameObject) : 충돌이 발생했을때 호출
*	gameObject : 충돌한 대상 오브젝트 포인터
* 
* @ OnTriggerEnter(GameObject* gameObject) : 겹침 이벤트가 발생했을때 한번 호출
*	gameObject : 충돌영역에 들어온 대상 오브젝트 포인터
* 
* @ OnTriggerStay(GameObject* gameObject) : 겹침 이벤트가 유지될때 프레임마다 호출
*	gameObject : 충돌영역에 겹쳐져있는 대상 오브젝트 포인터
* 
* @ OnTriggerExit(GameObject* gameObject) : 겹침 이벤트가 종료될때 한번 호출
*	gameObject : 충돌영역에서 벗어난 대상 오브젝트 포인터
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