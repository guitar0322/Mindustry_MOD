#pragma once
#include "Component.h"

class ZOrder :
    public Component
{
private:
    float _z;//zorder수행할 기준좌표
    float _x;
    RECT _rc;
public:
    virtual void Init();
    virtual void Render();
    virtual void OnEnable();
    virtual void OnDisable();
    void MoveZ(float z);//기준좌표를 이동
    void SetZ(float z) { _z = z; }//기준좌표를 설정
    float GetZ() { return _z; }//기준좌표를 반환
};