#pragma once
#define BACKGROUND_WIDTH  1125
#define BACKGROUND_HEIGHT 875
#define ENEMY_PLANE_MAX 10
#include "Scene.h"

/* SHUNG 21.07.12 */

class TitleScene : public Scene
{

private:

	/* BACKGROUND */
	ImageObject _backgroundImg;

	/* LOGO */
	ImageObject _logoImg;

	/* ICON */
	ImageObject _playButtonImg;
	ImageObject _editorButtonImg;
	ImageObject _settingButtonImg;
	ImageObject _abuotButtonImg;
	ImageObject _exitButtonImg;

	/* Menu Board */
	ImageObject _boardImg;
	ImageObject _choiceImg;
	Rect		_menuRect[5];

	/* 21.07.13 SETTING IMG */
	bool		_grab;
	bool		_inSetting;
	bool		_inInfo;
	bool		_alphaTrigger;
	bool		_choiceSoundSettingButton;
	bool		_choiceGoBackButton;

	ImageObject _settingTitleImg;
	ImageObject _settingMenuBoardImg;
	ImageObject _settingMenuChoiceImg;
	ImageObject _goBackIdleImg;
	ImageObject _goBackChoiceImg;

	Rect		_settingRect;
	Rect		_goBackRect;

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
	
	/* Init */
	virtual void ClipManager();
	virtual void RenderAndPositionManager();
	virtual void MakeRect();

	/* Render */
	virtual void AlphaManager();
	virtual void D2DRendererManager();

	/* Enemy */

	/* Init */
	void SetTitleSceneEnemy();
	/* Update */
	void EnemyMove();
};