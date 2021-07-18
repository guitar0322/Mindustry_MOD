#include "stdafx.h"
#include "Animator.h"
#include "AnimationClip.h"
Animator::Animator()
{
}


Animator::~Animator()
{

}

void Animator::Init()
{
	renderer = gameObject->GetComponent<Renderer>();
	if (renderer == nullptr) {
		throw "Animator에서 발생 : 게임 오브젝트에 Renderer컴포넌트가 없습니다";
	}
	_curFrameX = 0;
	_curFrameY = 0;
	_isPause = false;
	_isEnd = false;
}

void Animator::Update()
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
				for (transactionIter = transactionMap.begin(); transactionIter != transactionMap.end(); transactionIter++) {
					if (transactionIter->second.startClip == curClip) {
						SetClip(transactionIter->second.nextClip);
					}
				}
			}
		}
		renderer->SetFrameX(_curFrameX);
		_frameTime = 0;
	}
}

void Animator::Render()
{

}

void Animator::SetCurFrameY(int frameY)
{
	_curFrameY = frameY;
	renderer->SetFrameY(_curFrameY);
}

void Animator::SetClip(AnimationClip* newClip)
{
	preClip = curClip;
	curClip = newClip;
	_isEnd = false;
	_curFrameX = 0;
	_frameTime = 0;
	renderer->ChangeTargetBitmap(newClip->GetLoadName());
}

void Animator::SetClip(AnimationClip* newClip, int startFrame)
{
	preClip = curClip;
	curClip = newClip;
	_isEnd = false;
	_curFrameX = startFrame;
	_frameTime = 0;
	renderer->ChangeTargetBitmap(newClip->GetLoadName(), startFrame);
}

void Animator::SetClip(string clipName)
{
	preClip = curClip;
	curClip = GetClip(clipName);
	_isEnd = false;
	_curFrameX = 0;
	_frameTime = 0;
	renderer->ChangeTargetBitmap(clipName);
}

void Animator::SetClip(string clipName, int startFrame)
{
	preClip = curClip;
	curClip = GetClip(clipName);
	_isEnd = false;
	_curFrameX = startFrame;
	_frameTime = 0;
	renderer->ChangeTargetBitmap(clipName, startFrame);
}

void Animator::AddClip(string clipName, AnimationClip* newClip)
{
	clipMap.insert(make_pair(clipName, newClip));
}

void Animator::AddClip(string clipName)
{
	clipMap.insert(make_pair(clipName, CLIPMANAGER->FindClip(clipName)));
}

void Animator::AddClip(AnimationClip* newClip)
{
	if (newClip->GetLoadName().length() == 0)
		return;
	clipMap.insert(pair<string, AnimationClip*>(newClip->GetLoadName(), newClip));
}

AnimationClip* Animator::GetClip(string clipName)
{
	map<string, AnimationClip*>::iterator iter;
	iter = clipMap.find(clipName);
	if (iter != clipMap.end()) {
		return iter->second;
	}
	return nullptr;
}

void Animator::AddTransaction(string name, AnimationClip* startClip, AnimationClip* nextClip)
{
	TRANSACTION newTransaction = { startClip, nextClip };
	transactionMap.insert(make_pair( name, newTransaction));
}

void Animator::Pause()
{
	_isPause = true;
}

void Animator::Resume()
{
	_isPause = false;
}
