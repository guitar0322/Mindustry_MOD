#pragma once
#include <vector>
#include "Vector2.h"
using namespace std;

class GameObject;

/************************************************************************
* Framework Transform
*	���忡�� ������Ʈ�� ������ ������ ��� �ִ� Ŭ����(��ǥ, ȸ��, ũ�� ��)
*	�θ�, �ڽ� ������Ʈ�� �����
* by ȫ�뿵
* up to date : 21-07-09
* #Property @Function
* # Vector2 position : ���忡�� ������Ʈ�� x,y ��ġ����
* # Vector2 size : ���忡�� ������Ʈ�� ���� ���� ũ�� ����
* # float angle : ������Ʈ�� rotation��
* # vector<Transform*> child : �ڽ� ������Ʈ ���
* # Transform* parent : �θ� ������Ʈ�� Transform ������
* # GameObject* gameObject : Transform�� �����ϰ� �ִ� ������Ʈ ������
* # int siblingIdx : �θ� ������Ʈ ���� �ڱ� �ڽ��� �ڽ� ��� �ε���
* @ Function�� cpp�� ����
*************************************************************************/
class Transform
{
	typedef struct tagPOSITION {
		float x;
		float y;
	}POSITION;
	typedef struct tagScale {
		int width;
		int height;
	}SCALE;
	
public:
	Transform();
	~Transform();
	Vector2 position;
	Vector2 size;
	float angle;
	vector<Transform*> child;
	Transform* parent;
	GameObject* gameObject;
	int siblingIdx;
	bool Move(float x, float y);
	bool MoveX(float x);
	bool MoveY(float y);
	void Rotate(float degree);
	bool CheckCollision();
	int GetChildCount() { return child.size(); }
	Transform* GetChild(int i);
	void AddChild(GameObject* gameObject);
	void AddChild(Transform* transform);
	void DetachChild(int idx);
	void DetachParent();

	void SetX(float x) { position.x = x; }
	void SetY(float y) { position.y = y; }
	void SetPosition(float x, float y) { position.x = x; position.y = y; }
	void SetPosition(Vector2 position) { this->position = position; }
	float GetX() { return position.x; }
	float GetY() { return position.y; }

	void SetScaleX(float scaleX) { size.x = scaleX; }
	void SetScaleY(float scaleY) { size.y = scaleY; }
	void SetScale(float scaleX, float scaleY) { size.x = scaleX, size.y = scaleY; }
	float GetScaleX() { return size.x; }
	float GetScaleY() { return size.y; }

	/******************************************************
	* angle : ������Ʈ�� ȸ����
	* GetAngle�� ���� ������ ���� ��� ConvertAngleD2D�Լ���
	* ���� ��ȯ�� ��ģ�� ȣ���ؾ��Ѵ�
	******************************************************/
	void SetAngle(float angle) { this->angle = angle; }
	float GetAngle() const { return angle; }
};

