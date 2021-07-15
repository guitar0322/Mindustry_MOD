#include "stdafx.h"
#include "PlayerScene.h"
#include "PlayerControler.h"
#include "Player.h"
PlayerScene::PlayerScene()
{
}

PlayerScene::~PlayerScene()
{
}

HRESULT PlayerScene::Init()
{
	Scene::Init();

	////CLIPMANAGER->AddClip("back", "Night.png", 900,568);
	//CLIPMANAGER->AddClip("enemy_projectile", "sprites/units/weapons/missiles-mount.png", 48, 48);
	//CLIPMANAGER->AddClip("copper", "sprites/items/item-copper.png", 32, 32);

	////SetBackBufferSize(3000, 2272);

	////_backGround.Init();
	////_backGround.renderer->Init("back");
	////_backGround.transform->SetPosition(1800,1136);

	//_mineUI.Init();
	//_mineUI.uiRenderer->Init("copper");
	//_mineUI.transform->SetPosition(WINSIZEX/2-100,20);
	//

	

	//_mineCount = 0;
	return S_OK;
}

void PlayerScene::Update()
{
	//_backGround.Update();
	//_mineUI.Update();

}

void PlayerScene::Render()
{
	//Rect rect;
	//rect = RectMakePivot(Vector2(WINSIZEX + 500, WINSIZEY / 2), Vector2(50, 50), Pivot::Center);
	//D2DRenderer::GetInstance()->DrawRectangle(rect, D2DRenderer::DefaultBrush::Red, 1.f);
	////_backGround.Render();
	//_mineUI.Render(); // UI의 경우는 메인 카메라의 아랫줄에서 실행해야한다.

}

void PlayerScene::Release()
{
}
