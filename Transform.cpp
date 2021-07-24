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
* float x : ���� �������� ������ �Ÿ�
* float y : ���� �������� ������ �Ÿ�
* MoeX, MoveY�� ���� ȣ��
****************************************************************/
bool Transform::Move(float x, float y)
{
	bool result = true;
	result = MoveX(x);
	result = MoveY(y);
	return result;
}

/***************************************************************
* float x : ���� �������� ������ �Ÿ�
* ��� �ڽ� ������Ʈ�� MoveX(x)�� ȣ��
* �ڽ��� ��ġ�� ������ �� �浹 üũ �Լ� ȣ��
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
* ������Ʈ�� ȸ��
* ��� angle���� ������ �ǰų� 360���� Ŀ���� 0~360�� ������ ����
***************************************************************/
void Transform::Rotate(float degree)
{
	int childCount = GetChildCount();
	for (int i = 0; i < childCount; i++) {
		child[i]->Rotate(degree);
	}
	angle += degree;
	if (angle < 0.f)
		angle = 360 + angle;
	if (angle >= 360.f)
		angle -= 360.f;
}

/***************************************************************
* ������ �� �浹 ���θ� üũ
* BoxCollider ������Ʈ�� ���ٸ� �浹üũ�� �������� ����
* BoxColldier���� �浹 ���꿡 ���� ������ ��ŭ Move�Լ��� �ٽ� ȣ��
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
* int i : ������ �ڽ� ������Ʈ�� �ε���
* �ڽ� ������Ʈ�� Transform* �� ��ȯ
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
* GameObject* gameObject : �ڽ� ������Ʈ�� ������
* �ڽĿ�����Ʈ ��Ͽ� �߰�
****************************************************************/
void Transform::AddChild(GameObject* gameObject)
{
	child.push_back(gameObject->transform);
	gameObject->transform->parent = this;
	gameObject->transform->siblingIdx = GetChildCount() - 1;
}

/***************************************************************
* GameObject* gameObject : �ڽ� ������Ʈ�� Transform ������
* �ڽĿ�����Ʈ ��Ͽ� �߰�
****************************************************************/
void Transform::AddChild(Transform* transform)
{
	child.push_back(transform);
	transform->parent = this;
	transform->siblingIdx = GetChildCount() - 1;
}

/***************************************************************
* int idx : ������ �ڽ� ������Ʈ �ε���
* idx��° �ڽ� ������Ʈ���� ������ ����
****************************************************************/
void Transform::DetachChild(int idx)
{
	if (idx > GetChildCount() - 1)
	{
		throw "�ڽĻ��� idx�� ���� �ʽ��ϴ�";
		return;
	}
	child[idx]->parent = nullptr;
	child[idx]->siblingIdx = -1;
	child.erase(child.begin() + idx);
}

/***************************************************************
* �θ���� ������ ����
* �θ��� DetachChild() �Լ� ȣ��
****************************************************************/
void Transform::DetachParent()
{
	if (parent == nullptr) {
		sprintf_s(error, "DetachParent���� : �θ� ������Ʈ�� �������� �ʽ��ϴ�");
		throw "�θ� ������Ʈ�� �������� �ʽ��ϴ�";
		return;
	}
	parent->DetachChild(siblingIdx);
}
