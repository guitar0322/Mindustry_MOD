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
	CLIPMANAGER->AddClip("playercell", "player/alpha-cell.png",48, 48);
	CLIPMANAGER->AddClip("playerleft", "player/small-basic-weapon-L.png", 48, 48);
	CLIPMANAGER->AddClip("playerright", "player/small-basic-weapon-R.png", 48, 48);
	CLIPMANAGER->AddClip("back", "Night.png", 900, 568);
	SetBackBufferSize(900, 568);

	backGround.Init();
	backGround.renderer->Init("back");
	backGround.transform->SetPosition(900 / 2,568 /2);

	player = new Player();
	player->Init();
	player->renderer->Init("player");
	player->transform->SetPosition(WINSIZEX/2,WINSIZEY/2);
	player->transform->SetAngle(0.0f);

	playerCell = new ImageObject();
	playerCell->Init();
	playerCell->renderer->Init("playercell");
	playerCell->transform->SetPosition(WINSIZEX / 2, WINSIZEY / 2);

	playerLeft = new ImageObject();
	playerLeft->Init();
	playerLeft->renderer->Init("playerleft");
	playerLeft->transform->SetPosition(WINSIZEX / 2 - 12, WINSIZEY / 2 - 4);

	playerRight = new ImageObject();
	playerRight->Init();
	playerRight->renderer->Init("playerright");
	playerRight->transform->SetPosition(WINSIZEX / 2 + 11, WINSIZEY / 2 - 4);

	player->transform->AddChild(playerCell); // 본체 이미지(?)의 자식 함수를 따라가게 한다. 0번째 자식함수
	player->transform->AddChild(playerLeft); // 1번째 자식함수.
	player->transform->AddChild(playerRight); // 2번째 자식함수.
	return S_OK;
}

void PlayerScene::Update()
{
	backGround.Update();
	player->Update();
	playerCell->Update();
	playerLeft->Update();
	playerRight->Update();
}

void PlayerScene::Render()
{
	Rect rect;
	rect = RectMakePivot(Vector2(WINSIZEX + 500, WINSIZEY / 2), Vector2(50, 50), Pivot::Center);
	D2DRenderer::GetInstance()->DrawRectangle(rect, D2DRenderer::DefaultBrush::Red, 1.f);

	backGround.Render();
	player->Render();
	playerCell->Render();
	playerLeft->Render();
	playerRight->Render();
	MainCam->Render();
}

void PlayerScene::Release()
{
	NEW_SAFE_RELEASE(player);
}
