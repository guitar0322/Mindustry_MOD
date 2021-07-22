#pragma once

class ImageObject;

class PlayerConstructLaser
{
public:
	ImageObject* _constructLaserRC;
	ImageObject* _constuctLaserSizeS;
	ImageObject* _constuctLaserSizeL;
	ImageObject* _deleteLaserRC;
	ImageObject* _deleteLaserSizeS;
	ImageObject* _deleteLaserSizeL;

private:
	int _constructStartX, _constructStartY;
	float _constructEndX, _constructEndY;
	float _constructX, _constructY;				//중간 레이저 좌표
	float _constructDistance;							//레이저 스타트와 엔드의 거리
	float _constructAngle;					//레이저 앵글값
	bool _isLaserSizeL;

public:
	PlayerConstructLaser();
	~PlayerConstructLaser();

	void Init();
	void Update();
	void Render();

	void ShootLaser();			//레이저 발사 함수
	void SetImage();

	void SetConstructStartPoint(int constructStartX, int constructStartY) { _constructStartX = constructStartX; _constructStartY = constructStartY; }
	void SetConstructEndPoint(int constructEndX, int constructEndY) { _constructEndX = constructEndX; _constructEndY = constructEndY; }
	void SetConstructAngle(float constructAngle) { _constructAngle = constructAngle; }
	void SetConstructDistance(float constructDistance) { _constructDistance = constructDistance; }
	float GetConstructDistance() { return _constructDistance; }
	void SetIsLaserSizeL(bool isLaserSizeL) { _isLaserSizeL = isLaserSizeL; }
	void OnConstructLaser();
	void OffConstructLaser();
};

