#include "stdafx.h"
#include "Math.h"

const float Math::PI = 3.14159265f;
const float Math::PI2 = Math::PI * 2;
const float Math::Epsilon = 1E-6f;
const int Math::IntMin = -2147483647;
const int Math::IntMax = 2147483647;
const float Math::FloatMin = -3.402823E+38f;
const float Math::FloatMax = 3.402823E+38f;
/**********************************************************
## NegativeChecking ##
소수의 음수 양수를 판단해 ~1.f또는 1.f 반환
@@ float value : 값
**********************************************************/
 float Math::NegativeChecking(const float& value)
{
	if (value < 0.0f)
		return -1.0f;
	else
		return 1.0f;
}

/**********************************************************
## ToRadian ##
디그리값을 라디안으로 변환해 반환
@@ float degree : 디그리값
**********************************************************/
 float Math::ToRadian(const float& degree)
{
	return degree * Math::Math::PI / 180.0f;
}
/**********************************************************
## ToDegree ##
라디안을 디그리로 변환해 반환
@@ float radian : 라디안 값
**********************************************************/
 float Math::ToDegree(const float& radian)
{
	return radian * 180.0f / Math::Math::PI;
}

/**********************************************************
## Lerp ##
비율을 통해 두 값을 선형 보간해서 반환
@@ float val1 : 시작 값
@@ float val2 : 도달 값
@@ float amount : 두 값의 비율, 0.0f ~ 1.0f 사이의 값이 들어간다.
**********************************************************/
 float Math::Lerp(const float& val1, const float& val2, const float& amount)
{
	return val1 + (val2 - val1) * amount;
}
/**********************************************************
## Clampf ##
어떠한 값이 min,max보다 크거나 작아지려고 하면 min또는max를 반환
@@ float value : 값
@@ float min : 최소 범위
@@ float max : 최대 범위
**********************************************************/
 float Math::Clampf(float value, const float& min, const float& max)
{
	value = value > max ? max : value;
	value = value < min ? min : value;

	return value;
}
/**********************************************************
## Clamp ##
어떠한 값이 min,max보다 크거나 작아지려고 하면 min또는max를 반환
@@ int value : 값
@@ int min : 최소 범위
@@ int max : 최대 범위
**********************************************************/
 int Math::Clamp(int value, const int& min, const int& max)
{
	value = value > max ? max : value;
	value = value < min ? min : value;

	return value;
}


/**********************************************************
## FloatToInt ##
@@ const float& f : int로 형변환할 float
**********************************************************/
 int Math::FloatToInt(const float & f)
{
	return static_cast<int>(f + Math::Epsilon);
}
/**********************************************************
## FloatEqual ##
두 float이 부동소수점 오차 내에 있는지 비교

@@ const float& f1 : float 1
@@ const float& f2 : float 2
**********************************************************/
 bool Math::FloatEqual(const float & f1, const float & f2)
{
	return (fabs(f1 - f2) <= Math::Epsilon);
}

float Math::FixFloat(float f)
{
	return ((int)(f * pow(10.0f, 3))) / pow(10.0f, 3);
}

/*********************************************************************
## GetDistance ##
두 점 사이의 거리를 구한다
@@ float startX : 시작점 X
@@ float startY : 시작점 y
@@ float endX : 목표점 x
@@ float endY : 목표점 y
**********************************************************************/
 float Math::GetDistance(const float& startX, const float& startY, const float& endX, const float& endY)
{
	float x = endX - startX;
	float y = endY - startY;

	return sqrt(x * x + y * y);
}

float Math::Floor(const float & f, const int & cipher)
{
	int tempCipher = 10;
	for (int i = 0; i < cipher;++i)
		tempCipher *= 10;
	float result = std::floorf(((f + Math::Epsilon) * (float)tempCipher)) / (float)tempCipher;
	return result;
}

