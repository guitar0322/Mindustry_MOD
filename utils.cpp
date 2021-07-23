#include "stdafx.h"
#include "utils.h"

namespace HDY_UTIL
{
	/*****************************************************
	* ���� Winapi������ ������ GetAngle(����)����
	* D2D Angle(��׸�)�� ��ȯ���ִ� �Լ�
	* const float& angle : ���� ����
	*****************************************************/
	float ConvertAngleD2D(const float& angle)
	{
		float degree = Math::ToDegree(angle);
		float result = 90.f - degree;
		if (result < 0)
		{
			result += 360;
		}
		return result;
	}
	
	/*****************************************************
	* D2D Angle(��׸�)����
	* WinApi(����) �ޱ۷� ��ȯ
	* const float& angle : ��׸� ����
	*****************************************************/
	float ConvertAngleAPI(const float& angle)
	{
		float radian = Math::ToRadian(angle);
		radian = radian - Math::PI / 2;
		float result = Math::PI2 - radian;
		if (result >= Math::PI2)
		{
			result -= Math::PI2;
		}

		return result;
	}

	float GetDistance(const Vector2& v1, const Vector2& v2)
	{
		float deltaX = v1.x - v2.x;
		float deltaY = v1.y - v2.y;
		return sqrtf(deltaX * deltaX + deltaY * deltaY);
	}

	float GetDistance(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		return sqrtf(x * x + y * y);
	}

	template <typename T>
	T GetDistance(T a, T b) {
		return a - b;
	}

	float GetAngle(float x1, float y1, float x2, float y2)  	{
		float x = x2 - x1;
		float y = y2 - y1;

		float distance = sqrtf(x * x + y * y);

		//�ڽ����� ��ġ���� ������      �̺κ��� �ڽ���
		float angle = acosf(x / distance);

		//��ſ� Y�� ������ ������
		if (y2 > y1)
		{
			angle = Math::PI2 - angle;
			if (angle >= Math::PI2) angle -= Math::PI2;
		}
		
		return angle;
	}

	float GetAngle(Vector2& v1, Vector2& v2)
	{
		float deltaX = v2.x - v1.x;
		float deltaY = v2.y - v1.y;
		
		float distance = sqrtf(deltaX * deltaX + deltaY * deltaY);

		float angle = acosf(deltaX / distance);

		if (v2.y > v1.y)
		{
			angle = Math::PI2 - angle;
			if (angle >= Math::PI2) angle -= Math::PI2;
		}
		return angle;
	}

	float GetAngleDegree(float x1, float y1, float x2, float y2)
	{
		return Math::ToDegree(GetAngle(x1, y1, x2, y2));
	}
	
	float GetAngleDegree(Vector2& v1, Vector2& v2)
	{
		return Math::ToDegree(GetAngle(v1,v2));
	}

	Vector2 WorldToScreen(Vector2 worldPoint)
	{
		Vector2 result;
		if (MainCam == nullptr)
			throw("ī�޶� �Ҵ���� �ʾҽ��ϴ�");
		result.x = worldPoint.x - (MainCam->transform->GetX() - MainCam->GetRenderWidth() / 2);
		result.y = worldPoint.y - (MainCam->transform->GetY() - MainCam->GetRenderHeight() / 2);
		return result;
	}

	Vector2 WorldToScreen(float x, float y)
	{
		Vector2 result;
		if (MainCam == nullptr)
			throw("ī�޶� �Ҵ���� �ʾҽ��ϴ�");
		result.x = x - (MainCam->transform->GetX() - MainCam->GetRenderWidth() / 2);
		result.y = y - (MainCam->transform->GetY() - MainCam->GetRenderHeight() / 2);
		return result;
	}

	Vector2 ScreenToWorld(Vector2 screenPoint)
	{
		Vector2 result;
		float worldX = MainCam->GetRenderWidth() * (screenPoint.x - MainCam->GetScreenStart().first) / MainCam->GetScreenWidth();
		float worldY = MainCam->GetRenderHeight() * (screenPoint.y - MainCam->GetScreenStart().second) / MainCam->GetScreenHeight();
		result.x = MainCam->GetCameraStartX() + worldX;
		result.y = MainCam->GetCameraStartY() + worldY;
		return result;
	}

	Vector2 ScreenToWorld(float x, float y)
	{
		Vector2 result;
		float worldX = MainCam->GetRenderWidth() / MainCam->_zoomScale * (x - MainCam->GetScreenStart().first) / MainCam->GetScreenWidth();
		float worldY = MainCam->GetRenderHeight() / MainCam->_zoomScale * (y - MainCam->GetScreenStart().second) / MainCam->GetScreenHeight();
		result.x = MainCam->GetCameraStartX() + worldX;
		result.y = MainCam->GetCameraStartY() + worldY;
		return result;
	}

	POINTF GetCenterF(RECT rc)
	{
		return { (float)GetCenter(rc.left, rc.right) , (float)GetCenter(rc.top, rc.bottom) };
	}
	int GetWidth(RECT rc)
	{
		return GetDistance(rc.right, rc.left);
	}
	int GetHeight(RECT rc)
	{
		return GetDistance(rc.bottom, rc.top);
	}
	Vector2 MoveTowardTo(float x1, float y1, float x2, float y2, float speed, int limit)
	{
		float angle = GetAngle(x1, y1, x2, y2);
		float nextX, nextY;
		float distance;
		distance = GetDistance(x1, y1, x2, y2);
		float remain = distance - limit;
		if (remain > speed) 
		{
			nextX = x1 + cosf(angle) * speed;
			nextY = y1 - sinf(angle) * speed;
		}
		else 
		{
			nextX = x1 + cosf(angle) * remain;
			nextY = y1 - sinf(angle) * remain;
		}
		return Vector2(nextX, nextY);
	}

	Vector2 MoveTowardTo(Transform* moveTr, Transform* targetTr, float speed, float limit)
	{
		float angle = GetAngle(moveTr->GetX(), moveTr->GetY(), targetTr->GetX(), targetTr->GetY());
		float nextX, nextY;
		float distance;
		distance = GetDistance(moveTr->GetX(), moveTr->GetY(), targetTr->GetX(), targetTr->GetY());
		float remain = distance - limit;
		if (remain > speed)
		{
			nextX = moveTr->GetX() + cosf(angle) * speed;
			nextY = moveTr->GetY() - sinf(angle) * speed;
		}
		else
		{
			nextX = moveTr->GetX() + cosf(angle) * remain;
			nextY = moveTr->GetY() - sinf(angle) * remain;
		}
		moveTr->Move(cosf(angle) * speed, -sinf(angle) * speed);

		return Vector2(nextX, nextY);
	}

	Vector2 MoveTowardTo(Transform* moveTr, float x2, float y2, float speed, float limit)
	{
		float angle = GetAngle(moveTr->GetX(), moveTr->GetY(), x2, y2);
		float nextX, nextY;
		float distance;
		distance = GetDistance(moveTr->GetX(), moveTr->GetY(), x2, y2);
		float remain = distance - limit;
		if (remain > speed)
		{
			nextX = moveTr->GetX() + cosf(angle) * speed;
			nextY = moveTr->GetY() - sinf(angle) * speed;
		}
		else
		{
			nextX = moveTr->GetX() + cosf(angle) * remain;
			nextY = moveTr->GetY() - sinf(angle) * remain;
		}
		moveTr->Move(cosf(angle) * speed, -sinf(angle) * speed);

		return Vector2(nextX, nextY);
	}

	Vector2 MoveTowardTo(RECT& rc1, RECT& rc2, float speed, int limit)
	{
		POINTF center1 = GetCenterF(rc1);
		POINTF center2 = GetCenterF(rc2);
		float angle = GetAngle(center1.x, center1.y, center2.x, center2.y);
		float distance = GetDistance(center1.x, center1.y, center2.x, center2.y);
		float nextX, nextY;
		float remain = distance - limit;
		if (remain > speed) {
			nextX = center1.x + cosf(angle) * speed;
			nextY = center1.y - sinf(angle) * speed;
		}
		else {
			nextX = center1.x + cosf(angle) * remain;
			nextY = center1.y - sinf(angle) * remain;
		}
		rc1 = RectMakeCenter(nextX, nextY, GetWidth(rc1), GetHeight(rc1));
		return Vector2(nextX, nextY);
	}
	template<typename T>
	T GetCenter(T a, T b)
	{
		return (a + b) / 2;
	}
}