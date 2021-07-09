#include "stdafx.h"
#include "utils.h"

namespace HDY_UTIL
{
	float GetDistance(Vector2 v1, Vector2 v2)
	{
		float deltaX = v1.x - v2.y;
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
	float GetAngle(float x1, float y1, float x2, float y2)
	{
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
	POINTF MoveTowardTo(float x1, float y1, float x2, float y2, float speed, int limit)
	{
		float angle = GetAngle(x1, y1, x2, y2);
		float nextX, nextY;
		float distance;
		distance = GetDistance(x1, y1, x2, y2);
		float remain = distance - limit;
		if (remain > speed) {
			nextX = x1 + cosf(angle) * speed;
			nextY = y1 - sinf(angle) * speed;
		}
		else {
			nextX = x1 + cosf(angle) * remain;
			nextY = y1 - sinf(angle) * remain;
		}
		return { nextX, nextY };
	}
	POINTF MoveTowardTo(RECT& rc1, RECT& rc2, float speed, int limit)
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
		return { nextX, nextY };
	}
	template<typename T>
	T GetCenter(T a, T b)
	{
		return (a + b) / 2;
	}
}