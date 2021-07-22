#pragma once

class ImageObject;

class PlayerLaser
{
public:
	ImageObject* _collectLaserFirst;	//�ڿ����� ������ ����
	ImageObject* _collectLaserEnd;		//�ڿ����� ������ ��
	ImageObject* _collectLaser;			//�ڿ����� ������ �߰�
	ImageObject* _detectRC;				//�ڿ� Ž���� ��Ʈ


private:
	float _laserStartX, _laserStartY;
	float _laserEndX, _laserEndY;
	float _laserX, _laserY;				//�߰� ������ ��ǥ
	float _laserDistance;				//������ ��ŸƮ�� ������ �Ÿ�
	float _laserAngle;					//������ �ޱ۰�
	float _laserAlphaTime;				//������ ���ĺ��� �ð�
	int _rcRotate;						//������ Ž���� ��Ʈ ȸ����
	float _rcRotateTime;				//������ Ž���� ��Ʈ ȸ�� �ð�

public:
	PlayerLaser();
	~PlayerLaser();

	void Init();
	void Update();
	void Render();

	void ShootLaser();			//������ �߻� �Լ�
	void LaserAlpha();			//������ ���ĺ���
	void RcRotate();			//������ Ž�� ��Ʈ ȸ��
	void SetImage();
	void OffLaser();
	void SetLaserStartPoint(float laserStartX, float laserStartY) { _laserStartX = laserStartX; _laserStartY = laserStartY; }
	pair <float, float> GetLaserStartPoint() { return { _laserStartX, _laserStartY }; }
	void SetLaserEndPoint(int laserEndX, int laserEndY) { _laserEndX = laserEndX; _laserEndY = laserEndY; }
	pair <float, float> GetLaserEndPoint() { return { _laserEndX, _laserEndY }; }
	void SetLaserPoint(float laserX, float laserY) { _laserX = laserX; _laserY = laserY; }
	pair <float, float> GetLaserPoint() { return { _laserX, _laserY }; }
	void SetLaserDistance(float laserDistance) { _laserDistance = laserDistance; }
	float GetLaserDistance() { return _laserDistance; }
	void SetLaserAngle(float laserAngle) { _laserAngle = laserAngle; }
	float GetLaserAngle() { return _laserAngle; }


};

