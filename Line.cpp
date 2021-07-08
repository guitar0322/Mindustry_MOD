#include "stdafx.h"
#include "Line.h"

Line::Line(const Vector2& start, const Vector2& end)
	: start(start), end(end) {}

//중심 점과 각도 기준으로
Line::Line(const Vector2& start, const float& angle, const float& dist)
	: start(start)
{
	end.x = cosf(angle) * dist;
	end.y = -sinf(angle) * dist;
}

void Line::Remake(const Vector2 & start, const Vector2 & end)
{
	this->start = start;
	this->end = end;
}

float Line::Length()
{
	return Vector2::Length(&(start - end));
}

bool Line::operator == (const Line& line)
{
	if (start == line.start && end == line.end)
		return true;
	if (start == line.end && end == line.start)
		return true;

	return false;
}

