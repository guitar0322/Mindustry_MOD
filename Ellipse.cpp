#include "stdafx.h"
#include "Ellipse.h"

Ellipse::Ellipse()
	:center(), radius(0.f) {}

Ellipse::Ellipse(const float& x, const float& y, const float& radius)
	: center(x, y), radius(radius) {}

Ellipse::Ellipse(const Vector2& origin, const float& radius)
	: center(origin), radius(radius) {}
