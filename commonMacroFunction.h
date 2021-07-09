#pragma once

//============================================
// ## 21.04.23 ## commonMacroFunction ##
//============================================

//          ���߱��Լ�(�׷���DC, ������ǥX, ������ǥY, ����ǥ X, ����ǥY)
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

//�簢�� 
inline void Rectangle(HDC hdc, RECT& rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

//x, y���� �������� �ϴ� �簢���� ������
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

//x, y ��ǥ�� �������� ũ�⸸ŭ�� �簢���� ������
inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}