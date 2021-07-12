#include "stdafx.h"
#include "Circle.h"

Circle::Circle()
	:center(), radius(0.f) {}

Circle::Circle(const float& x, const float& y, const float& radius)
	: center(x, y), radius(radius) {}

Circle::Circle(const Vector2& origin, const float& radius)
	: center(origin), radius(radius) {}
