#include "stdafx.h"
#include "EffectManager.h"
#include "ParticleObject.h"
EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
}

void EffectManager::Init()
{
	CLIPMANAGER->AddClip("spark_particle", "sprites/effects/spark-particle.png", 4, 20);
	CLIPMANAGER->AddClip("spark_circle", "sprites/effects/spark-circle.png", 180, 36, 5, 1, 0.04f);
	CLIPMANAGER->AddClip("shoot", "sprites/effects/shoot.png", 67, 45, 3, 1, 0.04f);
	CLIPMANAGER->AddClip("smoke", "sprites/effects/smoke-particle.png", 160, 40, 4, 1, 0.12f)->SetIsLoop(false);
	CLIPMANAGER->AddClip("explosion", "sprites/effects/explosion.png", 585, 117, 5, 1, 0.08f)->SetIsLoop(false);
	CLIPMANAGER->AddClip("big_explosion", "sprites/effects/big_explosion.png", 1170, 234, 5, 1, 0.08f)->SetIsLoop(false);
	CLIPMANAGER->AddClip("core_landing", "sprites/effects/core_landing.png", 2000, 500, 4, 1, 0.08f)->SetIsLoop(false);
	CLIPMANAGER->AddClip("core_start_landing", "sprites/effects/core_start_landing.png", 1200, 200, 6, 1, 0.08f)->SetIsLoop(false);


	for (int i = 0; i < EFFECT_MIN; i++)
	{
		EFFECTINFO effectInfo;
		ZeroMemory(&effectInfo, sizeof(EFFECTINFO));
		_effectV.push_back(effectInfo);
	}
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		ParticleObject smallParticle;
		smallParticle.particleSystem->Init("spark_particle", 6);
		smallParticle.particleSystem->SetDuration(0.3f);
		smallParticle.particleSystem->SetScaleY(0.1f, 1.f);
		//smallParticle.particleSystem->SetPivotDistance(30.f);
		smallParticle.particleSystem->SetSpeed(1.f, 2.f);
		smallParticle.particleSystem->SetLoop(false);
		smallParticle.SetActive(false);
		_smallExplosionParticleV.push_back(smallParticle);
	}

	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		ParticleObject middleParticle;
		middleParticle.particleSystem->Init("spark_particle", 12);
		middleParticle.particleSystem->SetDuration(0.3f);
		middleParticle.particleSystem->SetScaleY(1.f, 4.f);
		middleParticle.particleSystem->SetPivotDistance(10.f);
		middleParticle.particleSystem->SetSpeed(1.f, 2.f);
		middleParticle.particleSystem->SetLoop(false);
		middleParticle.SetActive(false);
		_middleExplosionParticleV.push_back(middleParticle);
	}

	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		ParticleObject bicParticle;
		bicParticle.particleSystem->Init("spark_particle", 12);
		bicParticle.particleSystem->SetDuration(0.3f);
		bicParticle.particleSystem->SetPivotDistance(30.f);
		bicParticle.particleSystem->SetSpeed(1.f, 2.f);
		bicParticle.particleSystem->SetLoop(false);
		bicParticle.SetActive(false);
		_bigExplosionParticleV.push_back(bicParticle);
	}

	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		ParticleObject smokeParticle;
		smokeParticle.particleSystem->Init("smoke", 8);
		smokeParticle.particleSystem->SetDuration(0.8f);
		smokeParticle.particleSystem->SetPivotDistance(10.f);
		smokeParticle.particleSystem->SetSpeed(1.f, 2.f);
		smokeParticle.particleSystem->SetGravity(-0.08f);
		smokeParticle.particleSystem->SetLoop(false);
		smokeParticle.SetActive(false);
		_smokeParticleV.push_back(smokeParticle);
	}
}

void EffectManager::Update()
{
	for (_effectIter = _effectV.begin(); _effectIter != _effectV.end();) 
	{
		if (_effectIter->active == false)
		{
			_effectIter++;
			continue;
		}
		//����Ʈ�� �ִ��������� �ȵǸ� ���ͷ����͸� ������Ű�鼭 ����
		if (_effectIter->curFrame != _effectIter->maxFrame)
		{
			_effectIter->time += TIMEMANAGER->getElapsedTime();
			if (_effectIter->time >= _effectIter->frameTerm) {	//������ �ð��� ���ݺ��� Ŀ����
				_effectIter->curFrame++;						//���� ���������� �̵�
				_effectIter->time = 0;							//������ �ð� �ʱ�ȭ
			}
			_effectIter++;				//����Ʈ�� ����Ȱ��� �ƴϸ� ���ͷ����͸� ����
		}
		//����Ʈ�� �ִ��������� ���� ���
		else if(_effectV.size() > EFFECT_MIN)
			//����Ʈ�� ������ �ּҰ������� ���ٸ� ����Ʈ�� ���Ϳ��� erase
			_effectIter = _effectV.erase(_effectIter);
		else
			//����Ʈ ������ �ּҰ������� ���ٸ� erase���� �ʰ� active�� �ʱ�ȭ
			_effectIter->active = false;
	}

	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (_smallExplosionParticleV[i].isActive == true)
		{
			if (_smallExplosionParticleV[i].particleSystem->GetIsEnd() == true)
				_smallExplosionParticleV[i].SetActive(false);
			_smallExplosionParticleV[i].Update();
		}
	}

	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (_smokeParticleV[i].isActive == true)
		{
			if (_smokeParticleV[i].particleSystem->GetIsEnd() == true)
				_smokeParticleV[i].SetActive(false);
			_smokeParticleV[i].Update();
		}
	}
}

void EffectManager::Render()
{
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (_smallExplosionParticleV[i].isActive == true)
		{
			_smallExplosionParticleV[i].Render();
		}
	}

	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (_smokeParticleV[i].isActive == true)
		{
			_smokeParticleV[i].Render();
		}
	}

	for (int i = 0; i < _effectV.size(); i++) {
		if (_effectV[i].active == false) continue;
		AnimationClip* curClip = CLIPMANAGER->FindClip(_effectV[i].clipName);
		D2D1_RECT_F backBufferArea =
			D2D1::RectF(
				_effectV[i].x, _effectV[i].y,
				_effectV[i].x + curClip->GetFrameWidth(),
				_effectV[i].y + curClip->GetFrameHeight()
			);
		D2D1_RECT_F clipArea = 
			D2D1::RectF(
				curClip->GetFrameWidth() * _effectV[i].curFrame, 0,
				curClip->GetFrameWidth() * _effectV[i].curFrame + curClip->GetFrameWidth(),
				curClip->GetFrameHeight()
			);
		D2D1_MATRIX_3X2_F rotate = D2D1::Matrix3x2F::Rotation(_effectV[i].angle, D2D1::Point2F(_effectV[i].x + curClip->GetFrameWidth() / 2, _effectV[i].y + curClip->GetFrameHeight() / 2));
		BackBuffer->SetTransform(rotate);
		BackBuffer->DrawBitmap(curClip->GetBitmap(), backBufferArea, 1.f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, clipArea);
		BackBuffer->SetTransform(D2D1::Matrix3x2F::Identity());
	}
}

void EffectManager::Release()
{
	_effectV.clear();
}

void EffectManager::EmissionEffect(string effectClipName, int x, int y, float angle)
{
	AnimationClip targetClip = *CLIPMANAGER->FindClip(effectClipName);
	if (GetActiveNum() == EFFECT_MIN) 
	{
		EFFECTINFO effectInfo;
		effectInfo.x = x - targetClip.GetFrameWidth() / 2;
		effectInfo.y = y - targetClip.GetFrameHeight() / 2;
		effectInfo.active = true;
		effectInfo.time = 0;
		effectInfo.curFrame = 0;
		effectInfo.maxFrame = targetClip.GetFrameNum();
		effectInfo.frameTerm = targetClip.GetFrameTerm();
		effectInfo.clipName = effectClipName;
		effectInfo.angle = angle;
		_effectV.push_back(effectInfo);
	}
	else
	{
		for (int i = 0; i < EFFECT_MIN; i++)
		{
			if (_effectV[i].active == true) continue;
			_effectV[i].x = x - targetClip.GetFrameWidth() / 2;
			_effectV[i].y = y - targetClip.GetFrameHeight() / 2;
			_effectV[i].active = true;
			_effectV[i].time = 0;
			_effectV[i].curFrame = 0;
			_effectV[i].maxFrame = targetClip.GetFrameNum();
			_effectV[i].frameTerm = targetClip.GetFrameTerm();
			_effectV[i].clipName = effectClipName;
			_effectV[i].angle = angle;
			break;
		}
	}
}

void EffectManager::ActiveSmallParticle(float x, float y)
{
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (_smallExplosionParticleV[i].isActive == true) continue;
		_smallExplosionParticleV[i].transform->SetPosition(x, y);
		_smallExplosionParticleV[i].SetActive(true);
		_smallExplosionParticleV[i].particleSystem->Play();
		EmissionEffect("spark_circle", x, y, 0);
		break;
	}
}

void EffectManager::ActiveSmokeParticle(float x, float y)
{
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (_smokeParticleV[i].isActive == true) continue;
		_smokeParticleV[i].transform->SetPosition(x, y);
		_smokeParticleV[i].SetActive(true);
		_smokeParticleV[i].particleSystem->Play();
		break;
	}
}

int EffectManager::GetActiveNum()
{
	int result = 0;
	for (int i = 0; i < EFFECT_MIN; i++) {
		if (_effectV[i].active == true)
			result++;
	}
	return result;
}
