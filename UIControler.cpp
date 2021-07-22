#include "stdafx.h"
#include "UIControler.h"
#include "TileInfo.h"
#include "Button.h"
#include "PropContainer.h"
#include "GameMap.h"
#include "EnemyManager.h"
#include "GameInfo.h"

UIControler::UIControler()
	:_previewDir(false), _previewNum(0)
{
}

UIControler::~UIControler()
{
}

void UIControler::Init()
{
	conveyorArrow.Init();
	conveyorArrow.renderer->Init("conveyor_arrow");
	conveyorArrow.SetActive(false);
	_dir = RIGHT;
}
void UIControler::Update()
{
	propPreview->Update();
	if (propPreview->isActive == true)
	{
		Vector2 worldMouse = ScreenToWorld(_ptMouse);
		int tileX = worldMouse.x / TILESIZE;
		int tileY = worldMouse.y / TILESIZE;
		if (_previewV.empty() == true)
		{
			if (_selectCategoryIdx != PRODUCTION)
			{
				propPreview->transform->SetPosition(tileX * TILESIZE + 16, tileY * TILESIZE + 16);
				conveyorArrow.transform->SetPosition(tileX * TILESIZE + 16, tileY * TILESIZE + 16);
			}
			else
			{
				int tileHalfX = worldMouse.x / (TILESIZE / 2);
				int tileHalfY = worldMouse.y / (TILESIZE / 2);
				if (tileHalfX % 2 != 0)
					tileHalfX += 1;
				if (tileHalfY % 2 != 0)
					tileHalfY += 1;

				propPreview->transform->SetPosition((tileHalfX / 2) * TILESIZE, (tileHalfY / 2) * TILESIZE);
			}
			CheckValidTile();

		}
		else
		{
			propPreview->transform->SetPosition(_previewV[_previewV.size() - 1].transform->position);
			conveyorArrow.transform->SetPosition(_previewV[_previewV.size() - 1].transform->position);
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
			*   �Լ��� ȣ���Ͽ� ������ ���̸� ���� Ȥ�� ��ġ�� �����Ѵ�.
			* 6.���콺�� ���� ť�� �߰�
			********************************************************************/
			float deltaX = ScreenToWorld(_ptMouse).x - _worldStartPtMouse.x;
			float deltaY = ScreenToWorld(_ptMouse).y - _worldStartPtMouse.y;
			if (_selectCategoryIdx != PRODUCTION)
				SetPreview(deltaX, deltaY);
			else
				SetPreviewTwo(deltaX, deltaY);
		}

		if (KEYMANAGER->isOnceKeyUp(VK_RBUTTON))
		{
			RefreshPreview();
			propPreview->SetActive(false);
			propSelect->SetActive(false);
			conveyorArrow.SetActive(false);
		}

		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			propFactory->AddPropElem(_previewV, _selectCategoryIdx, _selectPropIdx, _dir);
			RefreshPreview();
		}
	}
	for (int i = 0; i < _previewV.size(); i++)
	{
		_previewV[i].Update();
	}
	conveyorArrow.Update();
}

void UIControler::Release()
{
	NEW_SAFE_RELEASE(propFactory);
	SAFE_DELETE(propFactory);
}

void UIControler::Render()
{
	conveyorArrow.Render();
	propPreview->Render();
	if (Math::FloatEqual(propPreview->renderer->GetAlpha(), 0.4f) == true)
	{
		propPreview->renderer->DrawFillRect(D2D1::ColorF::Red);
	}
	for (int i = 0; i < _previewV.size(); i++)
	{
		_previewV[i].Render();
		if (Math::FloatEqual(_previewV[i].renderer->GetAlpha(), 0.4f) == true)
			_previewV[i].renderer->DrawFillRect(D2D1::ColorF::Red);
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


		if (_selectCategoryIdx == RAIL)
		{
			propPreview->transform->SetAngle(_dir * 90);
			conveyorArrow.transform->SetAngle((_dir + 1) % 4 * 90);
			conveyorArrow.SetActive(true);
		}
		propPreview->renderer->ChangeTargetBitmap(clickedButton->GetComponent<UIRenderer>()->GetClipName());
		propSelect->transform->SetPosition(clickedButton->transform->GetX(), clickedButton->transform->GetY());
		_selectPropIdx = propIdx;
	}
}

void UIControler::RefreshPreview()
{
	_previewV.clear();

	_previewNum = 0;
	_previewDir = false;
}

void UIControler::SetPreview(float deltaX, float deltaY)
{
	int tileNumX = deltaX / TILESIZE;
	int tileNumY = deltaY / TILESIZE;
	bool curDir = Math::Abs(tileNumX) > Math::Abs(tileNumY);
	int bigNum = Math::Max(Math::Abs(tileNumX), Math::Abs(tileNumY)) + 1;
	if (_previewNum == bigNum && _previewDir == curDir)
	{
		return;
	}

	if (_selectCategoryIdx == RAIL)
	{
		if (Math::Abs(tileNumX) > Math::Abs(tileNumY) && tileNumX < 0)
			_dir = LEFT;
		else if (Math::Abs(tileNumX) > Math::Abs(tileNumY) && tileNumX > 0)
			_dir = RIGHT;
		else if (Math::Abs(tileNumX) <= Math::Abs(tileNumY) && tileNumY < 0)
			_dir = UP;
		else if (Math::Abs(tileNumX) <= Math::Abs(tileNumY) && tileNumY > 0)
			_dir = DOWN;
		propPreview->transform->SetAngle(_dir * 90);
		conveyorArrow.transform->SetAngle((_dir + 1) % 4 * 90);
	}
	int startX = _worldStartPtMouse.x / TILESIZE;
	int startY = _worldStartPtMouse.y / TILESIZE;
	_previewV.clear();
	for (int i = 0; i < bigNum; i++)
	{
		ImageObject newPreview;
		newPreview.transform->SetPosition
		(
			startX * TILESIZE + 16 + TILESIZE * i * Math::NegativeChecking(tileNumX) * (Math::Abs(tileNumX) > Math::Abs(tileNumY)),
			startY * TILESIZE + 16 + TILESIZE * i * Math::NegativeChecking(tileNumY) * (Math::Abs(tileNumX) <= Math::Abs(tileNumY))
		);
		int previewTileX = newPreview.transform->GetX() / TILESIZE;
		int previewTIleY = newPreview.transform->GetY() / TILESIZE;
		newPreview.transform->SetAngle(propPreview->transform->GetAngle());
		if (propContainer->GetPropMap(previewTIleY * TILENUMX + previewTileX) == nullptr)
		{
			newPreview.renderer->Init(propPreview->renderer->GetClipName());
			newPreview.renderer->SetAlpha(0.5f);
		}
		else
		{
			newPreview.renderer->Init(propPreview->renderer->GetClipName());
			newPreview.renderer->SetAlpha(0.4f);
		}
		_previewV.push_back(newPreview);
	}
	_previewNum = bigNum;
	_previewDir = curDir;

}

void UIControler::SetPreviewTwo(float deltaX, float deltaY)
{
	int previewSize = propPreview->renderer->GetWidth();
	int tileNumX = deltaX / previewSize;
	int tileNumY = deltaY / previewSize;
	bool curDir = Math::Abs(tileNumX) > Math::Abs(tileNumY);
	int bigNum = Math::Max(Math::Abs(tileNumX), Math::Abs(tileNumY)) + 1;
	if (_previewNum == bigNum && _previewDir == curDir)
	{
		return;
	}

	int startX = _worldStartPtMouse.x / (TILESIZE / 2);
	int startY = _worldStartPtMouse.y / (TILESIZE / 2);
	if (startX % 2 != 0)
		startX += 1;
	if (startY % 2 != 0)
		startY += 1;
	startX /= 2;
	startY /= 2;

	_previewV.clear();
	for (int i = 0; i < bigNum; i++)
	{
		ImageObject newPreview;
		newPreview.transform->SetPosition
		(
			startX * TILESIZE + previewSize * i * Math::NegativeChecking(tileNumX) * (Math::Abs(tileNumX) > Math::Abs(tileNumY)),
			startY * TILESIZE + previewSize * i * Math::NegativeChecking(tileNumY) * (Math::Abs(tileNumX) <= Math::Abs(tileNumY))
		);
		newPreview.transform->SetAngle(propPreview->transform->GetAngle());
		vector<int> previewTileV;
		int previewTileX = newPreview.transform->GetX() / TILESIZE;
		int previewTileY = newPreview.transform->GetY() / TILESIZE;
		previewTileV.push_back(previewTileY * TILENUMX + previewTileX);
		previewTileV.push_back((previewTileY - 1) * TILENUMX + previewTileX);
		previewTileV.push_back(previewTileY * TILENUMX + previewTileX - 1);
		previewTileV.push_back((previewTileY - 1) * TILENUMX + previewTileX - 1);

		bool isValid = true;
		bool isResource = false;
		for (int i = 0; i < 4; i++)
		{
			if (propContainer->GetPropMap(previewTileV[i]) != nullptr)
			{
				isValid = false;
				break;
			}
		}

		for (int i = 0; i < 4; i++)
		{
			tagTile tileInfo = gameMap->GetTileInfo(previewTileV[i]);
			if (tileInfo.resources != RES_NONE) 
			{
				isResource = true;
				break;
			}
		}
		if (isValid == true && isResource == true)
		{
			newPreview.renderer->Init(propPreview->renderer->GetClipName());
			newPreview.renderer->SetAlpha(0.5f);
		}
		else
		{
			newPreview.renderer->Init(propPreview->renderer->GetClipName());
			newPreview.renderer->SetAlpha(0.4f);
		}
		_previewV.push_back(newPreview);
	}
	_previewNum = bigNum;
	_previewDir = curDir;
}

void UIControler::CheckValidTile()
{
	int tileX = propPreview->transform->GetX() / TILESIZE;
	int tileY = propPreview->transform->GetY() / TILESIZE;

	if (_selectCategoryIdx == PRODUCTION)
	{
		vector<int> previewTile;
		previewTile.push_back(tileY * TILENUMX + tileX);
		previewTile.push_back((tileY - 1) * TILENUMX + tileX);
		previewTile.push_back(tileY * TILENUMX + tileX - 1);
		previewTile.push_back((tileY - 1) * TILENUMX + tileX - 1);

		bool isValid = true;
		bool isResource = false;
		for (int i = 0; i < 4; i++)
		{
			if (propContainer->GetPropMap(previewTile[i]) != nullptr)
			{
				isValid = false;
				break;
			}
		}

		for (int i = 0; i < 4; i++)
		{
			tagTile tileInfo = gameMap->GetTileInfo(previewTile[i]);
			if (tileInfo.resources != RES_NONE)
			{
				isResource = true;
				break;
			}
		}
		if (isValid == true && isResource == true)
		{
			propPreview->renderer->SetAlpha(0.5f);
		}
		else
		{
			propPreview->renderer->SetAlpha(0.4f);
		}
	}
	else 
	{
		Prop* prop = propContainer->GetPropMap(tileY * TILENUMX + tileX);
		if (prop != nullptr)
		{
			propPreview->renderer->SetAlpha(0.4f);
		}
		else
		{
			propPreview->renderer->SetAlpha(0.5f);
		}
	}

	return;
}

void UIControler::inResearch_ActiveChoiceImg(Transform* menuTr, bool isActive)
{
	choiceImg->transform->SetPosition(menuTr->GetX(), menuTr->GetY());
	choiceImg->SetActive(isActive);
}

/* ���� ���¿��� [��ü�ڿ�] ��ư EVENT */
void UIControler::inResearch_Active_Choice_Img(bool* name)
{
	// true = ���� �ִ� ����
	// false = �����ִ� ����
	if (*name)
	{
		all_Resources_Img->SetActive(true);
	}
	else
	{
		all_Resources_Img->SetActive(false);
	}
}

/* ���� ���¿��� [��ü�ڿ�] ��ư CLICK*/
void UIControler::inResearch_Active_all_Resources_Click_Event(bool* name)
{
	if (*name) // true = ���� �ִ� ����
	{
		*name = false;
		all_Resources_Img->SetActive(false);
		all_Resources_Open1_Img->SetActive(false);
		all_Resources_Open2_Img->SetActive(false);
		all_Resources_Open3_Img->SetActive(false);
		all_Resources_Text->SetActive(false);
		all_Resources_Close_Img->SetActive(true);

		//���� 1�� �̻����� �ľ� - ����
		//if (gameInfo->GetResourceAmount(COPPER) >= 1)
		//{
		//	float heightRange = 0;
		//	heightRange += TIMEMANAGER->getElapsedTime();
		//	all_Resources_Add->transform->SetScaleY(heightRange);
		//
		//	if (heightRange > 5)
		//    {
		//		heightRange = 0;
		//    }
		//    //_all_Resources_Bottom_Border.transform->SetPosition(_all_Resources_LR_Border.transform->SetX(), _all_Resources_LR_Border.transform->SetY());
		//}
	}
	else // false = �����ִ� ����
	{
		*name = true;
		all_Resources_Open1_Img->SetActive(true);
		all_Resources_Text->SetActive(true);
		all_Resources_Close_Img->SetActive(false);
	}
}

/* ���� ���¿��� [��ü�ڿ�] ��ư EXIT */
void UIControler::inResearch_InActive_Choice_Img()
{
	all_Resources_Img->SetActive(false);
}

/* ���� ���¿��� [���ư���] ��ư ENTER, EXIT */
void UIControler::inResearch_ActiveGoBackImg(bool isActive)
{
	research_goBackChoiceImg->SetActive(isActive);
}

/* ���� ���¿��� [���ư���] ��ư CLICK */
void UIControler::inResearch_ReturnToGameScene(bool* name, bool isActive)
{
	*name = isActive;
}

/* ���� ���¿��� [�ھ� DB] ��ư ENTER, EXIT */
void UIControler::inResearch_ActiveCoreDBImg(bool isActive)
{
	coreDBChoiceImg->SetActive(isActive);
}

/* ���� ���¿��� [�ھ� DB] ��ư CLICK */
void UIControler::inResearch_ReturnToCoreDBScene(bool* name, bool isActive)
{
	// �ھ� DB ȭ�� ������ �� �� ������ ��������ֱ�
	*name = isActive;
}

/* ���� ���¿��� [�������� ��ü] ��ư ENTER */
void UIControler::inResearch_ActiveChoiceImgWithBasicDes(Transform* menuTr, UIBase* name, Button* name2, bool* name3, bool isActive)
{
	if (*name3) return;

	choiceImg->transform->SetPosition(menuTr->GetX(), menuTr->GetY());
	name->SetActive(isActive);
	name2->SetActive(isActive);
	choiceImg->SetActive(isActive);
}

/* ���� ���¿��� [�������� ��ü] ��ư EXIT */
void UIControler::inResearch_inActiveChoiceImgWithBasicDes(Transform* menuTr, UIBase* name, bool* name2, Button* name3, bool isActive)
{
	if (*name2) return;
	else
	{
		name->SetActive(isActive);
		name3->SetActive(isActive);
		choiceImg->transform->SetPosition(menuTr->GetX(), menuTr->GetY());
		choiceImg->SetActive(isActive);
	}
}

/* ���� ���¿��� [�⺻ ����] ��ư ENTER */
void UIControler::inResearch_inBasicDes(Transform* menuTr, UIBase* name, bool* name2, bool isActive)
{
	*name2 = isActive;
	choiceImg->transform->SetPosition(menuTr->GetX(), menuTr->GetY());
	choiceImg->SetActive(isActive);
	name->SetActive(isActive);
}

/* ���� ���¿��� [�⺻ ����] ��ư EXIT */
void UIControler::inResearch_disableInBasicDes(Transform* menuTr, UIBase* name, bool* name2, Button* name3, bool isActive)
{
	*name2 = isActive;
	name3->SetActive(isActive);
	choiceImg->transform->SetPosition(menuTr->GetX(), menuTr->GetY());
	choiceImg->SetActive(isActive);
	name->SetActive(isActive);
}

/* ���� ���¿��� [�� ����] ��ư ENTER, EXIT */
void UIControler::inResearch_ActiveInResearchChoiceImg(Transform* menuTr, bool isActive)
{
	inResearchChoiceImg->transform->SetPosition(menuTr->GetX(), menuTr->GetY());
	inResearchChoiceImg->SetActive(isActive);
}

/* �⺻ ���� [i] �ֺ� ��ư CLICK*/
void UIControler::inResearch_ActiveDetailImg(UIBase* name, bool* name2, bool isActive)
{
	name->SetActive(isActive);
	*name2 = isActive;
	detailDes_GoBackIdleImg->transform->SetPosition(WINSIZEX / 2, WINSIZEY - 70);
	detailDes_GoBackIdleImg->SetActive(true);
}

/* �� ���� ���¿��� [���ư���] ��ư ENTER */
void UIControler::inDetailDes_ActiveGoBackImg(bool* name, bool isActive)
{
	if (!*name) return;
	detailDes_GoBackChoiceImg->SetActive(isActive);
}

/* �� ���� ���¿��� [���ư���] ��ư CLICK */
void UIControler::inResearch_ReturnToResearchScene(bool* name, UIBase* name2, bool isActive)
{
	*name = isActive;
	name2->SetActive(isActive);
	detailDes_GoBackChoiceImg->SetActive(isActive);
	detailDes_GoBackIdleImg->SetActive(isActive);
}

/* �� ���� ���¿��� [���ư���] ��ư EXIT */
void UIControler::inDetailDes_ReturnToResearch(bool isActive)
{
	detailDes_GoBackChoiceImg->SetActive(isActive);
}

/* �޴� ���¿��� [���ư���] ��ư ENTERT, EXIT */
void UIControler::inMenu_ActiveChoiceImg_GoBack(bool isActive)
{
	menu_GoBackChoiceImg->SetActive(isActive);
}

/* �޴� ���¿��� [���ư���] ��ư CLICK */
void UIControler::inMenu_ReturnToGameScene(bool* name, bool isActive)
{
	*name = isActive;
}

/* �޴� ���¿��� [���� �� ������] ��ư ENTER, EXIT */
void UIControler::inMenu_AcitveChoiceImg_SaveAndExit(bool isActive)
{
	menu_SaveAndExitChoiceImg->SetActive(isActive);
}

/* �޴� ���¿��� [���� �� ������] ��ư CLICK */
void UIControler::inMenu_AcitveRellayEnd(bool* name, bool isAcitve)
{
	*name = isAcitve;
	menu_SaveAndExitButton->uiMouseEvent->enable = false;
	menu_ReallyEnd_Img->SetActive(isAcitve);
}

/* ������ �����Ͻðڽ��ϱ�? ���¿��� [���] ��ư ENTERT, EXIT */
void UIControler::inReallyEnd_Active_CancleImg(bool* name, bool isActive)
{
	if (!*name) return;
	menu_ReallyEnd_Cancle_Choice->SetActive(isActive);
}

/* ������ �����Ͻðڽ��ϱ�? ���¿��� [���] ��ư CLICK */
void UIControler::inReallyEnd_Return_To_MenuState(bool* name, bool isAcitve)
{
	*name = isAcitve;
	menu_SaveAndExitButton->uiMouseEvent->enable = true;
	menu_ReallyEnd_Img->SetActive(isAcitve);
	menu_ReallyEnd_Cancle_Choice->SetActive(isAcitve);
}

/* ������ �����Ͻðڽ��ϱ�? ���¿��� [Ȯ��] ��ư ENTERT, EXIT */
void UIControler::inReallyEnd_Active_CheckImg(bool* name, bool isActive)
{
	if (!*name) return;
	menu_ReallyEnd_Check_Choice->SetActive(isActive);
}

/* ������ �����Ͻðڽ��ϱ�? ���¿��� [Ȯ��] ��ư CLICK */
void UIControler::inReallyEnd_Return_To_TilteScene(string SceneName)
{
	SCENEMANAGER->LoadScene(SceneName);
}

void UIControler::EnemyWaveSkip(bool isActive)
{
	enemyWaveSkip->SetActive(false);
	enemyWaveSkipClick->SetActive(isActive);
}

void UIControler::EnemyWaveSkipClick()
{
	enemyManager->SpawnEnemy();
}