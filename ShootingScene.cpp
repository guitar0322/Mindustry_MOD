#include "stdafx.h"
#include "ShootingScene.h"
#include "ProjectileManager.h"
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
	SetProjectile();
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
	_enemyGround->Update();
	_testCore->Update();
	_projectileManager->Update();
}

void ShootingScene::Render()
{
	_shootingScene.Render();
	_enemyPlane->Render();    
	_enemyGround->Render();
	_testCore->Render();
	_projectileManager->Render();
	MainCam->Render();
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
	_testCore->GetComponent<Animator>()->AddClip(CLIPMANAGER->FindClip("core"));
	_testCore->GetComponent<Animator>()->SetClip("core");
	_testCore->transform->SetPosition(3000 / 2, 3000 / 2);

	_testCore->AddComponent(new BoxCollider());
	_testCore->GetComponent<BoxCollider>()->Init();

}
void ShootingScene::SetProjectile()
{
	CLIPMANAGER->AddClip("enemy_projectile", "sprites/units/weapons/missiles-mount.png", 48, 48);

	_projectileManager = new GameObject();
	_projectileManager->AddComponent(new ProjectileManager());
	_projectileManager->GetComponent<ProjectileManager>()->Init();
}
void ShootingScene::SetEnemy()   
{
	CLIPMANAGER->AddClip("enemy_sei", "sprites/units/sei.png", 240, 240);
	CLIPMANAGER->AddClip("enemy_toxopid", "sprites/units/toxopid.png", 160, 190);

					////////////EnemyPlane////////////
	_enemyPlane = new EnemyPlane();
	_enemyPlane->GetComponent<Renderer>()->Init("enemy_sei");
	_enemyPlane->GetComponent<Animator>()->AddClip(CLIPMANAGER->FindClip("enemy_sei"));
	_enemyPlane->GetComponent<Animator>()->SetClip("enemy_sei");
	_enemyPlane->transform->SetPosition(WINSIZEX / 2 - 500, WINSIZEY / 2 + 250);
	_enemyPlane->transform->SetScale(0.3f, 0.3f);
	_enemyPlane->transform->SetPosition(400, 400);

	//EnemyObject에 EnemyInfo를 Add해주어서 가져오기만 하면 됨
	_enemyPlane->GetComponent<EnemyInfo>()->SetTestCore(_testCore);
	_enemyPlane->GetComponent<EnemyInfo>()->Init();
	_enemyPlane->GetComponent<EnemyInfo>()->SetSpeed(200.f);

	//EnemyPlaneControler는 EnemyPlane에 add해주어서 가져오기만 하면 됨

	_enemyPlane->AddComponent(new EnemyPlaneControler());
	_enemyPlane->GetComponent<EnemyPlaneControler>()->Init();
	_enemyPlane->GetComponent<EnemyPlaneControler>()->SetTestCore(_testCore);
	_enemyPlane->GetComponent<EnemyPlaneControler>()->SetProjectileManager(_projectileManager->GetComponent<ProjectileManager>());

	/////////////////// Enemy Ground >>>>>>>>>>>>>>>>>>>>>>>>>>>

	_enemyGround = new EnemyGround();
	_enemyGround->Init();
	_enemyGround->GetComponent<Renderer>()->Init("enemy_toxopid");
	_enemyGround->transform->SetPosition(2000, 500);

	_enemyGround->GetComponent<EnemyInfo>()->SetTestCore(_testCore);
	_enemyGround->GetComponent<EnemyInfo>()->Init();
	_enemyGround->GetComponent<EnemyInfo>()->SetSpeed(150.f);

	_enemyGround->AddComponent(new EnemyGroundControler());
	_enemyGround->GetComponent<EnemyGroundControler>()->Init();
	//_enemyGround->transform->SetScale(2, 2);
}


