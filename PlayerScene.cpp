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
	SetBackBufferSize(3000, 2272);

	backGround.Init();
	backGround.renderer->Init("back");
	backGround.transform->SetPosition(1800,1136);

	player = new Player();
	player->Init();
	player->renderer->Init("player");
	player->transform->SetPosition(1500,900);
	player->transform->SetAngle(0.0f);
	MainCam->transform->SetPosition(player->transform->position.x,player->transform->position.y);

	_projectileManager = new GameObject();
	_projectileManager->AddComponent(new ProjectileManager());
	_projectileManager->GetComponent<ProjectileManager>()->Init();

	player->controler->SetProjectileManager(_projectileManager->GetComponent<ProjectileManager>());
	return S_OK;
}

void PlayerScene::Update()
{
	backGround.Update();
	player->Update();
	_projectileManager->Update();
	mainCam->transform->SetPosition(player->transform->position.x, player->transform->position.y);
	MainCam->Update();
}

void PlayerScene::Render()
{
	Rect rect;
	rect = RectMakePivot(Vector2(WINSIZEX + 500, WINSIZEY / 2), Vector2(50, 50), Pivot::Center);
	D2DRenderer::GetInstance()->DrawRectangle(rect, D2DRenderer::DefaultBrush::Red, 1.f);

	backGround.Render();
	player->Render();
	_projectileManager->Render();

	MainCam->Render();
	wstring wstr = L"player speed : ";
	wstr.append(to_wstring(player->controler->GetSpeed()));
	D2DRENDERER->RenderText(100, 100, wstr, 20, L"¸¼Àº°íµñ", D2DRenderer::DefaultBrush::White);
}

void PlayerScene::Release()
{
	NEW_SAFE_RELEASE(player);
}
