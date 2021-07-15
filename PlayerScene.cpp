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

	CLIPMANAGER->AddClip("player", "player/alpha.png", 48, 48);
	CLIPMANAGER->AddClip("back", "Night.png", 900,568);
	CLIPMANAGER->AddClip("enemy_projectile", "sprites/units/weapons/missiles-mount.png", 48, 48);
	CLIPMANAGER->AddClip("copper", "sprites/items/item-copper.png", 32, 32);

	SetBackBufferSize(3000, 2272);

	_backGround.Init();
	_backGround.renderer->Init("back");
	_backGround.transform->SetPosition(1800,1136);

	_mineUI.Init();
	_mineUI.uiRenderer->Init("copper");
	_mineUI.transform->SetPosition(WINSIZEX/2-100,20);

	_player = new Player();
	_player->Init();
	_player->renderer->Init("player");
	_player->transform->SetPosition(1500,900);
	_player->transform->SetAngle(0.0f);
	MainCam->transform->SetPosition(_player->transform->position.x,_player->transform->position.y);

	_projectileManager = new GameObject();
	_projectileManager->AddComponent(new ProjectileManager());
	_projectileManager->GetComponent<ProjectileManager>()->Init();

	_player->controler->SetProjectileManager(_projectileManager->GetComponent<ProjectileManager>());

	_mineCount = 0;
	return S_OK;
}

void PlayerScene::Update()
{
	_backGround.Update();
	_player->Update();
	_projectileManager->Update();
	_mineUI.Update();
	mainCam->transform->SetPosition(_player->transform->position.x, _player->transform->position.y);
	MainCam->Update();
}

void PlayerScene::Render()
{
	Rect rect;
	rect = RectMakePivot(Vector2(WINSIZEX + 500, WINSIZEY / 2), Vector2(50, 50), Pivot::Center);
	D2DRenderer::GetInstance()->DrawRectangle(rect, D2DRenderer::DefaultBrush::Red, 1.f);
	_backGround.Render();
	_player->Render();
	_projectileManager->Render();
	MainCam->Render();
	_mineUI.Render(); // UI의 경우는 메인 카메라의 아랫줄에서 실행해야한다.
	wstring wstr = L"player speed : ";
	wstr.append(to_wstring(_player->controler->GetSpeed()));
	D2DRENDERER->RenderText(100, 100, wstr, 20, L"맑은고딕", D2DRenderer::DefaultBrush::White);

	wstring wstrangle = L"Angle : ";
	wstrangle.append(to_wstring(_player->controler->GetTargetAngle()));
	D2DRENDERER->RenderText(100, 150, wstrangle, 20, L"맑은고딕", D2DRenderer::DefaultBrush::White);

	wstring mineCount = L"";
	mineCount.append(to_wstring(_mineCount));
	D2DRENDERER->RenderText(WINSIZEX / 2-50, 10, mineCount, 20, L"fontello", D2DRenderer::DefaultBrush::White);
}

void PlayerScene::Release()
{
	NEW_SAFE_RELEASE(_player);
}
