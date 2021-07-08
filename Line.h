#pragma once
/****************************************************************************
# Geometry::Line ##

*****************************************************************************/
namespace MyGeometry
{
	typedef class Line final
	{
	private:
		enum { MaxRayRange = 1000 };
	public:
		Vector2 start;
		Vector2 end;

		Line() {}
		explicit Line(const Vector2& start, const Vector2& end);
		explicit Line(const Vector2& start, const float& angle, const float& dist = (float)MaxRayRange);

		void Remake(const Vector2& start, const Vector2& end);
		float Length();
		bool operator == (const Line& line);
	};
}