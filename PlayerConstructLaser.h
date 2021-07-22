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
	float _laserStartX, _laserStartY;

public:
	PlayerConstructLaser();
	~PlayerConstructLaser();

	void Init();
	void Update();
	void Render();

	void ShootLaser();			//레이저 발사 함수
	void SetImage();

	void SetLaserStartPoint(float laserStartX, float laserStartY) { _laserStartX = laserStartX; _laserStartY = laserStartY; }


};

