#pragma once
#include "Component.h"
/**********************************************************************
D2D Framework BoxCollider
by ȫ�뿵
up to date 21-07-08
# Rect _rc : �浹ü �簢����
# Rect _intersectRc : �浹ü���� overlap �簢 ����
# bool _isTrigger : overlap �̺�Ʈ Enter, Stay, Exit�̺�Ʈ �ߵ� ��������
    true�� ���, false�� ������� ����.
    true�� �������꿡 ���� �浹ü�� �з����� ����
# vector<BoxCollider*> _overlapColV : ������ �ִ� �浹ü ���
**********************************************************************/
class BoxCollider :
    public Component
{
private:
    Rect _rc;
    Rect _intersectRc;
    float _width;
    float _height;
    int _weight;
    bool _isTrigger;
    //int _colliderCheckOffset;//��ó �浹ü Ž�� ����
    vector<BoxCollider*> _overlapColV;
    vector<pair<int, int>> _partitionIdx;
public:
    BoxCollider();
    ~BoxCollider();
    //int weight;//���� ���꿡�� ����� �浹ü�� ����
    virtual void Init();
    virtual void Update();
    virtual void Render();
    virtual void OnDisable();
    virtual void OnEnable();
    bool CheckCollision();
    void TriggerEventHandler();
    void SetWidth(float width);
    void SetHeight(float height);
    void SetSize(float width, float height);

    Rect GetRc() const { return _rc; }

    void SetIsTrigger(bool isTrigger) { _isTrigger = isTrigger; }
    bool GetIsTrigger() const { return _isTrigger; }

    //void SetOffset(int offset) { _colliderCheckOffset = offset; }

    void RemoveOverlapCol(BoxCollider* exitCollider);
    void AddOverlapCol(BoxCollider* overlapCollider);
    void RefreshPartition();
    vector<pair<int, int>> GetPartitionIdx() const { return _partitionIdx; }
};

