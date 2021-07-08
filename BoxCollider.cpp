#include "stdafx.h"
#include "BoxCollider.h"

BoxCollider::BoxCollider()
{
	_width = 100;
	_height = 100;
	_isTrigger = true;
	_colliderCheckOffset = 50;
}

BoxCollider::~BoxCollider()
{

}

void BoxCollider::Init()
{
	COLLIDERMANAGER->InsertCollider(this);
}

void BoxCollider::Update()
{
	_rc = RectMakeCenter(transform->GetX(), transform->GetY(), _width, _height);
	TriggerEventHandler();
	//if (isTrigger == false) return;
	//int colNum = COLLIDERMANAGER->colliderList.size();
	//for (int i = 0; i < colNum; i++) {
	//	if (CheckCollision(GetCenterX(_rc), GetCenterY(_rc), i)) {
	//		vCol.push_back(i);
	//	}
	//}
	//for (int i = 0; i < vCol.size(); i++) {
	//	bool isExist = false;
	//	for (int j = 0; j < prevCol.size(); j++) {
	//		 if(vCol[i] == prevCol[j]) {
	//			if (gameObject->isActive == true)
	//				gameObject->OnTriggerStay(COLLIDERMANAGER->colliderList[prevCol[j]]->gameObject);
	//			isExist = true;
	//			break;
	//		}
	//	}
	//	if (isExist == false) {
	//		if(gameObject->isActive == true)
	//			gameObject->OnTriggerEnter(COLLIDERMANAGER->colliderList[vCol[i]]->gameObject);
	//	}
	//}

	//for (int i = 0; i < prevCol.size(); i++) {
	//	bool isExist = false;
	//	for (int j = 0; j < vCol.size(); j++) {
	//		if (vCol[j] == prevCol[i]) {
	//			isExist = true;
	//			break;
	//		}
	//	}
	//	if (isExist == false) {
	//		if (gameObject->isActive == true)
	//			gameObject->OnTriggerExit(COLLIDERMANAGER->colliderList[prevCol[i]]->gameObject);
	//	}
	//}

	//prevCol.clear();
	//prevCol.assign(vCol.begin(), vCol.end());
	//vCol.clear();
}
bool BoxCollider::CheckCollision(float tempX, float tempY) {
	if (enable == false) {
		return false;
	}
	
	/*int colNum = COLLIDERMANAGER->colliderList.size();
	int deltaX = tempX - transform->GetX();
	int deltaY = tempY - transform->GetY();
	int marginX = 0, marginY = 0;
	for (int i = 0; i < colNum; i++) {
		if (CheckCollision(tempX, tempY, i)) {
			if (COLLIDERMANAGER->colliderList[i]->isTrigger == false && this->isTrigger == false) {
				int w = intersectRc.right - intersectRc.left;
				int h = intersectRc.bottom - intersectRc.top;
				if (w <= h) {
					deltaX >= 0 ? marginX = deltaX - w : marginX = deltaX + w;
				}
				else {
					deltaY >= 0 ? marginY = deltaY - h : marginY = deltaY + h;
				}
				string targetName = COLLIDERMANAGER->colliderList[i]->gameObject->name;
				gameObject->OnCollision(COLLIDERMANAGER->colliderList[i]->gameObject);
				if (weight > COLLIDERMANAGER->colliderList[i]->weight) {
					bool isLack = false;
					for (int j = 0; j < colNum; j++) {
						if (COLLIDERMANAGER->colliderList[j]->isTrigger == false  &&
							COLLIDERMANAGER->colliderList[j] != COLLIDERMANAGER->colliderList[i] &&
							CheckCollision(COLLIDERMANAGER->colliderList[i]->rc, j)) {
							string name = COLLIDERMANAGER->colliderList[j]->gameObject->name;
							int bottom = COLLIDERMANAGER->colliderList[i]->rc.bottom;
							int top = COLLIDERMANAGER->colliderList[j]->rc.top;
   							isLack = true;
							break;
						}
					}
					if (isLack == true) {
						COLLIDERMANAGER->colliderList[i]->isTrigger = true;
					}
					else {
						COLLIDERMANAGER->colliderList[i]->transform->Move(deltaX - marginX, deltaY - marginY);
					}
					return false;
				}
				else {
					bool isLack = false;
					for (int j = 0; j < colNum; j++) {
						if (COLLIDERMANAGER->colliderList[j]->isTrigger == false &&
							COLLIDERMANAGER->colliderList[j] != COLLIDERMANAGER->colliderList[i] && 
							CheckCollision(transform->GetX() + marginX, transform->GetY() + marginY, j)) {
							isLack = true;
							string name = COLLIDERMANAGER->colliderList[j]->gameObject->name;
  							break;
						}
					}
					if (isLack == true) {
						this->isTrigger = true;
					}
					else {
						transform->Move(marginX, marginY);
					}
					return true;
				}
			}
		}
	}*/
	return false;
}

bool BoxCollider::CheckCollision()
{
	vector<BoxCollider*> aroundColliderV = COLLIDERMANAGER->GetAroundCollider(this, _colliderCheckOffset);
	_rc = RectMakeCenter(transform->GetX(), transform->GetY(), _width, _height);
	bool result = false;
	for (int i = 0; i < aroundColliderV.size(); i++)
	{
		if (aroundColliderV[i]->gameObject->isActive == false) continue;
		if (aroundColliderV[i]->enable == false) continue;

		if (IntersectRect(&_intersectRc, &this->_rc, &aroundColliderV[i]->_rc))
		{
			if (this->_isTrigger == false && aroundColliderV[i]->_isTrigger == false)
			{
				int w = _intersectRc.right - _intersectRc.left;
				int h = _intersectRc.bottom - _intersectRc.top;
				if (w > h)
				{
					if (_intersectRc.bottom == aroundColliderV[i]->_rc.bottom)
					{
						this->transform->MoveY(h);
					}
					else if(_intersectRc.top == aroundColliderV[i]->_rc.top)
					{
						this->transform->MoveY(-h);
					}
				}
				else
				{
					if (_intersectRc.left == aroundColliderV[i]->_rc.left)
					{
						this->transform->MoveX(-w);
					}
					else if (_intersectRc.right == aroundColliderV[i]->_rc.right)
					{
						this->transform->MoveX(w);
					}
				}
				result = true;
				this->gameObject->OnCollision(aroundColliderV[i]->gameObject);
			}
			else if (this->_isTrigger == true)
			{
				_overlapColV.push_back(aroundColliderV[i]);
				this->gameObject->OnTriggerEnter(aroundColliderV[i]->gameObject);
				aroundColliderV[i]->_overlapColV.push_back(this);
				aroundColliderV[i]->gameObject->OnTriggerEnter(this->gameObject);
			}
		}
	}

	return result;
}

bool BoxCollider::CheckCollision(float tempX, float tempY, int colIdx)
{
	Rect tempRc = RectMakePivot(Vector2(tempX, tempY), Vector2(_width, _height), Pivot::Center);
	Rect targetRc;
	if (&(this->_rc) == &(COLLIDERMANAGER->colliderList[colIdx]->_rc)) return false;
	if (COLLIDERMANAGER->colliderList[colIdx]->gameObject->isActive == false) return false;
	if (COLLIDERMANAGER->colliderList[colIdx]->enable == false) return false;
	targetRc = COLLIDERMANAGER->colliderList[colIdx]->_rc;
	if (IntersectRect(&_intersectRc, &tempRc, &targetRc)) {
		int w = _intersectRc.right - _intersectRc.left;
		int h = _intersectRc.bottom - _intersectRc.top;
		if (h >= w) {
			if (_intersectRc.right <= (targetRc.right + targetRc.left) / 2) {
			}
			else {
			}
		}
		else {
		}
		return true;
	}
	return false;
}

bool BoxCollider::CheckCollision(Rect rc, int colIdx)
{
	Rect targetRc;
	if (&(this->_rc) == &(COLLIDERMANAGER->colliderList[colIdx]->_rc)) return false;
	if (COLLIDERMANAGER->colliderList[colIdx]->gameObject->isActive == false) return false;
	if (COLLIDERMANAGER->colliderList[colIdx]->enable == false) return false;
	targetRc = COLLIDERMANAGER->colliderList[colIdx]->_rc;
	if (IntersectRect(&_intersectRc, &rc, &targetRc)) {
		int w = _intersectRc.right - _intersectRc.left;
		int h = _intersectRc.bottom - _intersectRc.top;
		if (h >= w) {
			if (_intersectRc.right <= GetCenterX(targetRc)) {
			}
			else {
			}
		}
		else {
		}
		return true;
	}
	return false;
}
void BoxCollider::TriggerEventHandler()
{
	for (int i = 0; i < _overlapColV.size(); i++)
	{
		if (!IntersectRect(&_overlapColV[i]->_rc, &this->_rc))
		{
			RemoveOverlapCol(_overlapColV[i]);
			this->gameObject->OnTriggerExit(_overlapColV[i]->gameObject);
			_overlapColV[i]->gameObject->OnTriggerExit(this->gameObject);
		}
		else
		{
			this->gameObject->OnTriggerStay(_overlapColV[i]->gameObject);
			_overlapColV[i]->gameObject->OnTriggerStay(this->gameObject);
		}
	}
}
void BoxCollider::SetWidth(float width)
{
	this->_width = width;
	_rc = RectMakeCenter(transform->GetX(), transform->GetY(), width, _height);
}
void BoxCollider::SetHeight(float height)
{
	this->_height = height;
	_rc = RectMakeCenter(transform->GetX(), transform->GetY(), _width, height);
}
void BoxCollider::SetSize(float width, float height)
{
	this->_width = width;
	this->_height = height;
	_rc = RectMakeCenter(transform->GetX(), transform->GetY(), width, height);
}

void BoxCollider::RemoveOverlapCol(BoxCollider* exitCollider)
{
	for (int i = 0; i < _overlapColV.size(); i++)
	{
		if (exitCollider == _overlapColV[i])
		{
			_overlapColV.erase(_overlapColV.begin() + i);
			break;
		}
	}
}
void BoxCollider::Render()
{
	D2DRENDERER->DrawRectangle(_rc, D2DRenderer::DefaultBrush::Green);
}

void BoxCollider::OnDisable()
{
	//COLLIDERMANAGER->EraseCollider(this);
	COLLIDERMANAGER->RemoveCollider(this);
}

void BoxCollider::OnEnable()
{
	//COLLIDERMANAGER->AddCollider(this);
	COLLIDERMANAGER->InsertCollider(this);
}
