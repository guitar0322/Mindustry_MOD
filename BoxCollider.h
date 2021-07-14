#pragma once
#include "Component.h"
/**********************************************************************
D2D Framework BoxCollider
by 홍대영
up to date 21-07-08
# Rect _rc : 충돌체 사각영역
# Rect _intersectRc : 충돌체간의 overlap 사각 영역
# bool _isTrigger : overlap 이벤트 Enter, Stay, Exit이벤트 발동 전제조건
    true면 사용, false면 사용하지 않음.
    true면 물리연산에 의해 충돌체가 밀려나지 않음
# vector<BoxCollider*> _overlapColV : 겹쳐져 있는 충돌체 목록
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
    //int _colliderCheckOffset;//근처 충돌체 탐색 범위
    vector<BoxCollider*> _overlapColV;

public:
    BoxCollider();
    ~BoxCollider();
    //int weight;//물리 연산에서 적용될 충돌체의 무게
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
};

