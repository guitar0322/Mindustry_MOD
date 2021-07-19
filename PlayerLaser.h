#pragma once

class ImageObject;

class PlayerLaser
{
public:
	ImageObject* _collectLaserFirst;	//자원추출 레이저 시작
	ImageObject* _collectLaserEnd;		//자원추출 레이저 끝
	ImageObject* _collectLaser;			//자원추출 레이저 중간
	ImageObject* _detectRc;				//자원 탐지용 렉트

private:
	float _laserStartX, _laserStartY;
	float _laserEndX, _laserEndY;
	float _laserX, _laserY;				//중간 레이저 좌표
	float _laserDistance;				//레이저 스타트와 엔드의 거리
	float _laserAngle;					//레이저 앵글값
	float _laserAlphaTime;				//레이저 알파블랜더 시간
	int _rcRotate;						//레이저 탐지용 렉트 회전값
	float _rcRotateTime;				//레이저 탐지용 렉트 회전 시간
	

public:
	PlayerLaser();
	~PlayerLaser();

	void Init();
	void Update();
	void Render();

	void ShootLaser();			//레이저 발사 함수
	void LaserAlpha();			//레이저 알파블랜드
	void RcRotate();			//레이저 탐지 렉트 회전
	void SetImage();

	void SetLaserStartPoint(float laserStartX, float laserStartY) { _laserStartX = laserStartX; _laserStartY = laserStartY; }
	pair <float, float> GetLaserFirstPoint() { return { _laserStartX, _laserStartY }; }
	void SetLaserEndPoint(int laserEndX, int laserEndY) { _laserEndX = laserEndX; _laserEndY = laserEndY; }
	pair <float, float> GetLaserEndPoint() { return { _laserEndX, _laserEndY }; }
	void SetLaserPoint(float laserX, float laserY) { _laserX = laserX; _laserY = laserY; }
	pair <float, float> GetLaserPoint() { return { _laserX, _laserY }; }
	void SetLaserDistance(float laserDistance) { _laserDistance = laserDistance; }
	float GetLaserDistance() { return _laserDistance; }
	void SetLaserAngle(float laserAngle) { _laserAngle = laserAngle; }
	float GetLaserAngle() { return _laserAngle; }


};

