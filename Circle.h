#pragma once
namespace MyGeometry 
{
	class Circle
	{
	public:
		Vector2 center;
		float radius;
	public:
		Circle();
		explicit Circle(const float& x, const float& y, const float& radius);
		explicit Circle(const Vector2& origin, const float& radius);
	};
}

