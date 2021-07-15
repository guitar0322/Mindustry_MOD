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
�Ҽ��� ���� ����� �Ǵ��� ~1.f�Ǵ� 1.f ��ȯ
@@ float value : ��
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
��׸����� �������� ��ȯ�� ��ȯ
@@ float degree : ��׸���
**********************************************************/
 float Math::ToRadian(const float& degree)
{
	return degree * Math::Math::PI / 180.0f;
}
/**********************************************************
## ToDegree ##
������ ��׸��� ��ȯ�� ��ȯ
@@ float radian : ���� ��
**********************************************************/
 float Math::ToDegree(const float& radian)
{
	return radian * 180.0f / Math::Math::PI;
}

/**********************************************************
## Lerp ##
������ ���� �� ���� ���� �����ؼ� ��ȯ
@@ float val1 : ���� ��
@@ float val2 : ���� ��
@@ float amount : �� ���� ����, 0.0f ~ 1.0f ������ ���� ����.
**********************************************************/
 float Math::Lerp(const float& val1, const float& val2, const float& amount)
{
	return val1 + (val2 - val1) * amount;
}
/**********************************************************
## Clampf ##
��� ���� min,max���� ũ�ų� �۾������� �ϸ� min�Ǵ�max�� ��ȯ
@@ float value : ��
@@ float min : �ּ� ����
@@ float max : �ִ� ����
**********************************************************/
 float Math::Clampf(float value, const float& min, const float& max)
{
	value = value > max ? max : value;
	value = value < min ? min : value;

	return value;
}
/**********************************************************
## Clamp ##
��� ���� min,max���� ũ�ų� �۾������� �ϸ� min�Ǵ�max�� ��ȯ
@@ int value : ��
@@ int min : �ּ� ����
@@ int max : �ִ� ����
**********************************************************/
 int Math::Clamp(int value, const int& min, const int& max)
{
	value = value > max ? max : value;
	value = value < min ? min : value;

	return value;
}


/**********************************************************
## FloatToInt ##
@@ const float& f : int�� ����ȯ�� float
**********************************************************/
 int Math::FloatToInt(const float & f)
{
	return static_cast<int>(f + Math::Epsilon);
}
/**********************************************************
## FloatEqual ##
�� float�� �ε��Ҽ��� ���� ���� �ִ��� ��

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
�� �� ������ �Ÿ��� ���Ѵ�
@@ float startX : ������ X
@@ float startY : ������ y
@@ float endX : ��ǥ�� x
@@ float endY : ��ǥ�� y
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

