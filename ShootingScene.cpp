#include "stdafx.h"
#include "ShootingScene.h"
#include "EnemyInfo.h"
ShootingScene::ShootingScene()
{
}

ShootingScene::~ShootingScene()
{
}

HRESULT ShootingScene::Init()
{
	Scene::Init();
	SetScene();
	TestCore();
	SetEnemy();
	
	return S_OK;
}

void ShootingScene::Release()
{
}

void ShootingScene::Update()
{
	_shootingScene.Update();
	_enemyPlane->Update();
	_testCore->Update();
	_testCore->transform->SetPosition(WINSIZEX / 2 - 150, WINSIZEY / 2 - 150);
}

void ShootingScene::Render()
{
	_shootingScene.Render();
	_enemyPlane->Render();       
	_testCore->Render();
	MainCam->Render();
}

void ShootingScene::SetScene()
{
	CLIPMANAGER->AddClip("scene_shootingscene", "scene_shootingscene.png", 740, 329);
	SetBackBufferSize(740,329);
	_shootingScene.Init();
	_shootingScene.renderer->Init("scene_shootingscene");
	_shootingScene.transform->SetPosition(MAPWIDTH / 2, MAPHEIGHT / 2);
}



void ShootingScene::TestCore()
{
	CLIPMANAGER->AddClip("core", "sprites/units/alpha.png", 48, 48);
	
	_testCore = new AnimObject ();
	_testCore->Init();
	_testCore->GetComponent<Renderer>()->Init("core");
	_testCore->GetComponent<Animator>()->AddClip(CLIPMANAGER->FindClip("core"));
	_testCore->GetComponent<Animator>()->SetClip("core");
	_testCore->transform->SetPosition(WINSIZEX / 2 - 150, WINSIZEY / 2 - 150);
	
}

void ShootingScene::SetEnemy()   
{
	CLIPMANAGER->AddClip("enemy_sei", "sprites/units/sei.png", 240, 240);
	////////////EnemyPlane////////////
	_enemyPlane = new EnemyPlane();
	_enemyPlane->GetComponent<Renderer>()->Init("enemy_sei");
	_enemyPlane->GetComponent<Animator>()->AddClip(CLIPMANAGER->FindClip("enemy_sei"));
	_enemyPlane->GetComponent<Animator>()->SetClip("enemy_sei");
	_enemyPlane->transform->SetPosition(WINSIZEX / 2, WINSIZEY / 2);
	_enemyPlane->transform->SetScale(0.3f, 0.3f);

	_enemyPlane->AddComponent(new EnemyInfo());
	_enemyPlane->GetComponent<EnemyInfo>()->Init();
	_enemyPlane->GetComponent<EnemyInfo>()->SetSpeed(50.f);
	//

	_enemyPlane->AddComponent(new EnemyPlaneControler());
	_enemyPlane->GetComponent<EnemyPlaneControler>()->Init();

	//클래스에서 Set을 해줘도 되지만 Scene에서 해주는게 더 옳다
	//왜 why
	////////////EnemyPlaneControler///////////////////
	//_enemyPlaneControler = new EnemyPlaneControler();
	//_enemyPlaneControler->Init(_enemyPlane);
}
