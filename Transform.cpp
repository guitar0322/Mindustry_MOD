#include "stdafx.h"
#include "Transform.h"
#include "GameObject.h"

Transform::Transform()
{
	position.x = WINSIZEX / 2;
	position.y = WINSIZEY / 2;
	size.x = 1.f;
	size.y = 1.f;
	angle = 0;
	siblingIdx = -1;
}

Transform::~Transform()
{

}
/***************************************************************
* float x : 가로 방향으로 움직일 거리
* float y : 세로 방향으로 움직일 거리
* MoeX, MoveY를 각각 호출
****************************************************************/
bool Transform::Move(float x, float y)
{
	bool result = true;
	result = MoveX(x);
	result = MoveY(y);
	return result;
}

/***************************************************************
* float x : 가로 방향으로 움직일 거리
* 모든 자식 오브젝트의 MoveX(x)를 호출
* 자신의 위치를 변경한 후 충돌 체크 함수 호출
****************************************************************/
bool Transform::MoveX(float x)
{
	int childCount = GetChildCount();
	for (int i = 0; i < childCount; i++) {
		child[i]->MoveX(x);
	}
	position.x += x;
	if (CheckCollision() == true) {
		return false;
	}
	return true;
}

bool Transform::MoveY(float y)
{
	int childCount = GetChildCount();
	for (int i = 0; i < childCount; i++) {
		child[i]->MoveY(y);
	}
	position.y += y;
	if (CheckCollision() == true) {
		return false;
	}
	return true;
}

/**************************************************************
* 오브젝트를 회전
* 결과 angle값이 음수가 되거나 360보다 커지면 0~360의 값으로 보정
***************************************************************/
void Transform::Rotate(float degree)
{
	angle += degree;
	if (angle < 0.f)
		angle = 360 - (-angle);
	if (angle > 360.f)
		angle -= 360.f;
}

/***************************************************************
* 움직인 후 충돌 여부를 체크
* BoxCollider 컴포넌트가 없다면 충돌체크를 수행하지 않음
* BoxColldier에서 충돌 연산에 의해 겹쳐진 만큼 Move함수가 다시 호출
****************************************************************/
bool Transform::CheckCollision()
{
	BoxCollider* collider;
	collider = gameObject->GetComponent<BoxCollider>();
	if (collider == nullptr) {
		return false;
	}
	else {
		return collider->CheckCollision();
	}
	return false;
}

/***************************************************************
* int i : 가져올 자식 오브젝트의 인덱스
* 자식 오브젝트의 Transform* 를 반환
****************************************************************/
Transform* Transform::GetChild(int i)
{
	if (i >= GetChildCount()) {
		return nullptr;
	}
	else {
		return child[i];
	}
}

/***************************************************************
* GameObject* gameObject : 자식 오브젝트의 포인터
* 자식오브젝트 목록에 추가
****************************************************************/
void Transform::AddChild(GameObject* gameObject)
{
	child.push_back(gameObject->transform);
	gameObject->transform->parent = this;
	gameObject->transform->siblingIdx = GetChildCount() - 1;
}

/***************************************************************
* GameObject* gameObject : 자식 오브젝트의 Transform 포인터
* 자식오브젝트 목록에 추가
****************************************************************/
void Transform::AddChild(Transform* transform)
{
	child.push_back(transform);
	transform->parent = this;
	transform->siblingIdx = GetChildCount() - 1;
}

/***************************************************************
* int idx : 제거할 자식 오브젝트 인덱스
* idx번째 자식 오브젝트와의 연결을 해제
****************************************************************/
void Transform::DetachChild(int idx)
{
	if (idx > GetChildCount() - 1)
	{
		throw "자식삭제 idx가 옳지 않습니다";
		return;
	}
	child[idx]->parent = nullptr;
	child[idx]->siblingIdx = -1;
	child.erase(child.begin() + idx);
}

/***************************************************************
* 부모와의 연결을 해제
* 부모의 DetachChild() 함수 호출
****************************************************************/
void Transform::DetachParent()
{
	if (parent == nullptr) {
		sprintf_s(error, "DetachParent오류 : 부모 오브젝트가 존재하지 않습니다");
		throw "부모 오브젝트가 존재하지 않습니다";
		return;
	}
	parent->DetachChild(siblingIdx);
}
