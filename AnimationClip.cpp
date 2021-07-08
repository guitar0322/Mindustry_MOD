#include "stdafx.h"
#include "AnimationClip.h"

HRESULT AnimationClip::Init(ID2D1Bitmap* clipBitmap, float wholeWidth, float wholeHeight, int frameNumX, int frameNumY, float frameTerm, bool isLoop)
{
	_clipBitmap = clipBitmap;
	_frameWidth = wholeWidth / frameNumX;
	_frameHeight = wholeHeight / frameNumY;
	_frameTerm = frameTerm;
	_frameNum = frameNumX;
	_isLoop = isLoop;

	return S_OK;
}

AnimationClip::AnimationClip()
{
	_loadName.clear();
}

AnimationClip::~AnimationClip()
{

}
