#pragma once
namespace MyGeometry 
{
	class Ellipse
	{
	public:
		Vector2 center;
		float radius;
	public:
		Ellipse();
		explicit Ellipse(const float& x, const float& y, const float& radius);
		explicit Ellipse(const Vector2& origin, const float& radius);
	};
}

