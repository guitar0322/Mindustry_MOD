#pragma once
namespace MyGeometry
{
	class Rect final
	{
	public:
		float left;
		float top;
		float right;
		float bottom;
		Pivot pivot;
	public:
		Rect();
		/***************************************
		explicit 키워드
		생성자에서 묵시적 형변환이 이루어지지 않도록 막아주는 역할
		****************************************/
		explicit Rect(const float& left, const float& top, const float& right, const float& bottom);
		explicit Rect(const int& left, const int& top, const int& right, const int& bottom);
		explicit Rect(const Vector2& pos, const Vector2& size, const Pivot& pivot);
		explicit Rect(const RECT& rc);

		const RECT GetRect();
		float GetWidth();
		float GetHeight();
		Vector2 GetCenter();
		Vector2 GetBottom();
		Vector2 GetSize();
		Vector2 GetPivot();
		void Remake(const Vector2& pos, const Vector2& size, const Pivot& pivot);
		void Move(const Vector2& moveValue);

		const Rect& operator=(const RECT& rc);
		const bool operator==(const Rect& rc);
		const bool operator==(const RECT& rc);
	};
}

