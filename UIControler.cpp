#include "stdafx.h"
#include "UIControler.h"
#include "TileInfo.h"

UIControler::UIControler()
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
		propPreview->transform->SetPosition(tileX * TILESIZE + 16, tileY * TILESIZE + 16);
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			_previewMapIter = _previewMap.find(tileX + tileY * TILENUMX);
			if (_previewMapIter == _previewMap.end())
			{
				ImageObject preView;
				preView.renderer->Init(propPreview->renderer->GetClipName());
				preView.renderer->SetAlpha(0.5f);
				preView.transform->SetPosition(tileX * TILESIZE + 16, tileY * TILESIZE + 16);
				_previewMap.insert(pair<int, ImageObject>(tileX + tileY * TILENUMX, preView));
				_propQueue.push(tileX + tileY * TILENUMX);
			}
		}

		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			propFactory->AddPropElem(&_propQueue, _selectCategoryIdx, _selectPropIdx);
			_previewMap.clear();
			propPreview->SetActive(false);
			propSelect->SetActive(false);
		}
	}
}

void UIControler::Release()
{
	NEW_SAFE_RELEASE(propFactory);
	SAFE_DELETE(propFactory);
}

void UIControler::Render()
{
	for (_previewMapIter = _previewMap.begin(); _previewMapIter != _previewMap.end(); _previewMapIter++)
	{
		_previewMapIter->second.Render();
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

void UIControler::ActiveChoiceImg(Transform* menuTr, bool isActive)
{
	choiceImg->transform->SetPosition(menuTr->GetX(), menuTr->GetY());
	choiceImg->SetActive(isActive);
}
