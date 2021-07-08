#pragma once
#define EFFECT_MIN 3
/*
* 오브젝트 풀을 활용한 이펙트 매니저
* 최소 EFFECT_MIN개이 이펙트정보 구조체를 보유하고 있다가
* 이후에 추가적인 이펙트 생성 요청이 있을 경우 새로운 이펙트 구조체를 생성하고
* 요청이 없을 경우 이펙트 정보 벡터의 크기를 EFFECT_MIN으로 유지
*/
class EffectManager : public singletonBase<EffectManager>
{
private:
    typedef struct tagEffectInfo {
        int x, y;           //방사되는 위치
        int curFrame;       //이펙트 현재프레임
        int maxFrame;       //이펙트 최대프레임
        float frameTerm;    //이펙트 프레임간 간격
        float time;         //이펙트 프레임 지속시간
        string clipName;    //타겟 이펙트 클립이름
        bool active;        //화성화 여부
    }EFFECTINFO;
private:
    vector<EFFECTINFO> _effectV;//이펙트 렌더를 위한 구조체 정보
    vector<EFFECTINFO>::iterator _effectIter;
public:
    EffectManager();
    ~EffectManager();
    virtual void Init();
    virtual void Release();
    void Update();
    void Render();
    void EmissionEffect(string effectClipName, int x, int y);//x, y에 CLIPMANAGER에 있는 클립을 방사
    int GetEffectNum() { return _effectV.size(); }//이펙트정보 벡터의 전체 크기를 반환
    int GetActiveNum();//최소개수 3개중 활성화된 이펙트의 개수를 반환
};


