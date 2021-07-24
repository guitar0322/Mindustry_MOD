#pragma once
#include "Component.h"
class UIAnimator :
	public Component
{
private:
	float _frameTime;
	bool _isPause;
	bool _isEnd;
	int _curFrameX;
	int _curFrameY;
public:
	UIAnimator();
	~UIAnimator();

	UIRenderer* uiRenderer;
	AnimationClip* curClip;
	AnimationClip* preClip;
	map<string, AnimationClip*> clipMap;

	virtual void Init();
	virtual void Update();

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
	void Pause();
	void Resume();
	bool GetEnd() const { return _isEnd; }

};

