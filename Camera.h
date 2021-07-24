#pragma once
#include "Component.h"

/*************************************************************
* Framework Camera Component
* by ȫ�뿵
* up to date 21-07-09
* # Property @ Function
* # int _screenWidth, int _screenHeight : ī�޶� ��ũ�� ũ��
* # int _renderWidth, _renderHeight : ī�޶� �Կ� ����
* # bool _isShake : ī�޶� ��鸲 ����
* # shakeWeight : ī�޶� ��鸲 ����
* # float _zoomScale : ī�޶� Ȯ�� ��� ����
* 
*************************************************************/

class Camera : public Component
{
private :
	float _screenWidth, _screenHeight;
	float _screenStartX, _screenStartY;
	float _renderWidth, _renderHeight;
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

	void SetScreenStart(float x, float y) { _screenStartX = x; _screenStartY = y; }
	pair<int, int> GetScreenStart() { return { _screenStartX, _screenStartY }; }

	float GetCameraStartX() { return _cameraStartX; }
	float GetCameraStartY() { return  _cameraStartY; }

	//pair<float, float> GetCameraStart() { return { _cameraStartX, _cameraStartY }; }

	void SetScreenWidth(float width) { _screenWidth = width; }
	void SetScreenHeight(float height) { _screenHeight = height; }
	void SetScreenSize(float width, float height) { _screenWidth = width; _screenHeight = height; }
	float GetScreenWidth() { return _screenWidth; }
	float GetScreenHeight() { return _screenHeight; }
	pair<float, float> GetScreenSize() { return { _screenWidth, _screenHeight }; }

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

