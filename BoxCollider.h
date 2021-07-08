#pragma once
#include "Component.h"
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
    int _colliderCheckOffset;
    vector<BoxCollider*> _overlapColV;
    vector<BoxCollider*> _overlapColPreV;
public:
    BoxCollider();
    ~BoxCollider();
    vector<int> vCol;
    vector<int> prevCol;
    bool isTrigger;
    int weight;
    virtual void Init();
    virtual void Update();
    virtual void Render();
    virtual void OnDisable();
    virtual void OnEnable();
    bool CheckCollision(float tempX, float tempY);
    bool CheckCollision();
    bool CheckCollision(float tempX, float tempY, int colIdx);
    bool CheckCollision(Rect rc, int colIdx);
    void TriggerEventHandler();
    void SetWidth(float width);
    void SetHeight(float height);
    void SetSize(float width, float height);

    Rect GetRc() const { return _rc; }

    void SetIsTrigger(bool isTrigger) { _isTrigger = isTrigger; }
    bool GetIsTrigger() const { return _isTrigger; }

    void SetOffset(int offset) { _colliderCheckOffset = offset; }

    void RemoveOverlapCol(BoxCollider* exitCollider);
};

