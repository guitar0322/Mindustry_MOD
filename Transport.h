#pragma once
#include "Component.h"
#include "PropInfo.h"
class Transport :
    public Component
{
private:
    typedef struct tagLink {
        bool isConnect; //true면 연결 false면 미연결
        bool inOut; //true면 out false면 in
    }LINK;
    enum SHAPE {
        O,
        I,
        L,
        L2,
        T,
        T2,
        T3,
        CROSS
    };
private:
    Animator* _animator;
    Animator* _firstConveyorAnimator;
    LINK linkInfo[4];
    PROPDIR _outDir;
    SHAPE _shape;
    int _tileX;
    int _tileY;
public:
    virtual void Init();
    virtual void Update();

    void SetX(int x) { _tileX = x; }
    void SetY(int y) { _tileY = y; }

    void LinkConveyor(PROPDIR dir);
    void SetOutDir(PROPDIR dir) { _outDir = dir; }
    PROPDIR GetOutDir() const { return _outDir; }
    void SetShape(int shape) { _shape = SHAPE(shape); }

    void SetFirstAnimator(Animator* firstAnimator) { _firstConveyorAnimator = firstAnimator; }
    /*************************************************
    * 컨베이어 설계
    * 네개의 연결 고리가 있다 (구조체 LINK)
    * 각 연결고리는 나가는것인지 들어가는것인지 구분짓는 bool이 있다
    * 지어질때 4갈래를 검사해 컨베이어가 있을 경우 방향을 매개변수로 컨베이어 추가 함수(LickConveyor)호출한다
    * LinkConveyor가 호출되면 방향에 따라 LINK의 멤버변수값, 애니메이터 클립, 앵글을 적절하게 바꾼다.(함수에서 더 자세히)
    * 나가는곳은 단 한곳만 있을 수 있다
    * 
    **************************************************/
};

