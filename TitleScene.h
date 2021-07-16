#pragma once
#define BACKGROUND_WIDTH  1125
#define BACKGROUND_HEIGHT 875
#define ENEMY_PLANE_MAX 10
#include "Scene.h"
#include "TitleUIControler.h"

/* SHUNG 21.07.12 */

class TitleScene : public Scene
{

private:

	TitleUIControler* titleUIControler;

	/* Bool */
	bool		_grab;
	bool		_inSetting;
	bool		_inInfo;
	bool		_alphaTrigger;
	bool		_choiceSoundSettingButton;
	bool		_choiceGoBackButton;

	/* Background */
	ImageObject _backgroundImg;

	/* Logo */
	ImageObject _logoImg;

	/* Icon & Button */
	/* Play */
	ImageObject _playIconImg;
	UIBase		_playButton;
	/* Ediotr */
	ImageObject _editorIconImg;
	UIBase		_ediotrButton;
	/* Setting */
	ImageObject _settingIconImg;
	ImageObject _settingTitleImg;
	ImageObject _settingMenuBoardImg;
	UIBase		_settingButton;
	UIBase		_soundButton;
	/* About */
	ImageObject _abuotIconImg;
	UIBase		_aboutButton;
	/* Exit */
	ImageObject _exitIconImg;
	UIBase		_exitButton;
	/* GoBack */
	ImageObject _goBackIdleImg;
	ImageObject _goBackChoiceImg;
	UIBase		_goBackButton;

	/* Menu Board & Menu Choice */
	ImageObject _boardImg;
	ImageObject _choiceImg;
	ImageObject _choiceImg2;

	/* 비행기 관련 소스 코드 작업 (민재-대영) */
	GameObject* _enemyPlane[ENEMY_PLANE_MAX];
	ImageObject* _enemyPlaneShadow[ENEMY_PLANE_MAX];
	float _emergencyTime;
	float _randomSpawnTime;

public:

	TitleScene();
	~TitleScene();

	int testInt;

	virtual HRESULT Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();
	
	/* Titile */
	/* Init */
	virtual void ClipManager();
	virtual void Render_SetPosition_MouseEvent();
	
	/* Render */
	virtual void AlphaManager();
	virtual void D2DRendererManager();

	/* Enemy */
	/* Init */
	void SetTitleSceneEnemy();
	/* Update */
	void EnemyMove();
};