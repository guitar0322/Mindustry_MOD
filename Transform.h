#pragma once
#include <vector>
#include "Vector2.h"
using namespace std;

class GameObject;

/************************************************************************
* Framework Transform
*	월드에서 오브젝트의 기하학 정보를 담고 있는 클래스(좌표, 회전, 크기 등)
*	부모, 자식 오브젝트의 연결고리
* by 홍대영
* up to date : 21-07-09
* #Property @Function
* # Vector2 position : 월드에서 오브젝트의 x,y 위치정보
* # Vector2 size : 월드에서 오브젝트의 가로 세로 크기 비율
* # float angle : 오브젝트이 rotation값
* # vector<Transform*> child : 자식 오브젝트 목록
* # Transform* parent : 부모 오브젝트의 Transform 포인터
* # GameObject* gameObject : Transform을 소유하고 있는 오브젝트 포인터
* # int siblingIdx : 부모 오브젝트 기준 자기 자신의 자식 목록 인덱스
* @ Function은 cpp를 참고
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
	* angle : 오브젝트의 회전값
	* GetAngle을 통해 각도를 정할 경우 ConvertAngleD2D함수를
	* 통해 변환을 거친후 호출해야한다
	******************************************************/
	void SetAngle(float angle) { this->angle = angle; }
	float GetAngle() const { return angle; }
};

