#pragma once
#include "Component.h"
class Transport :
    public Component
{
private:
    int _tileX;
    int _tileY;
public:
    virtual void Init();
    virtual void Update();

    void SetX(int x) { _tileX = x; }
    void SetY(int y) { _tileY = y; }

    /*************************************************
    * �����̾� ����
    * �װ��� ���� ���� �ִ� (����ü LINK)
    * �� ������� �����°����� ���°����� �������� bool�� �ִ�
    * �����°��� �� �Ѱ��� ���� �� �ִ�
    * �������� 4������ �˻��� �����̾ ���� ��� ������ �Ű������� �����̾� �߰� �Լ�(LickConveyor)ȣ���Ѵ�
    * LinkConveyor�� ȣ��Ǹ� ���⿡ ���� LINK�� ���������, �ִϸ����� Ŭ��, �ޱ��� �����ϰ� �ٲ۴�.(�Ʒ����� �� �ڼ���)
    * 
    **************************************************/
};

