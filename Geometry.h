#pragma once
#include "Rect.h"
#include "Circle.h"
/**********************************
Framework Geometry
By ȫ�뿵 21/07/05
***********************************/
namespace MyGeometry 
{
	inline Vector2 GetCenter(Rect rect)
	{
		Vector2 result;
		result.x = (rect.right + rect.left) / 2;
		result.y = (rect.bottom + rect.top) / 2;
		return result;
	}

	inline float GetCenterX(Rect rect)
	{
		return (rect.right + rect.left) / 2;
	}
	inline float GetCenterY(Rect rect)
	{
		return (rect.top + rect.bottom) / 2;
	}
	/**********************************************
	������ 3������ �������� �簢���� ����
	***********************************************/
	inline Rect RectMakePivot(const Vector2& pos, const Vector2& size, const Pivot& pivot)
	{
		Rect result;
		switch (pivot)
		{
		case Pivot::LeftTop:
			result.left = pos.x;
			result.top = pos.y;
			result.right = pos.x + size.x;
			result.bottom = pos.y + size.y;
			break;
		case Pivot::Center:
			result.left = pos.x - size.x / 2.f;
			result.top = pos.y - size.y / 2.f;
			result.right = pos.x + size.x / 2.f;
			result.bottom = pos.y + size.y / 2.f;
			break;
		case Pivot::BottomCenter:
			result.left = pos.x - size.x / 2.f;
			result.top = pos.y - size.y;
			result.right = pos.x + size.x / 2.f;
			result.bottom = pos.y;
			break;
		}
		return result;
	}

	inline Rect RectMakeCenter(const Vector2& pos, const Vector2& size)
	{
		Rect result;
		result.left = pos.x - size.x / 2.f;
		result.top = pos.y - size.y / 2.f;
		result.right = pos.x + size.x / 2.f;
		result.bottom = pos.y + size.y / 2.f;
		return result;
	}
	inline RECT RectMakeCenter(int x, int y, int width, int height)
	{
		RECT result;
		result.left = x - width / 2;
		result.top = y - height / 2;
		result.right = x + width / 2;
		result.bottom = y + height / 2;
		return result;
	}
	inline RECT RectMake(int x, int y, int width, int height)
	{
		RECT result;
		result.left = x;
		result.top = y;
		result.right = x + width;
		result.bottom = y + height;
		return result;
	}

	/****************************************
	## IntersectRect ##
	Rect* rc1 : ��Ʈ 1
	Rect* rc2 : ��Ʈ 2
	return bool :  true�� ��ħ false�� �Ȱ�ħ
	*****************************************/
	inline bool IntersectRect(const Rect* const rc1, const Rect* const rc2)
	{
		if (rc1->right <= rc2->left || rc1->left >= rc2->right) return false;
		if (rc1->bottom <= rc2->top || rc1->top >= rc2->bottom) return false;
		return true;
	}

	/*****************************
	## IntersectRect ##
	Rect* result : �浹 ���� ��ȯ
	******************************/
	inline bool IntersectRect(Rect* const result, const Rect* const rc1, const Rect* const rc2)
	{
		if (IntersectRect(rc1, rc2) == false)
			return false;
		if (result != nullptr)
		{
			result->left = Math::Max(rc1->left, rc2->left);
			result->right = Math::Min(rc1->right, rc2->right);
			result->top = Math::Max(rc1->top, rc2->top);
			result->bottom = Math::Min(rc1->bottom, rc2->bottom);
		}
		return true;
	}

	/*******************************************
	## IntersectRect ##
	rcHold : ������ �ִ� ��Ʈ
	rcMove : ������ ��Ʈ
	Enum* pOutput : rcMove�� ����� ������ ��ȯ
	********************************************/
	inline bool IntersectRect(const Rect* const rcHold, const Rect* const rcMove, Direction::Enum* pOutput)
	{
		Rect intersectRc;

		if (IntersectRect(&intersectRc, rcHold, rcMove) == false)
			return false;

		float interW = intersectRc.right - intersectRc.left;
		float interH = intersectRc.bottom - intersectRc.top;

		if (Math::FloatEqual(interW, interH))
		{
			if (Math::FloatEqual(intersectRc.left, rcHold->left))
			{
				if (pOutput)
					*pOutput = (Direction::Enum)((*pOutput) | Direction::Right);
			}
			else if (Math::FloatEqual(intersectRc.right, rcHold->right))
			{
				if (pOutput)
					*pOutput = (Direction::Enum)((*pOutput) | Direction::Left);
			}
			//��
			if (Math::FloatEqual(intersectRc.top, rcHold->top))
			{
				if (pOutput)
					*pOutput = (Direction::Enum)((*pOutput) | Direction::Bottom);
			}
			//�Ʒ�
			else if (Math::FloatEqual(intersectRc.bottom, rcHold->bottom))
			{
				if (pOutput)
					*pOutput = (Direction::Enum)((*pOutput) | Direction::Top);
			}
		}
		else if (interW < interH)
		{
			if (Math::FloatEqual(intersectRc.left, rcHold->left))
			{
				if (pOutput)
					*pOutput = (Direction::Enum)((*pOutput) | Direction::Right);
			}
			else if (Math::FloatEqual(intersectRc.right, rcHold->right))
			{
				if (pOutput)
					*pOutput = (Direction::Enum)((*pOutput) | Direction::Left);
			}

		}
		else
		{
			//��
			if (Math::FloatEqual(intersectRc.top, rcHold->top))
			{
				if (pOutput)
					*pOutput = (Direction::Enum)((*pOutput) | Direction::Bottom);
			}
			//�Ʒ�
			else if (Math::FloatEqual(intersectRc.bottom, rcHold->bottom))
			{
				if (pOutput)
					*pOutput = (Direction::Enum)((*pOutput) | Direction::Top);
			}
		}

		return true;
	}

	/******************************************************
	## IntersectRectReaction ##
	rcMove�� ������ ������ ��ȯ�ϰ� �浹�ϱ� �� ���·� �о
	*******************************************************/
	inline bool IntersectRectReaction(Rect* const rcMove, const Rect* const rcHold, Direction::Enum* const pOutDirection = nullptr)
	{
		Rect intersectRc;

		if (IntersectRect(&intersectRc, rcHold, rcMove) == false)
			return false;

		float interW = intersectRc.right - intersectRc.left;
		float interH = intersectRc.bottom - intersectRc.top;

		if (Math::FloatEqual(interW, interH))
		{
			if (Math::FloatEqual(intersectRc.left, rcHold->left))
			{
				rcMove->left -= interW;
				rcMove->right -= interW;
				if (pOutDirection)
					*pOutDirection = (Direction::Enum)((*pOutDirection) | Direction::Right);
			}
			else if (Math::FloatEqual(intersectRc.right, rcHold->right))
			{
				rcMove->left += interW;
				rcMove->right += interW;
				if (pOutDirection)
					*pOutDirection = (Direction::Enum)((*pOutDirection) | Direction::Left);
			}
			//��
			if (Math::FloatEqual(intersectRc.top, rcHold->top))
			{
				rcMove->top -= interH;
				rcMove->bottom -= interH;
				if (pOutDirection)
					*pOutDirection = (Direction::Enum)((*pOutDirection) | Direction::Bottom);
			}
			//�Ʒ�
			else if (Math::FloatEqual(intersectRc.bottom, rcHold->bottom))
			{
				rcMove->top += interH;
				rcMove->bottom += interH;
				if (pOutDirection)
					*pOutDirection = (Direction::Enum)((*pOutDirection) | Direction::Top);
			}
		}
		else if (interW < interH)
		{
			if (Math::FloatEqual(intersectRc.left, rcHold->left))
			{
				rcMove->left -= interW;
				rcMove->right -= interW;
				if (pOutDirection)
					*pOutDirection = (Direction::Enum)((*pOutDirection) | Direction::Right);
			}
			else if (Math::FloatEqual(intersectRc.right, rcHold->right))
			{
				rcMove->left += interW;
				rcMove->right += interW;
				if (pOutDirection)
					*pOutDirection = (Direction::Enum)((*pOutDirection) | Direction::Left);
			}

		}
		else
		{
			//��
			if (Math::FloatEqual(intersectRc.top, rcHold->top))
			{
				rcMove->top -= interH;
				rcMove->bottom -= interH;
				if (pOutDirection)
					*pOutDirection = (Direction::Enum)((*pOutDirection) | Direction::Bottom);
			}
			//�Ʒ�
			else if (Math::FloatEqual(intersectRc.bottom, rcHold->bottom))
			{
				rcMove->top += interH;
				rcMove->bottom += interH;
				if (pOutDirection)
					*pOutDirection = (Direction::Enum)((*pOutDirection) | Direction::Top);
			}
		}
		return true;
	}

	/**************************************
	Vector2InRect
	Rect* rc : ��Ʈ
	Vector2* pt : ��ǥ
	return bool : ����� ��ȯ
	**************************************/
	inline bool Vector2InRect(const Rect* const rc, const Vector2* const pt)
	{
		if (rc->left > pt->x)return false;
		if (rc->right < pt->x)return false;
		if (rc->top > pt->y)return false;
		if (rc->bottom < pt->y)return false;
		return true;
	}

	/********************************
	Vector2InEllipse ##
	Vector2* pVector : ��ǥ
	Eliipse* pEllipse : ��
	return bool : ����� ��ȯ
	*********************************/
	inline bool Vector2InCircle(const Vector2* const pVector, const Circle* const pEllipse)
	{
		float deltaX = pVector->x - pEllipse->center.x;
		float deltaY = pVector->y - pEllipse->center.y;

		float distSquare = deltaX * deltaX + deltaY * deltaY;

		float radiusSquare = pEllipse->radius * pEllipse->radius;

		if (radiusSquare < distSquare) return false;

		return true;
	}

	/******************************
	IntersectEllipseEllipse ##
	FloatEllipse* ellipse1 : ��
	FloatEllipse* ellipse2 : ��
	return bool : ��� ��ȯ��
	*******************************/
	inline bool IntersectCircleToCircle(const Circle* const ellipse1, const Circle* const ellipse2)
	{
		Vector2 dirVector;
		dirVector.x = ellipse1->center.x - ellipse2->center.x;
		dirVector.y = ellipse1->center.y - ellipse2->center.y;
		float length = Vector2::Length(&dirVector);

		if (length > ellipse1->radius + ellipse2->radius)
			return false;

		return true;
	}
}