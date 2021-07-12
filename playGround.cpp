#include "stdafx.h"
#include "playGround.h"
#include "SampleScene.h"
#include "SampleScene2.h"
#include "MapScene.h"
#include "GameScene.h"
playGround::playGround()
{

}


playGround::~playGround()
{
}

//초기화는 여기다 하세요 제발
HRESULT playGround::init()
{
	gameNode::init(true);
	_camShakeFrame = 0;
	
	MapScene* mapScene = new MapScene();
	SCENEMANAGER->AddScene("background", mapScene);
	//SCENEMANAGER->LoadScene("background");

	SampleScene* sampleScene = new SampleScene();
	SCENEMANAGER->AddScene("sample", sampleScene);
	SCENEMANAGER->LoadScene("sample");

	SampleScene2* sampleScene2 = new SampleScene2();
	SCENEMANAGER->AddScene("sample2", sampleScene2);

	GameScene* gameScene = new GameScene();
	SCENEMANAGER->AddScene("game", gameScene);
	//SCENEMANAGER->LoadScene("game");

	//플레이어 회전 설계
	//앵글을 깍아줄지 늘려줄지 정하는방법
	//현재앵글 - 목표앵글이 180보다 크면 줄여준다
	//앵글이 음수가 되면 360 - 음수절대값 으로 바꿔준다
	//앵글이 360보다 커지면 0 + 남는값으로 바꿔준다.

	//_mainCam.transform->SetX(_mainCam.transform->GetX() + 100);
	//testParticle = new image();
	//testParticle->init("full_charge_hit_effect_left.bmp", 240, 88, 4, 1, true, RGB(255, 0, 255));
	//testParticle2 = new image();
	//testParticle2->init("trap_blast_projectile.bmp", 168, 50, 4, 1, true, RGB(255, 0, 255));

	//particleObj.AddComponent(new ParticleSystem(testParticle, 5, 5));
	//demoParticleSys = particleObj.GetComponent<ParticleSystem>();
	//demoParticleSys->SetPosition(WINSIZEX / 2, WINSIZEY / 2);
	//demoParticleSys->SetInterval(1000);
	//demoParticleSys->SetDuration(150);
	//demoParticleSys->SetSpeed(0);
	//demoParticleSys->SetLoop(true);
	
	//_mainCam.camera->Shake(3, 2);
	return S_OK;
}

//메모리 해제는 여기다 하세요 제발
void playGround::release()
{
	gameNode::release();

}

//여기에다 연산하세요 제에발
void playGround::update()
{
	gameNode::update();
	//changeParticleTime++;
	//if (changeParticleTime == 300) {
	//	demoParticleSys->SetParticleImage(testParticle2);
	//}
	//_camShakeFrame++;
	//if (_camShakeFrame == 100) {
	//	_mainCam.camera->ShakeOff();
	//}
	//if (_camShakeFrame == 200) {
	//	_camShakeFrame = 0;
	//	_mainCam.camera->Shake(6, 2); 
	//}
	oldTime = curTime;
	curTime = clock();
	SCENEMANAGER->Update();
	//_mainCam.Update();
	//demoParticleSys->Update();
	deltaTime = curTime - oldTime;
	//_alphaFrame++;
	//if (_alphaFrame == 5) {
	//	_alphaFrame = 0;
	//	if (_ui.uiRenderer->alpha > 0)
	//		_ui.uiRenderer->SetAlpha(_ui.uiRenderer->alpha - 1);
	//}
	//_ui.Update();
}

//여기에다 그려라 좀! 쫌!
void playGround::render()
{
	D2DRenderer::GetInstance()->BeginRender(D2D1::ColorF::Black);
	// 위에 건들지마라
	//================제발 이 사이에 좀 그립시다==========================
	//demoParticleSys->Render();

	SCENEMANAGER->Render();
	wstring fps = L"FPS : ";
	fps.append(to_wstring(TIMEMANAGER->getFPS()));
	D2DRENDERER->RenderText(10, 10, fps, 30);
	//==================================================
	//여기도 건들지마라
	//_ui.Render();
	//_mainCam.camera->Render(_hdc);
	//this->getBackBuffer()->render(hdc, 0, 0);
	D2DRenderer::GetInstance()->EndRender();
}
