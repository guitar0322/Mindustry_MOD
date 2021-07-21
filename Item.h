#pragma once
#include "GameObject.h"
#include "GameInfo.h"

class PropContainer;
class Conveyor;

class Item :
    public GameObject
{
private:
    RESOURCE _type;
    Conveyor* _curConveyor;
    PropContainer* _propContainer;
    pair<int, int> _preTile;
    float _speed;
    int _dir;
    bool _isOverCenter;
    float _colliderDelay;
public:
    Item(RESOURCE type);
    ~Item();
    Renderer* renderer;
    BoxCollider* collider;
    virtual void Update();
    RESOURCE GetTargetResource() const { return _type; }
    void SetType(RESOURCE type) { _type = type; }
    void SetConveyor(Conveyor* conveyor);
    void SetLinkPropContainer(PropContainer* propContainer) { _propContainer = propContainer; }
};

/***************************************************
* ��� ����
* 1.�ڿ��� ������ġ�� �ִ� Ÿ���� �ε����� ���Ѵ�.
* 2.���� �ʿ��� ���� Ÿ���� �����̾� ��Ʈ���� ���Ѵ�.
* 3.���� �������� �÷����ִ� ��Ʈ �����͸� �ٲ۴�.
* 4.��Ʈ�� ���������� ������ ���� ������ �״�� �����δ�.
* 5.�������ʹ� ��Ʈ�� �ⱸ ���⿡ ���� �����δ�.
* 
* �����°� ����
* 1.BoxCollider�״�� �̿� 1��
* 2��
* 1.
*****************************************************/

