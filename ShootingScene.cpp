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
	_enemyPlaneWeapon->Update();
	//_enemyGround->Update();
	_enemyGround_Leg_Right->Update();
	_enemyGround_Leg_Left->Update();
	_enemyGround_Weapon_Right->Update();
	_enemyGround_Weapon_Left->Update();
	_testCore->Update();
	_projectileManager->Update();
}

void ShootingScene::Render()
{
	_shootingScene.Render();
	_enemyPlaneWeapon->Render();
	_enemyPlane->Render(); 
	_enemyGround_Leg_Left->Render();
	_enemyGround_Leg_Right->Render();
	_enemyGround->Render();
	_enemyGround_Weapon_Right->Render();
	_enemyGround_Weapon_Left-> Render();

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
	_testCore->transform->SetPosition(3000 / 2, 3000 / 2);
	_testCore->transform->SetScale(3, 3);

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
	CLIPMANAGER->AddClip("enemy_atrax", "sprites/units/enemy/enemy_atrax.png", 188, 218);
	CLIPMANAGER->AddClip("enemy_atrax_weapon", "sprites/units/enemy/enemy_atrax_weapon.png", 96, 140);

	CLIPMANAGER->AddClip("enemy_dagger", "sprites/units/enemy/enemy_dagger.png", 48, 48);
	CLIPMANAGER->AddClip("enemy_dagger_leg_right", "sprites/units/enemy/enemy_dagger_leg_right.png",11,25);
	CLIPMANAGER->AddClip("enemy_dagger_leg_left", "sprites/units/enemy/enemy_dagger_leg_left.png",11,25);
	CLIPMANAGER->AddClip("enemy_dagger_weapon_right", "sprites/units/enemy/enemy_dagger_weapon_right.png",7,21);
	CLIPMANAGER->AddClip("enemy_dagger_weapon_left", "sprites/units/enemy/enemy_dagger_weapon_left.png",7,21);

				//////////////////////////EnemyPlane/////////////////////////
	_enemyPlaneWeapon = new GameObject();
	_enemyPlaneWeapon->AddComponent(new Renderer());
	_enemyPlaneWeapon->GetComponent<Renderer>()->Init("enemy_atrax_weapon");

	_enemyPlane = new EnemyPlane();
	_enemyPlane->GetComponent<Renderer>()->Init("enemy_atrax");
	_enemyPlane->transform->SetPosition(WINSIZEX / 2 - 500, WINSIZEY / 2 + 250);
	_enemyPlane->transform->AddChild(_enemyPlaneWeapon);
	_enemyPlaneWeapon->transform->SetPosition(_enemyPlane->transform->GetX(), _enemyPlane->transform->GetY() - 130);
	
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

	_enemyGround_Leg_Left = new GameObject();
	_enemyGround_Leg_Left->AddComponent(new Renderer());
	_enemyGround_Leg_Left->GetComponent<Renderer>()->Init("enemy_dagger_leg_left");
	_enemyGround_Leg_Left->transform->SetPosition(_enemyGround->transform->GetX() - 20, _enemyGround->transform->GetY() + 40);
	_enemyGround_Leg_Left->transform->SetScale(3, 3);

	_enemyGround_Leg_Right = new GameObject();
	_enemyGround_Leg_Right->AddComponent(new Renderer());
	_enemyGround_Leg_Right->GetComponent<Renderer>()->Init("enemy_dagger_leg_right");
	_enemyGround_Leg_Right->transform->SetPosition(_enemyGround->transform->GetX() + 20, _enemyGround->transform->GetY() + 40);
	_enemyGround_Leg_Right->transform->SetScale(3, 3);

	_enemyGround_Weapon_Left = new GameObject();
	_enemyGround_Weapon_Left->AddComponent(new Renderer());
	_enemyGround_Weapon_Left->GetComponent<Renderer>()->Init("enemy_dagger_weapon_left");
	_enemyGround_Weapon_Left->transform->SetPosition(_enemyGround->transform->GetX() - 50, _enemyGround->transform->GetY() + 30);
	_enemyGround_Weapon_Left->transform->SetScale(3, 3);

	_enemyGround_Weapon_Right = new GameObject();
	_enemyGround_Weapon_Right->AddComponent(new Renderer());
	_enemyGround_Weapon_Right->GetComponent<Renderer>()->Init("enemy_dagger_weapon_left");
	_enemyGround_Weapon_Right->transform->SetPosition(_enemyGround->transform->GetX() + 50, _enemyGround->transform->GetY() + 30);
	_enemyGround_Weapon_Right->transform->SetScale(3, 3);

	_enemyGround->transform->AddChild(_enemyGround_Leg_Left);
	_enemyGround->transform->AddChild(_enemyGround_Leg_Right);
	_enemyGround->transform->AddChild(_enemyGround_Weapon_Left);
	_enemyGround->transform->AddChild(_enemyGround_Weapon_Right);

	_enemyGround->GetComponent<EnemyInfo>()->SetTestCore(_testCore);
	_enemyGround->GetComponent<EnemyInfo>()->Init();
	_enemyGround->GetComponent<EnemyInfo>()->SetSpeed(150.f);

	_enemyGround->AddComponent(new EnemyGroundControler());
	_enemyGround->GetComponent<EnemyGroundControler>()->Init();
	_enemyGround->GetComponent<EnemyGroundControler>()->SetTestCore(_testCore);
}


