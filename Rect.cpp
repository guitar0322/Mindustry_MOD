#include "stdafx.h"
#include "Rect.h"

Rect::Rect()
	:left(0.f), top(0.f), right(0.f), bottom(0.f) {}

Rect::Rect(const float& left, const float& top, const float& right, const float& bottom)
	: left(left), top(top), right(right), bottom(bottom) {}

Rect::Rect(const int& left, const int& top, const int& right, const int& bottom)
	: left((float)left), top((float)top), right((float)right), bottom((float)bottom) {}

Rect::Rect(const Vector2& pos, const Vector2& size, const Pivot& pivot)
{
	*this = RectMakePivot(pos, size, pivot);
	this->pivot = pivot;
}

Rect::Rect(const RECT& rc)
	:left((float)rc.left), top((float)rc.top), right((float)rc.right), bottom((float)rc.bottom) {}

//사용자 정의 Rect를 WINAPI RECT로 변환하여 반환
const RECT Rect::GetRect()
{
	return { (LONG)left,(LONG)top,(LONG)right,(LONG)bottom };
}

float Rect::GetWidth()
{
	return right - left;
}

float Rect::GetHeight()
{
	return bottom - top;
}

Vector2 Rect::GetCenter()
{
	return Vector2(left + (right - left) / 2.f, top + (bottom - top) / 2.f);
}

Vector2 Rect::GetBottom()
{
	return Vector2(left + (right - left) / 2.f, bottom);
}

Vector2 Rect::GetSize()
{
	return Vector2((right - left), (bottom - top));
}

Vector2 Rect::GetPivot()
{
	Vector2 result;
	switch (pivot)
	{
	case Pivot::LeftTop:
		result.x = left;
		result.y = top;
		break;
	case Pivot::Center:
		result.x = (left + right) / 2;
		result.y = (top + bottom) / 2;
		break;
	case Pivot::BottomCenter:
		result.x = (left + right) / 2;
		result.y = bottom;
		break;
	}
	return result;
}

void Rect::Remake(const Vector2& pos, const Vector2& size, const Pivot& pivot)
{
	*this = ::RectMakePivot(pos, size, pivot);
}

void Rect::Move(const Vector2& moveValue)
{
	left += moveValue.x;
	right += moveValue.x;
	top += moveValue.y;
	bottom += moveValue.y;
}

const Rect& Rect::operator=(const RECT& rc)
{
	this->left = (float)rc.left;
	this->right = (float)rc.right;
	this->top = (float)rc.top;
	this->bottom = (float)rc.bottom;
	return *this;
}

const bool Rect::operator==(const Rect& rc)
{
	if (this->left != rc.left) return false;
	if (this->right != rc.right) return false;
	if (this->top != rc.top) return false;
	if (this->bottom != rc.bottom) return false;
	return true;
}

const bool Rect::operator==(const RECT& rc)
{
	if (this->left != rc.left) return false;
	if (this->right != rc.right) return false;
	if (this->top != rc.top) return false;
	if (this->bottom != rc.bottom) return false;
	return true;
}
