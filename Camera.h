#pragma once
#include "Component.h"

/*************************************************************
* Framework Camera Component
* by 홍대영
* up to date 21-07-09
* # Property @ Function
* # int _screenWidth, int _screenHeight : 카메라 스크린 크기
* # int _renderWidth, _renderHeight : 카메라 촬영 범위
* # bool _isShake : 카메라 흔들림 여부
* # shakeWeight : 카메라 흔들림 강도
* # float _zoomScale : 카메라 확대 축소 비율
* 
*************************************************************/

class Camera : public Component
{
private :
	int _screenWidth, _screenHeight;
	int _screenStartX, _screenStartY;
	int _renderWidth, _renderHeight;
	float _cameraStartX, _cameraStartY;
	bool _isShake;
	int _shakeWeight;
	int _shakeNum;
	int _shakeMode;
	float _shakeAngle;
	int _shakeDir;
	pair<float, float> _shakeStart;
	Rect _renderRc;
public:
	Camera();
	~Camera();
	float _zoomScale;
	void ResizeScreen(int screenWidth, int screenHeight);
	virtual void Init();
	virtual void Render();
	virtual void Update();

	void SetScreenStart(int x, int y) { _screenStartX = x; _screenStartY = y; }
	pair<int, int> GetScreenStart() { return { _screenStartX, _screenStartY }; }

	float GetCameraStartX() { return _cameraStartX; }
	float GetCameraStartY() { return  _cameraStartY; }

	//pair<float, float> GetCameraStart() { return { _cameraStartX, _cameraStartY }; }

	void SetScreenWidth(int width) { _screenWidth = width; }
	void SetScreenHeight(int height) { _screenHeight = height; }
	void SetScreenSize(int width, int height) { _screenWidth = width; _screenHeight = height; }
	int GetScreenWidth() { return _screenWidth; }
	int GetScreenHeight() { return _screenHeight; }
	pair<int, int> GetScreenSize() { return { _screenWidth, _screenHeight }; }

	void SetRenderWidth(int width) { _renderWidth = width; }
	void SetRenderHeight(int height) { _renderHeight = height; }
	void SetRenderSize(int width, int height) { _renderWidth = width; _renderHeight = height;}
	void Shake(int weight, int mode);
	void ShakeOff();
	float GetRenderWidth() { return _renderWidth / _zoomScale; }
	float GetRenderHeight() { return _renderHeight / _zoomScale; }

	Rect GetRenderRc() const { return _renderRc; }
	pair<int, int> GetRenderSize() { return { _renderWidth / _zoomScale, _renderHeight / _zoomScale }; }

	void StaticToBackBuffer();
};

