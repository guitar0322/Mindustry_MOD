#pragma once
#include "Component.h"
#include "PropInfo.h"
class Item;

class Transport :
    public Component
{
private:
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
    Item* _inResource;
    vector<pair<int, Item*>> _resInfo;
    int _tileX;
    int _tileY;
    bool _isLack;
    float _unLackTerm;
    bool _unLackFlag;
public:
    virtual void Init();
    virtual void Update();
    virtual void OnTriggerEnter(GameObject* gameObject);
    virtual void OnTriggerExit(GameObject* gameObject);

    void SetX(int x) { _tileX = x; }
    void SetY(int y) { _tileY = y; }

    void LinkConveyor(PROPDIR dir);
    void SetOutDir(PROPDIR dir) { _outDir = dir; }
    PROPDIR GetOutDir() const { return _outDir; }
    void SetShape(int shape) { _shape = SHAPE(shape); }
    void SetFirstAnimator(Animator* firstAnimator) { _firstConveyorAnimator = firstAnimator; }
    void SetIsLack(bool isLack);
    bool GetIsLeck() const { return _isLack; }

    Item* GetInResource() { return _inResource; }
    /*************************************************
    * �����̾� ����
    * �װ��� ���� ���� �ִ� (����ü LINK)
    * �� ������� �����°����� ���°����� �������� bool�� �ִ�
    * �������� 4������ �˻��� �����̾ ���� ��� ������ �Ű������� �����̾� �߰� �Լ�(LickConveyor)ȣ���Ѵ�
    * LinkConveyor�� ȣ��Ǹ� ���⿡ ���� LINK�� ���������, �ִϸ����� Ŭ��, �ޱ��� �����ϰ� �ٲ۴�.(�Լ����� �� �ڼ���)
    * �����°��� �� �Ѱ��� ���� �� �ִ�
    * 
    **************************************************/
};

