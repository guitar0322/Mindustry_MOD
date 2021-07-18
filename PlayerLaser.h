#pragma once

class ImageObject;

class PlayerLaser
{
public:
	ImageObject* _collectLaserFirst;	//�ڿ����� ������ ����
	ImageObject* _collectLaserEnd;		//�ڿ����� ������ ��
	ImageObject* _collectLaser;			//�ڿ����� ������ �߰�
	ImageObject* _detectRc;				//�ڿ� Ž���� ��Ʈ

private:
	float _laserStartX, _laserStartY;
	int _laserEndX, _laserEndY;
	float _laserX, _laserY;
	float _laserDistance;


public:
	PlayerLaser();
	~PlayerLaser();

	void Init();
	void Update();
	void Render();

	void ShootLaser();

	void SetImage();

	void SetLaserStartPoint(float laserStartX, float laserStartY) { _laserStartX = laserStartX; _laserStartY = laserStartY; }
	pair <float, float> GetLaserFirstPoint() { return { _laserStartX, _laserStartY }; }
	void SetLaserEndPoint(float laserEndX, float laserEndY) { _laserEndX = laserEndX; _laserEndY = laserEndY; }
	pair <float, float> GetLaserEndPoint() { return { _laserEndX, _laserEndY }; }
	void SetLaserPoint(float laserX, float laserY) { _laserX = laserX; _laserY = laserY; }
	pair <float, float> GetLaserPoint() { return { _laserX, _laserY }; }
	void SetLaserDistance(float laserDistance) { _laserDistance = laserDistance; }
	float GetLaserDistance() { return { _laserDistance }; }


};

