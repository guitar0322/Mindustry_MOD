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
	float _constructDistance;							//������ ��ŸƮ�� ������ �Ÿ�
	float _constructAngle;					//������ �ޱ۰�
	bool _isLaserSizeL;
	bool _isDelete;
public:
	PlayerConstructLaser();
	~PlayerConstructLaser();

	void Init();
	void Update();
	void Render();

	void ShootLaser();			//������ �߻� �Լ�
	void SetImage();

	void SetConstructStartPoint(int constructStartX, int constructStartY) { _constructStartX = constructStartX; _constructStartY = constructStartY; }
	void SetConstructEndPoint(int constructEndX, int constructEndY) { _constructEndX = constructEndX; _constructEndY = constructEndY; }
	Vector2 GetConstructEndPoint() const { return Vector2(_constructEndX, _constructEndY); }
	void SetConstructAngle(float constructAngle) { _constructAngle = constructAngle; }
	void SetConstructDistance(float constructDistance) { _constructDistance = constructDistance; }
	float GetConstructDistance() { return _constructDistance; }
	void SetIsLaserSizeL(bool isLaserSizeL) { _isLaserSizeL = isLaserSizeL; }
	void SetIsDelete(bool isDelete) { _isDelete = isDelete; }
	void OnConstructLaser();
	void OffConstructLaser();
};

