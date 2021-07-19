#include "stdafx.h"
#include "UIControler.h"
#include "TileInfo.h"
#include "PropContainer.h"
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
				//2칸짜리 미리보기설계
				//마우스가 타일의 교차점을 기준으로 한타일 사이즈만큼 벗어 났을때 위치가 갱신되어야 한다
				//마우스가 교차점을 기준으로 타일사이즈 안에 있다는 것을 알아내는 방법
				//마우스 교차점 좌표 = tileX * TILESIZE, tileY * TILESIZE
				//마우스 좌표를 TILESIZE/2 로나눈다
				//좌표가 짝수배면 해당 교점에 생성
				//좌표가 홀수배면 +1 지점에 생성
			}
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
			* 미리보기 생성 설계
			* 1. 기존방식은 마우수의 위치에 계속해서 넣는 방식
			* 2. 개선방식->일직전으로만 짓는것으로 변경
			* 3. 마우스를 클릭한 start지점에서 현재 마우스 위치까지의 deltaX, deltaY구함
			* 4.y가 더 크면 수직방향으로 생성
			* 5.x가 더 크면 수평방향으로 생성
			* 5-1. 가변적인 미리보기를 어떻게 자료구조에 저장하고 렌더할 것인가?
			* 5-2. 미리보기개수, 방향을 프레임마다 구하고 둘중하나라도 달라진다면
			*   함수를 호출하여 벡터의 길이를 변경 혹은 위치를 변경한다.
			* 6.마우스를 떼면 큐에 추가
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
	int bigNum = Math::Max(Math::Abs(tileNumX), Math::Abs(tileNumY));
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
		vector<pair<int, int>> previewTileV;
		int previewTileX = newPreview.transform->GetX() / TILESIZE;
		int previewTileY = newPreview.transform->GetY() / TILESIZE;
		previewTileV.push_back({ previewTileX, previewTileY });
		previewTileV.push_back({ previewTileX-1, previewTileY });
		previewTileV.push_back({ previewTileX, previewTileY-1 });
		previewTileV.push_back({ previewTileX-1, previewTileY-1 });

		bool isValid = true;
		for (int i = 0; i < 4; i++)
		{
			if (propContainer->GetPropMap(previewTileV[i].second * TILENUMX + previewTileV[i].first) != nullptr)
			{
				isValid = false;
				newPreview.renderer->Init(propPreview->renderer->GetClipName());
				newPreview.renderer->SetAlpha(0.4f);
				break;
			}
		}
		if (isValid == true)
		{
			newPreview.renderer->Init(propPreview->renderer->GetClipName());
			newPreview.renderer->SetAlpha(0.5f);
		}
		_previewV.push_back(newPreview);
	}
	_previewNum = bigNum;
	_previewDir = curDir;
}

void UIControler::inResearch_ActiveChoiceImg(Transform* menuTr, bool isActive)
{
	choiceImg->transform->SetPosition(menuTr->GetX(), menuTr->GetY());
	choiceImg->SetActive(isActive);
}

void UIControler::inResearch_ActiveGoBackImg(bool isActive)
{
	goBackChoiceImg->SetActive(isActive);
}

void UIControler::inResearch_ActiveInResearchChoiceImg(Transform* menuTr, bool isActive)
{
	inResearchChoiceImg->transform->SetPosition(menuTr->GetX(), menuTr->GetY());
	inResearchChoiceImg->SetActive(isActive);
}

void UIControler::inResearch_ReturnToGameScene(bool* name, bool isActive)
{
	*name = isActive;
}

void UIControler::inResearch_ActiveCoreDBImg(bool isActive)
{
	coreDBChoiceImg->SetActive(isActive);
}

void UIControler::inResearch_ReturnToCoreDBScene(bool* name, bool isActive)
{
	// 코어 DB 화면 구성할 때 불 값으로 연결시켜주기
	*name = isActive;
}

void UIControler::inResearch_ActiveChoiceImgWithBasicDes(Transform* menuTr, UIBase* name, bool isActive)
{
	choiceImg->transform->SetPosition(menuTr->GetX(), menuTr->GetY());
	choiceImg->SetActive(isActive);
	name->SetActive(isActive);
}

void UIControler::inResearch_inBasicDes(Transform* menuTr, UIBase* name, bool* name2, bool isActive)
{
	*name2 = isActive;
	choiceImg->transform->SetPosition(menuTr->GetX(), menuTr->GetY());
	choiceImg->SetActive(isActive);
	name->SetActive(isActive);
}

void UIControler::inResearch_inActiveChoiceImgWithBasicDes(Transform* menuTr, UIBase* name, bool* name2, bool isActive)
{
	if (*name2) return;
	else
	{
		name->SetActive(isActive);
		choiceImg->transform->SetPosition(menuTr->GetX(), menuTr->GetY());
		choiceImg->SetActive(isActive);
	}
}

void UIControler::inResearch_disableInBasicDes(Transform* menuTr, UIBase* name, bool* name2, bool isActive)
{
	*name2 = isActive;
	choiceImg->transform->SetPosition(menuTr->GetX(), menuTr->GetY());
	choiceImg->SetActive(isActive);
	name->SetActive(isActive);
}


