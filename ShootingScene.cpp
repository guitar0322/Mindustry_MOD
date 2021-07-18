#include "stdafx.h"
#include "ShootingScene.h"
#include "ProjectileManager.h"
#include <iostream>
ShootingScene::ShootingScene()
{
}

ShootingScene::~ShootingScene()
{
}

HRESULT ShootingScene::Init()
{
	Scene::Init();

	CLIPMANAGER->AddClip("enemy_atrax", "sprites/units/enemy/enemy_atrax.png", 188, 329);
	CLIPMANAGER->AddClip("enemy_dagger_walk", "sprites/units/enemy/enemy_dagger_walk.png", 369, 114, 3, 1, 0.6f); 
	SetScene();
	TestCore();
	SetProjectile();
	SetEnemyManager();
	return S_OK;
}

void ShootingScene::Release()
{
}

void ShootingScene::Update()
{
	_shootingScene.Update();
	_testCore->Update();
	_projectileManager->Update();
	_enemyManager->Update();
	
}

void ShootingScene::Render()
{
	_shootingScene.Render();
	_testCore->Render();
	_projectileManager->Render();
	_enemyManager->Render();


	MainCam->Render();

	wstring minute = L"MINUTE : ";
	minute.append(to_wstring(_enemyManager->GetComponent<EnemyManager>()->GetTimeMinute()));
	D2DRENDERER->RenderText(10, 10, minute, 30, L"fontello", D2DRenderer::DefaultBrush::Blue);
	
	wstring second = L"SECOND: ";
	second.append(to_wstring(_enemyManager->GetComponent<EnemyManager>()->GetTimeSecond()));
	D2DRENDERER->RenderText(10, 60, second, 30, L"fontello", D2DRenderer::DefaultBrush::Blue);

	wstring wave = L"CurWave: ";
	wave.append(to_wstring(_enemyManager->GetComponent<EnemyManager>()->GetCurWave()));
	D2DRENDERER->RenderText(10, 110, wave, 30, L"fontello", D2DRenderer::DefaultBrush::Blue);
}

void ShootingScene::SetScene()
{
	CLIPMANAGER->AddClip("scene_shootingscene", "scene_shootingscene.png", 740, 329);
	SetBackBufferSize(3000,3000);
	MainCam->SetRenderSize(3000, 3000);
	MainCam->transform->SetPosition(3000 / 2, 3000 / 2);
	_shootingScene.Init();
	_shootingScene.renderer->Init("scene_shootingscene");
	_shootingScene.transform->SetPosition(MAPWIDTH / 2, MAPHEIGHT / 2);	
}

void ShootingScene::TestCore()
{
	CLIPMANAGER->AddClip("core", "sprites/units/alpha.png", 48, 48);
	
	_testCore = new AnimObject ();
	_testCore->tag = TAGMANAGER->GetTag("player");
	_testCore->Init();
	_testCore->GetComponent<Renderer>()->Init("core");
	_testCore->transform->SetPosition(3000 / 2, 3000 / 2);
	_testCore->transform->SetScale(3, 3);
	_testCore->AddComponent(new BoxCollider());
	_testCore->GetComponent<BoxCollider>()->Init();
}
void ShootingScene::SetProjectile()
{
	CLIPMANAGER->AddClip("enemy_projectile", "sprites/units/enemy/projectile.png", 52, 52);

	_projectileManager = new GameObject();
	_projectileManager->AddComponent(new ProjectileManager());
	_projectileManager->GetComponent<ProjectileManager>()->Init();
	
}
void ShootingScene::SetEnemyManager()
{
	_enemyManager = new GameObject();
	_enemyManager->AddComponent(new EnemyManager());
	_enemyManager->GetComponent<EnemyManager>()->SetTestCoreTransform(_testCore);
	_enemyManager->GetComponent<EnemyManager>()->SetProjectileManager(_projectileManager->GetComponent<ProjectileManager>());
	_enemyManager->GetComponent<EnemyManager>()->Init();
	_projectileManager->GetComponent<ProjectileManager>()->SetEnemyManager(_enemyManager->GetComponent<EnemyManager>());
}

void ShootingScene::SetEnemy()   
{
	CLIPMANAGER->AddClip("enemy_atrax", "sprites/units/enemy/enemy_atrax.png", 188, 329);
	
	//dagger
	CLIPMANAGER->AddClip("enemy_dagger", "sprites/units/enemy/DAGGER.png", 48, 48);
	CLIPMANAGER->AddClip("enemy_dagge_walk", "sprites/units/enemy/enemy_dagger_walk.bmp", 369, 114, 3, 1, 0.2f);
	CLIPMANAGER->AddClip("enemy_dagge_walk_left", "sprites/units/enemy/enemy_dagger_walk_left.bmp", 342, 123, 3, 1, 0.2f);
	CLIPMANAGER->AddClip("enemy_dagge_walk_right", "sprites/units/enemy/enemy_dagger_walk_right.bmp", 342, 126, 3, 1, 0.2f);

	//////////////////////////EnemyPlane/////////////////////////
	_enemyPlane = new EnemyPlane();
	_enemyPlane->GetComponent<Renderer>()->Init("enemy_atrax");
	_enemyPlane->transform->SetPosition(WINSIZEX / 2 - 500, WINSIZEY / 2 + 250);
	
	//EnemyObject에 EnemyInfo를 Add해주어서 가져오기만 하면 됨
	_enemyPlane->GetComponent<EnemyInfo>()->SetTestCore(_testCore);
	_enemyPlane->GetComponent<EnemyInfo>()->Init();
	_enemyPlane->GetComponent<EnemyInfo>()->SetSpeed(250.f);

	//EnemyPlaneControler는 EnemyPlane에 add해주어서 가져오기만 하면 됨

	_enemyPlane->AddComponent(new EnemyPlaneControler());
	_enemyPlane->GetComponent<EnemyPlaneControler>()->Init();
	_enemyPlane->GetComponent<EnemyPlaneControler>()->SetTestCore(_testCore);
	_enemyPlane->GetComponent<EnemyPlaneControler>()->SetProjectileManager(_projectileManager->GetComponent<ProjectileManager>());
	_projectileManager->GetComponent<ProjectileManager>()->SetEnemyPlanecontrolerTransform(_enemyPlane);
					//////////////////////Enemy Ground///////////////////////////

	_enemyGround = new EnemyGround();
	_enemyGround->Init();
	_enemyGround->GetComponent<Renderer>()->Init("enemy_dagger");
	_enemyGround->transform->SetPosition(2000, 500);
	_enemyGround->transform->SetScale(3, 3);

	_enemyGround->GetComponent<EnemyInfo>()->SetTestCore(_testCore);
	_enemyGround->GetComponent<EnemyInfo>()->Init();
	_enemyGround->GetComponent<EnemyInfo>()->SetSpeed(150.f);

	_enemyGround->AddComponent(new EnemyGroundControler());
	_enemyGround->GetComponent<EnemyGroundControler>()->Init();
	_enemyGround->GetComponent<EnemyGroundControler>()->SetTestCore(_testCore);
}
