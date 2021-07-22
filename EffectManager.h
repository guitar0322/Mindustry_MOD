#pragma once
#define EFFECT_MIN 3
#define PARTICLE_MAX 10
/*
* ������Ʈ Ǯ�� Ȱ���� ����Ʈ �Ŵ���
* �ּ� EFFECT_MIN���� ����Ʈ���� ����ü�� �����ϰ� �ִٰ�
* ���Ŀ� �߰����� ����Ʈ ���� ��û�� ���� ��� ���ο� ����Ʈ ����ü�� �����ϰ�
* ��û�� ���� ��� ����Ʈ ���� ������ ũ�⸦ EFFECT_MIN���� ����
*/
class ParticleObject;

class EffectManager : public singletonBase<EffectManager>
{
private:
    typedef struct tagEffectInfo {
        int x, y;           //���Ǵ� ��ġ
        int curFrame;       //����Ʈ ����������
        int maxFrame;       //����Ʈ �ִ�������
        float frameTerm;    //����Ʈ �����Ӱ� ����
        float time;         //����Ʈ ������ ���ӽð�
        string clipName;    //Ÿ�� ����Ʈ Ŭ���̸�
        bool active;        //ȭ��ȭ ����
        float angle;
    }EFFECTINFO;
private:
    vector<EFFECTINFO> _effectV;//����Ʈ ������ ���� ����ü ����
    vector<EFFECTINFO>::iterator _effectIter;
    vector<ParticleObject> _smallExplosionParticleV;
    vector<ParticleObject> _middleExplosionParticleV;
    vector<ParticleObject> _bigExplosionParticleV;
    vector<ParticleObject> _smokeParticleV;
    vector<ParticleObject>::iterator _particleVIter;
public:
    EffectManager();
    ~EffectManager();
    virtual void Init();
    virtual void Release();
    void Update();
    void Render();
    void EmissionEffect(string effectClipName, int x, int y, float angle);//x, y�� CLIPMANAGER�� �ִ� Ŭ���� ���
    void ActiveSmallParticle(float x, float y);
    void ActiveSmokeParticle(float x, float y);
    int GetEffectNum() { return _effectV.size(); }//����Ʈ���� ������ ��ü ũ�⸦ ��ȯ
    int GetActiveNum();//�ּҰ��� 3���� Ȱ��ȭ�� ����Ʈ�� ������ ��ȯ
};


