#pragma once
#include "singletonBase.h"
#include "timer.h"

class TimeManager : public singletonBase<TimeManager>
{
private:
	Timer* _timer;

public:
	TimeManager();
	~TimeManager();

	HRESULT init();
	void release();
	void update(float lock = 0.0f);
	void render(HDC hdc);

	inline float getElapsedTime() const { return _timer->getElapsedTime(); }
	inline float getWorldTime() const { return _timer->getWorldTime(); }
	inline int getFPS() const { return _timer->getFrameRate(); }
};

