#include "stdafx.h"
#include "UIAnimator.h"

UIAnimator::UIAnimator()
{
}

UIAnimator::~UIAnimator()
{
}

void UIAnimator::Init()
{
	uiRenderer = gameObject->GetComponent<UIRenderer>();
	if (uiRenderer == nullptr) {
		throw "Animator에서 발생 : 게임 오브젝트에 uiRenderer컴포넌트가 없습니다";
	}
	_curFrameX = 0;
	_curFrameY = 0;
	_isPause = false;
	_isEnd = false;
}

void UIAnimator::Update()
{
	if (curClip == nullptr)
		return;
	if (_isPause == true) return;
	_frameTime += TIMEMANAGER->getElapsedTime();
	if (_frameTime >= curClip->GetFrameTerm()) {
		_curFrameX++;
		if (_curFrameX == curClip->GetFrameNum())
		{
			if (curClip->GetIsLoop() == true)
			{
				_curFrameX = 0;
			}
			else
			{
				_isEnd = true;
				_curFrameX = curClip->GetFrameNum() - 1;
			}
		}
		uiRenderer->SetFrameX(_curFrameX);
		_frameTime = 0;
	}
}

void UIAnimator::SetCurFrameY(int frameY)
{
	_curFrameY = frameY;
	uiRenderer->SetFrameY(_curFrameY);
}

void UIAnimator::SetClip(AnimationClip * newClip)
{
	preClip = curClip;
	curClip = newClip;
	_isEnd = false;
	_curFrameX = 0;
	_frameTime = 0;
	uiRenderer->ChangeTargetBitmap(newClip->GetLoadName());
}

void UIAnimator::SetClip(AnimationClip * newClip, int startFrame)
{
	preClip = curClip;
	curClip = newClip;
	_isEnd = false;
	_curFrameX = startFrame;
	_frameTime = 0;
	uiRenderer->ChangeTargetBitmap(newClip->GetLoadName(), startFrame);
}

void UIAnimator::SetClip(string clipName)
{
	preClip = curClip;
	curClip = GetClip(clipName);
	_isEnd = false;
	_curFrameX = 0;
	_frameTime = 0;
	uiRenderer->ChangeTargetBitmap(clipName);
}

void UIAnimator::SetClip(string clipName, int startFrame)
{
	preClip = curClip;
	curClip = GetClip(clipName);
	_isEnd = false;
	_curFrameX = startFrame;
	_frameTime = 0;
	uiRenderer->ChangeTargetBitmap(clipName, startFrame);
}

void UIAnimator::AddClip(string clipName, AnimationClip * newClip)
{
	clipMap.insert(make_pair(clipName, newClip));
}

void UIAnimator::AddClip(string clipName)
{
	clipMap.insert(make_pair(clipName, CLIPMANAGER->FindClip(clipName)));
}

void UIAnimator::AddClip(AnimationClip * newClip)
{
	if (newClip->GetLoadName().length() == 0)
		return;
	clipMap.insert(pair<string, AnimationClip*>(newClip->GetLoadName(), newClip));
}

AnimationClip * UIAnimator::GetClip(string clipName)
{
	map<string, AnimationClip*>::iterator iter;
	iter = clipMap.find(clipName);
	if (iter != clipMap.end()) {
		return iter->second;
	}
	return nullptr;
}

void UIAnimator::Pause()
{
	_isPause = true;
}

void UIAnimator::Resume()
{
	_isPause = false;
}
