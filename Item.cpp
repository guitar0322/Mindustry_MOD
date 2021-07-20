#include "stdafx.h"
#include "Item.h"
#include "TileInfo.h"
#include "Conveyor.h"
#include "PropContainer.h"
#include "Transport.h"
int moveDir[4][2] = { {1, 0},{0,1},{-1,0},{0,-1} };

Item::Item(RESOURCE type)
	:_speed(45.f), _isOverCenter(false)
{
	_type = type;
	tag = TAGMANAGER->GetTag("resource");

	renderer = new Renderer();
	AddComponent(renderer);
	switch (_type) {
	case COPPER:
		renderer->Init(resClipName[COPPER]);
		break;
	case LEAD:
		renderer->Init(resClipName[LEAD]);
		break;
	}

	collider = new BoxCollider();
	AddComponent(collider);
	collider->Init();
	collider->SetIsTrigger(false);
	collider->SetSize(20, 16);
}

Item::~Item()
{
}

void Item::Update()
{
	GameObject::Update();
	int tileX = transform->GetX() / TILESIZE;
	int tileY = transform->GetY() / TILESIZE;
	if (_preTile.first != tileX || _preTile.second != tileY)
	{
		_preTile.first = tileX;
		_preTile.second = tileY;
		_curConveyor = dynamic_cast<Conveyor*>(_propContainer->GetPropMap(_preTile.second * TILENUMX + _preTile.first));
		if (_curConveyor != nullptr)
		{
			SetConveyor(_curConveyor);
		}
		else
		{
			_speed = 0;
		}
	}
	if (_speed != 0.f)
	{
		transform->Move(_speed * TIMEMANAGER->getElapsedTime() * moveDir[_dir][0], _speed * TIMEMANAGER->getElapsedTime() * moveDir[_dir][1]);
		if (_isOverCenter == false) {
			switch (_dir) {
			case 0:
				if (_curConveyor->transform->GetX() < transform->GetX())
				{
					transform->SetPosition(_curConveyor->transform->position);
					_dir = _curConveyor->transport->GetOutDir();
					_isOverCenter = true;
				}
				break;
			case 1:
				if (_curConveyor->transform->GetY() < transform->GetY())
				{
					transform->SetPosition(_curConveyor->transform->position);
					_dir = _curConveyor->transport->GetOutDir();
					_isOverCenter = true;
				}
				break;
			case 2:
				if (_curConveyor->transform->GetX() > transform->GetX())
				{
					transform->SetPosition(_curConveyor->transform->position);
					_dir = _curConveyor->transport->GetOutDir();
					_isOverCenter = true;
				}
				break;
			case 3:
				if (_curConveyor->transform->GetY() > transform->GetY())
				{
					transform->SetPosition(_curConveyor->transform->position);
					_dir = _curConveyor->transport->GetOutDir();
					_isOverCenter = true;
				}
				break;
			}
		}
	}

}

void Item::SetConveyor(Conveyor* conveyor)
{
	_curConveyor = conveyor;
	_isOverCenter = false;
	_speed = 45.f;
	if (_curConveyor->transform->GetX() > transform->GetX())
		_dir = 0;
	else if (_curConveyor->transform->GetY() > transform->GetY())
		_dir = 1;
	else if (_curConveyor->transform->GetX() < transform->GetX())
		_dir = 2;
	else if (_curConveyor->transform->GetY() < transform->GetY())
		_dir = 3;
}
