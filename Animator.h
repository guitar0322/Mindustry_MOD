#pragma once
#include "Component.h"
#include <map>
class AnimationClip;
//Ʈ������� �߰��� �� �ְ�
//Ʈ������� ������ ������ �߰��Ѵ�
typedef struct tagTransaction {
    bool isReset; //�������� 0���� �����Ұ���
    
}Transaction;

class Animator :
    public Component
{
private:
    typedef struct tagTransaction {
        AnimationClip* startClip;
        AnimationClip* nextClip;
    }TRANSACTION;
private:
    float _frameTime;
	bool _isPause;
    bool _isEnd;
    int _curFrameX;
    int _curFrameY;
public:
    Animator();
    ~Animator();
    Renderer* renderer;
    AnimationClip* curClip;
    AnimationClip* preClip;
    map<string, AnimationClip*> clipMap;
    map<string, TRANSACTION> transactionMap;
    map<string, TRANSACTION>::iterator transactionIter;
    void Init();
    void Update();
    void Render();
    int GetCurFrameX() const { return _curFrameX; }
    float GetFrameTime() const { return _frameTime; }
    void SetFrameTime(float frameTime) { _frameTime = frameTime; }
    void SetCurFrameY(int frameY);

    void SetClip(AnimationClip* newClip);
    void SetClip(AnimationClip* newClip, int startFrame);
    void SetClip(string clipName);
    void SetClip(string clipName, int startFrame);
    void AddClip(string clipName, AnimationClip* newClip);
    void AddClip(string clipName);
    void AddClip(AnimationClip* newClip);
    AnimationClip* GetClip(string clipName);
    void AddTransaction(string name, AnimationClip* startClip, AnimationClip* nextClip);
	void Pause();
	void Resume();
    bool GetEnd() const { return _isEnd; }
};

