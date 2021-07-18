#pragma once
#include "Component.h"
enum SHAPE {
	CIRCLE,
	HALF
};
struct Particle {
	float x, y;
	float activeTime;
	float duration;
	float speedX, speedY;
	float gravity;
	float angle;
	float alpha;
	bool isEmission;
	int curFrameX;
	int curFrameY;
	float frameTick;
	float scaleY;
};

class ParticleSystem :
    public Component
{
private:
	bool _isStop;
	AnimationClip* _targetClip;
	ID2D1Bitmap* _targetBitmap;
	string _loadClipName;
	vector<Particle> _particleV;
	int _totalParticleNum;
	int _emissionNum;
	float _deltaTime;
	float _interval;
	float _minDuration;
	float _maxDuration;
	float _frameTerm;
	float _frameWidth;
	float _frameHeight;
	float _minAlpha;
	float _maxAlpha;
	float _pivotDistance;
	float _emissionTerm;
	float _minScaleY;
	float _maxScaleY;

	bool _isLoop;
	float _minSpeed, _maxSpeed;
	float _minAngle, _maxAngle;
	float _gravity;
public:
	ParticleSystem();
	~ParticleSystem();
	HRESULT Init(string clipName, int totalNum);
	void Emission(int idx);
	void EmissionAll();
	virtual void Update();
	virtual void Render();
	void Play();
	void Stop();

	void SetAngle(float minAngle, float maxAngle) { _minAngle = minAngle, _maxAngle = maxAngle; }
	void SetMinAngle(float minAngle) { _minAngle = minAngle; }
	void SetMaxAngle(float maxAngle) { _maxAngle = maxAngle; }
	float GetMinAngle() { return _minAngle; }
	float GetMaxAngle() { return _maxAngle; }

	void SetDuration(float duration) { _minDuration = duration; _maxDuration = duration; }
	void SetDuration(float minDuration, float maxDuration) { _minDuration = minDuration; _maxDuration = maxDuration; }

	void SetInterval(float interval) { _interval = interval; }

	void SetSpeed(float speed) { _minSpeed = speed, _maxSpeed = speed; }
	void SetSpeed(float minSpeed, float maxSpeed) { _minSpeed = minSpeed; _maxSpeed = maxSpeed; }

	void SetLoop(bool isLoop) { _isLoop = isLoop; }

	void SetGravity(float gravity) { _gravity = gravity; }

	void SetTotalParticleNum(int num) { _totalParticleNum = num; }

	void SetPivotDistance(float distance) { _pivotDistance = distance; }

	void SetEmissionTerm(float term) { _emissionTerm = term; }

	void SetScaleY(float minScaleY, float maxScaleY) { _minScaleY = minScaleY, _maxScaleY = maxScaleY; }
};

