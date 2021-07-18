#pragma once
class Camera;
class CameraManager : public singletonBase<CameraManager>
{
private:
	vector<Camera*> _cameraList;
	Camera* _mainCam;
public:
	CameraManager();
	~CameraManager();
	Camera* GetMainCam() { return _mainCam; }
	void Init();
	void Release();
	void AddCamera(Camera* newCamera);
	void SetMainCam(Camera* mainCam);
};

