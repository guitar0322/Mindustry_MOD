#pragma once
#include "image.h"
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
	bool isEmission;
	int curFrame;
	float frameTick;
};

class ParticleSystem :
    public Component
{
private:
	int _x, _y;
	bool _isStop;
	image* _particleImage;
	vector<Particle> _particle;
	int _num;
	int _emissionNum;
	float _deltaTime;
	float _interval;
	float _minDuration, _maxDuration;
	float _frameTerm;
	bool _isLoop;
	float _minSpeed, _maxSpeed;
	float _minAngle, _maxAngle;
	float _gravity;
public:
	ParticleSystem(image* particleImage, int num, float frameTerm);
	~ParticleSystem();
	void Emission(int idx);
	void EmissionAll();
	virtual void Update();
	virtual void Render();
	void Play();
	void Stop();

	float GetX() { return _x; }
	float GetY() { return _y; };

	void SetAngle(float minAngle, float maxAngle) { _minAngle = minAngle, _maxAngle = maxAngle; }
	void SetMinAngle(float minAngle) { _minAngle = minAngle; }
	void SetMaxAngle(float maxAngle) { _maxAngle = maxAngle; }
	float GetMinAngle() { return _minAngle; }
	float GetMaxAngle() { return _maxAngle; }

	void SetPosition(int x, int y) { _x = x; _y = y; }

	void SetDuration(float duration) { _minDuration = duration; _maxDuration = duration; }
	void SetDuration(float minDuration, float maxDuration) { _minDuration = minDuration; _maxDuration = maxDuration; }

	void SetInterval(float interval) { _interval = interval; }

	void SetSpeed(float speed) { _minSpeed = speed, _maxSpeed = speed; }
	void SetSpeed(float minSpeed, float maxSpeed) { _minSpeed = minSpeed; _maxSpeed = maxSpeed; }

	void SetLoop(bool isLoop) { _isLoop = isLoop; }

	void SetGravity(float gravity) { _gravity = gravity; }
	void SetParticleImage(image* newImage) { _particleImage = newImage; }
};

