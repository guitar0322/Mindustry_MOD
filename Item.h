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
* 운송 설계
* 1.자원의 현재위치가 있는 타일의 인덱스를 구한다.
* 2.게임 맵에서 현재 타일이 컨베이어 벨트인지 구한다.
* 3.현재 아이템이 올려져있는 벨트 포인터를 바꾼다.
* 4.벨트의 중점까지는 무조건 현재 방향을 그대로 움직인다.
* 5.중점부터는 벨트의 출구 방향에 따라 움직인다.
* 
* 막히는것 설계
* 1.BoxCollider그대로 이용 1안
* 2안
* 1.
*****************************************************/

