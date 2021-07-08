#pragma once
class ID2D1Bitmap;

class AnimationClip
{
private:
	ID2D1Bitmap* _clipBitmap;
	string _loadName;
	float _frameWidth;
	float _frameHeight;
	float _frameTerm;
	int _frameNum;
	bool _isLoop;
public:
	AnimationClip();
	~AnimationClip();
	HRESULT Init(ID2D1Bitmap* clipBitmap, float wholeWidth, float wholeHeight, int frameNumX, int frameNumY, float frameTerm, bool isLoop);

	ID2D1Bitmap* GetBitmap() const { return _clipBitmap; }
	float GetFrameWidth() const { return _frameWidth; }
	float GetFrameHeight() const { return _frameHeight; }
	float GetFrameTerm() const { return _frameTerm; }
	int GetFrameNum() const { return _frameNum; }
	bool GetIsLoop() const { return _isLoop; }
	void SetIsLoop(bool isLoop) { _isLoop = isLoop; }

	void SetLoadName(string loadName) { _loadName = loadName; }
	string GetLoadName() const { return _loadName; }
};

