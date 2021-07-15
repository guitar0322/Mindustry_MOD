#include "stdafx.h"
#include "ParticleSystem.h"
#include "image.h"


ParticleSystem::ParticleSystem()
	:_minDuration(1.f), _maxDuration(1.f), _minSpeed(1.f), _maxSpeed(1.f), _isLoop(true),
	_isStop(false), _gravity(0), _frameTerm(Math::FloatMax), _totalParticleNum(0),
	_minAlpha(1.f), _maxAlpha(1.f), _pivotDistance(0), _emissionTerm(0),
	_minScaleY(1.f), _maxScaleY(1.f)
{

}

ParticleSystem::~ParticleSystem()
{

}
HRESULT ParticleSystem::Init(string clipName, int totalNum)
{
	_totalParticleNum = totalNum;
	_loadClipName = clipName;
	_targetClip = CLIPMANAGER->FindClip(clipName);
	if (_targetClip == nullptr)
		throw("particle system init error");
	_targetBitmap = _targetClip->GetBitmap();
	_frameTerm = _targetClip->GetFrameTerm();
	_frameWidth = _targetClip->GetFrameWidth();
	_frameHeight = _targetClip->GetFrameHeight();
	for (int i = 0; i < _totalParticleNum; i++) {
		_particleV.push_back(Particle());
		_particleV[i].isEmission = false;
		_particleV[i].curFrameX = 0;
		_particleV[i].curFrameY = 0;
	}
	return S_OK;
}
void ParticleSystem::Emission(int idx)
{
	if (_particleV[idx].isEmission == false) {
		if (_minAngle == 0 && _maxAngle == 0) {
			_particleV[idx].angle = RND->getFloat(Math::PI2);
		}
		else {
			_particleV[idx].angle = RND->getFromFloatTo(_minAngle, _maxAngle);
		}
		_particleV[idx].x = transform->GetX() + _pivotDistance * cosf(_particleV[idx].angle);
		_particleV[idx].y = transform->GetY() + _pivotDistance * -sinf(_particleV[idx].angle);
		_particleV[idx].isEmission = true;
		_particleV[idx].speedX = cosf(_particleV[idx].angle) * RND->getFromFloatTo(_minSpeed, _maxSpeed);
		_particleV[idx].speedY = -sinf(_particleV[idx].angle) * RND->getFromFloatTo(_minSpeed, _maxSpeed);
		_particleV[idx].alpha = RND->getFromFloatTo(_minAlpha, _maxAlpha);
		_particleV[idx].scaleY = RND->getFromFloatTo(_minScaleY, _maxScaleY);
		if (this->_minDuration == this->_maxDuration)
			_particleV[idx].duration = this->_minDuration;
		else
			_particleV[idx].duration = RND->getFromFloatTo(_minDuration, _maxDuration);
		_particleV[idx].activeTime = 0;
		_emissionNum = idx + 1;
		if (_emissionNum == _totalParticleNum && _isLoop == true) {
			_emissionNum = 0;
		}
	}
}

void ParticleSystem::EmissionAll()
{
	for (int i = 0; i < _totalParticleNum; i++) {
		Emission(i);
	}
}

void ParticleSystem::Update()
{
	if (_isStop == false) {
		_deltaTime += TIMEMANAGER->getElapsedTime();
		if (_deltaTime >= _interval && _interval != 0) {
			_deltaTime = 0;
			if (_emissionNum != _totalParticleNum)
				Emission(_emissionNum);
		}
		else if (_interval == 0 && _deltaTime >= _emissionTerm) {
			_deltaTime = 0;
			if (_emissionNum != _totalParticleNum)
				EmissionAll();
		}
	}
	for (int i = 0; i < _totalParticleNum; i++) {
		if (_particleV[i].isEmission == false) continue;
		_particleV[i].activeTime += TIMEMANAGER->getElapsedTime();
		_particleV[i].frameTick += TIMEMANAGER->getElapsedTime();
		if (_particleV[i].frameTick >= _frameTerm) {
			_particleV[i].frameTick = 0;
			_particleV[i].curFrameX++;
			if (_particleV[i].curFrameX == _targetClip->GetFrameNum())
				_particleV[i].curFrameX = 0;
		}
		if (_particleV[i].activeTime >= _particleV[i].duration) {
			_particleV[i].isEmission = false;
		}
		_particleV[i].x += _particleV[i].speedX;
		_particleV[i].y += _particleV[i].speedY;
		_particleV[i].speedY += _gravity;
	}
}

void ParticleSystem::Render()
{
	for (int i = 0; i < _totalParticleNum; i++) {
		if (_particleV[i].isEmission == false) continue;
		D2D1_RECT_F bitmapArea = D2D1::RectF(_particleV[i].curFrameX * _frameWidth, _particleV[i].curFrameY * _frameHeight, 
			(_particleV[i].curFrameX + 1) * _frameWidth, (_particleV[i].curFrameY + 1) * _frameHeight);

		D2D1_RECT_F backBufferArea = D2D1::RectF(_particleV[i].x - _frameWidth / 2, _particleV[i].y - _frameHeight / 2,
			_particleV[i].x + _frameWidth / 2, _particleV[i].y + _frameHeight / 2);
		D2D1_MATRIX_3X2_F rotate = D2D1::Matrix3x2F::Rotation(
			ConvertAngleD2D(_particleV[i].angle), D2D1::Point2F(_particleV[i].x, _particleV[i].y));
		D2D1_MATRIX_3X2_F scale = D2D1::Matrix3x2F::Scale(
			D2D1::SizeF(1.f, _particleV[i].scaleY), D2D1::Point2F(_particleV[i].x, _particleV[i].y));

		BackBuffer->SetTransform(scale * rotate);
		BackBuffer->DrawBitmap(_targetBitmap, backBufferArea, _particleV[i].alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, bitmapArea);
		BackBuffer->SetTransform(D2D1::Matrix3x2F::Identity());
	}
}

void ParticleSystem::Play()
{
	_isStop = false;
	_emissionNum = 0;
	for (int i = 0; i < _totalParticleNum; i++) {
		_particleV[i].isEmission = false;
	}
}

void ParticleSystem::Stop()
{
	_isStop = true;
}
