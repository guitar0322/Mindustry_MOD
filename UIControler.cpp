#include "stdafx.h"
#include "UIControler.h"
#include "TileInfo.h"

UIControler::UIControler()
	:_previewDir(false), _previewNum(0)
{
}

UIControler::~UIControler()
{
}

void UIControler::Init()
{
}

void UIControler::Update()
{
	if (propPreview->isActive == true)
	{
		Vector2 worldMouse = ScreenToWorld(_ptMouse);
		int tileX = worldMouse.x / TILESIZE;
		int tileY = worldMouse.y / TILESIZE;
		if (_previewV.empty() == true)
		{
			propPreview->transform->SetPosition(tileX * TILESIZE + 16, tileY * TILESIZE + 16);
		}
		else
		{
			propPreview->transform->SetPosition(_previewV[_previewV.size() - 1].transform->position);
		}
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_worldStartPtMouse = ScreenToWorld(_ptMouse);
		}
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			/********************************************************************
			* �̸����� ���� ����
			* 1. ��������� ������� ��ġ�� ����ؼ� �ִ� ���
			* 2. �������->���������θ� ���°����� ����
			* 3. ���콺�� Ŭ���� start�������� ���� ���콺 ��ġ������ deltaX, deltaY����
			* 4.y�� �� ũ�� ������������ ����
			* 5.x�� �� ũ�� ����������� ����
			* 5-1. �������� �̸����⸦ ��� �ڷᱸ���� �����ϰ� ������ ���ΰ�?
			* 5-2. �̸����ⰳ��, ������ �����Ӹ��� ���ϰ� �����ϳ��� �޶����ٸ� 
			*	�Լ��� ȣ���Ͽ� ������ ���̸� ���� Ȥ�� ��ġ�� �����Ѵ�.
			* 6.���콺�� ���� ť�� �߰�
			********************************************************************/
			float deltaX = ScreenToWorld(_ptMouse).x - _worldStartPtMouse.x;
			float deltaY = ScreenToWorld(_ptMouse).y - _worldStartPtMouse.y;
			SetPreview(deltaX, deltaY);
		}

		if (KEYMANAGER->isOnceKeyUp(VK_RBUTTON))
		{
			RefreshPreview();
		}

		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			propFactory->AddPropElem(_previewV, _selectCategoryIdx, _selectPropIdx);
			RefreshPreview();
		}
	}
	for (int i = 0; i < _previewV.size(); i++)
	{
		_previewV[i].Update();
	}
}

void UIControler::Release()
{
	NEW_SAFE_RELEASE(propFactory);
	SAFE_DELETE(propFactory);
}

void UIControler::Render()
{
	//for (_previewMapIter = _previewMap.begin(); _previewMapIter != _previewMap.end(); _previewMapIter++)
	//{
	//	_previewMapIter->second.Render();
	//}
	for (int i = 0; i < _previewV.size(); i++)
	{
		_previewV[i].Render();
	}
}

void UIControler::ClickCategoryIcon(GameObject* clickedButton, int category)
{
	categorySelect->transform->SetPosition(clickedButton->transform->GetX(), clickedButton->transform->GetY());
	_selectCategoryIdx = category;
	propSelect->SetActive(false);
	for (int i = 0; i < preIconV->size(); i++)
	{
		(*preIconV)[i]->SetActive(false);
	}
	switch (category)
	{
	case 0:
		preIconV = turretIconV;
		break;
	case 1:
		preIconV = drillIconV;
		break;
	case 2:
		preIconV = railIconV;
		break;
	case 3:
		preIconV = wallIconV;
		break;
	}
	for (int i = 0; i < preIconV->size(); i++)
	{
		(*preIconV)[i]->SetActive(true);
	}
}

void UIControler::ClickPropIcon(GameObject* clickedButton, int propIdx)
{
	if (propSelect->transform->position == clickedButton->transform->position && propSelect->isActive == true)
	{
		propSelect->SetActive(false);
		propPreview->SetActive(false);
		_selectPropIdx = -1;
	}
	else
	{
		propSelect->SetActive(true);
		propPreview->SetActive(true);
		propPreview->renderer->ChangeTargetBitmap(clickedButton->GetComponent<UIRenderer>()->GetClipName());
		propSelect->transform->SetPosition(clickedButton->transform->GetX(), clickedButton->transform->GetY());
		_selectPropIdx = propIdx;
	}
}

void UIControler::RefreshPreview()
{
	_previewV.clear();
	propPreview->SetActive(false);
	propSelect->SetActive(false);
	_previewNum = 0;
	_previewDir = false;
}

void UIControler::SetPreview(float deltaX, float deltaY)
{
	int tileNumX = deltaX / TILESIZE;
	int tileNumY = deltaY / TILESIZE;
	bool curDir = Math::Abs(tileNumX) > Math::Abs(tileNumY);
	int bigNum = Math::Max(Math::Abs(tileNumX), Math::Abs(tileNumY));
	if (_previewNum == bigNum && _previewDir == curDir)
	{
		return;
	}
	int startX = _worldStartPtMouse.x / TILESIZE;
	int startY = _worldStartPtMouse.y / TILESIZE;
	_previewV.clear();
	for (int i = 0; i < bigNum; i++)
	{
		ImageObject newPreview;
		newPreview.renderer->Init(propPreview->renderer->GetClipName());
		newPreview.renderer->SetAlpha(0.5f);
		_previewV.push_back(newPreview);
	}
	_previewNum = bigNum;
	_previewDir = curDir;
	for (int i = 0; i < _previewV.size(); i++)
	{
		_previewV[i].transform->SetPosition(
			startX * TILESIZE + 16 + TILESIZE * i * Math::NegativeChecking(tileNumX) * (Math::Abs(tileNumX) > Math::Abs(tileNumY)),
			startY * TILESIZE + 16 + TILESIZE * i * Math::NegativeChecking(tileNumY) * (Math::Abs(tileNumX) <= Math::Abs(tileNumY))
		);
	}
}

void UIControler::ActiveChoiceImg(Transform* menuTr, bool isActive)
{
	choiceImg->transform->SetPosition(menuTr->GetX(), menuTr->GetY());
	choiceImg->SetActive(isActive);
}
