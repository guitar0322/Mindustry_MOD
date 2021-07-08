#include "stdafx.h"
#include "ParticleSystem.h"
#include "image.h"


ParticleSystem::ParticleSystem(image* particleImage, int num, float frameTerm)
{
	_particleImage = particleImage;
	_num = num;
	_minDuration = 1000;
	_maxDuration = 1000;
	_minSpeed = 1.0f;
	_maxSpeed = 1.0f;
	_isLoop = true;
	_isStop = false;
	_gravity = 0;
	_frameTerm = frameTerm;
	for (int i = 0; i < _num; i++) {
		_particle.push_back(Particle());
		_particle[i].isEmission = false;
		_particle[i].curFrame = 0;
	}
}

ParticleSystem::~ParticleSystem()
{

}
void ParticleSystem::Emission(int idx)
{
	if (_particle[idx].isEmission == false) {
		if (_minAngle == 0 && _maxAngle == 0) {
			_particle[idx].angle = RND->getFloat(Math::PI2);
		}
		else {
			_particle[idx].angle = RND->getFromFloatTo(_minAngle, _maxAngle);
		}
		//_particle[idx].img = _particleImage;
		_particle[idx].x = this->_x;
		_particle[idx].y = this->_y;
		_particle[idx].isEmission = true;
		_particle[idx].speedX = cosf(_particle[idx].angle) * RND->getFromFloatTo(_minSpeed, _maxSpeed);
		_particle[idx].speedY = -sinf(_particle[idx].angle) * RND->getFromFloatTo(_minSpeed, _maxSpeed);
		if (this->_minDuration == this->_maxDuration)
			_particle[idx].duration = this->_minDuration;
		else
			_particle[idx].duration = RND->getFromFloatTo(_minDuration, _maxDuration);
		_particle[idx].activeTime = 0;
		_emissionNum = idx + 1;
		if (_emissionNum == _num && _isLoop == true) {
			_emissionNum = 0;
		}
	}
}

void ParticleSystem::EmissionAll()
{
	for (int i = 0; i < _num; i++) {
		Emission(i);
	}
}

void ParticleSystem::Update()
{
	_x = gameObject->transform->position.x;
	_y = gameObject->transform->position.y;
	if (_isStop == false) {
		_deltaTime += TIMEMANAGER->getElapsedTime();
		if (_deltaTime >= _interval && _interval != 0) {
			_deltaTime = 0;
			if (_emissionNum != _num)
				Emission(_emissionNum);
		}
		else if (_interval == 0) {
			if (_emissionNum != _num)
				EmissionAll();
		}
	}
	for (int i = 0; i < _num; i++) {
		if (_particle[i].isEmission == false) continue;
		_particle[i].activeTime += TIMEMANAGER->getElapsedTime();
		_particle[i].frameTick += TIMEMANAGER->getElapsedTime();
		if (_particle[i].frameTick >= _frameTerm) {
			_particle[i].frameTick = 0;
			_particle[i].curFrame++;
			if (_particle[i].curFrame == _particleImage->getMaxFrameX())
				_particle[i].curFrame = 0;
		}
		if (_particle[i].activeTime >= _particle[i].duration) {
			_particle[i].isEmission = false;
		}
		_particle[i].x += _particle[i].speedX;
		_particle[i].y += _particle[i].speedY;
		_particle[i].speedY += _gravity;
	}
}

void ParticleSystem::Render()
{
	for (int i = 0; i < _num; i++) {
		if (_particle[i].isEmission == false) continue;
		//_particleImage->frameRender(BackBuffer,
		//	_particle[i].x - _particleImage->getFrameWidth()/2,
		//	_particle[i].y - _particleImage->getFrameHeight()/2
		//	, _particle[i].curFrame, 0);
	}
}

void ParticleSystem::Play()
{
	_isStop = false;
	_emissionNum = 0;
	for (int i = 0; i < _num; i++) {
		_particle[i].isEmission = false;
	}
}

void ParticleSystem::Stop()
{
	_isStop = true;
}
