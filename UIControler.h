#pragma once
#include "PropFactory.h"
#include <map>
#include <queue>
#include "PropInfo.h"
#define CATEGORY_NUM 4

using namespace std;
class GameMap;
class Button;
class EnemyManager;

class UIControler
{
private:
    int _selectCategoryIdx;
    int _selectPropIdx;
    int _previewNum;
    bool _previewDir;
    Vector2 _worldStartPtMouse;
    vector<string> _clipArr[CATEGORY_NUM];
    vector<ImageObject> _previewV;
    PROPDIR _dir;
public:
    GameMap* gameMap;
    PropFactory* propFactory;
    PropContainer* propContainer;
    UIControler();
    ~UIControler();
    GameObject* categorySelect;
    GameObject* propSelect;
    ImageObject* propPreview;
    ImageObject conveyorArrow;
    vector<GameObject*>* wallIconV;
    vector<GameObject*>* drillIconV;
    vector<GameObject*>* turretIconV;
    vector<GameObject*>* railIconV;
    vector<GameObject*>* preIconV;
    void Init();
    void Update();
    void Release();
    void Render();
    void ClickCategoryIcon(GameObject* clickedButton, int category);
    void ClickPropIcon(GameObject* clickedButton, int propIdx);
    void RefreshPreview();
    void SetPreview(float deltaX, float deltaY);
    void SetPreviewTwo(float deltaX, float deltaY);
    void CheckValidTile();
    /* SHUNG 210715 */
    /* �ÿ� */
    /* ���� */
    UIBase* choiceImg;
    UIBase* lockImg;
    UIBase* inResearchChoiceImg;
    UIBase* research_goBackIdleImg;
    UIBase* research_goBackChoiceImg;
    UIBase* coreDBIdleImg;
    UIBase* coreDBChoiceImg;
    UIBase* detailDes_GoBackIdleImg;
    UIBase* detailDes_GoBackChoiceImg;

    /* �޴� */
    UIBase* menu_GoBackIdleImg;            // �޴� [���ư���] �⺻ ���� �̹���
    UIBase* menu_GoBackChoiceImg;          // �޴� [���ư���] ���� ���� �̹���
    UIBase* menu_SettingIdleImg;           // �޴� [����] �⺻ ���� �̹���
    UIBase* menu_SettingChoiceImg;         // �޴� [����] ���� ���� �̹���
    UIBase* menu_SaveAndExitIdleImg;       // �޴� [���� �� ������] �⺻ ���� �̹���
    UIBase* menu_SaveAndExitChoiceImg;     // �޴� [���� �� ������] ���� ���� �̹���

    void inResearch_ActiveChoiceImg(Transform* menuTr, bool isActive);
    
    /* ���� ���¿��� [���ư���] ��ư ENTER, EXIT */
    void inResearch_ActiveGoBackImg(bool isActive);
    /* ���� ���¿��� [���ư���] ��ư CLICK */
    void inResearch_ReturnToGameScene(bool* name, bool isActive);

    /* ���� ���¿��� [�ھ� DB] ��ư ENTER, EXIT */
    void inResearch_ActiveCoreDBImg(bool isActive);
    /* ���� ���¿��� [�ھ� DB] ��ư CLICK */
    void inResearch_ReturnToCoreDBScene(bool* name, bool isActive);
    
    /* ���� ���¿��� [�������� ��ü] ��ư ENTER */
    void inResearch_ActiveChoiceImgWithBasicDes(Transform* menuTr, UIBase* name, Button* name2, bool* name3, bool isActive);
    /* ���� ���¿��� [�������� ��ü] ��ư EXIT */
    void inResearch_inActiveChoiceImgWithBasicDes(Transform* menuTr, UIBase* name, bool* name2, Button* name3, bool isActive);

    /* ���� ���¿��� [�⺻ ����] ��ư ENTER */
    void inResearch_inBasicDes(Transform* menuTr, UIBase* name, bool* name2, bool isActive);
    /* ���� ���¿��� [�⺻ ����] ��ư EXIT */
    void inResearch_disableInBasicDes(Transform* menuTr, UIBase* name, bool* name2, Button* name3, bool isActive);

    /* ���� ���¿��� [�� ����] ��ư ENTER, EXIT */
    void inResearch_ActiveInResearchChoiceImg(Transform* menuTr, bool isActive);
    /* ���� ���¿��� [�� ����] ��ư CLICK */
    void inResearch_ActiveDetailImg(UIBase* name, bool* name2, bool isActive);

    /* �� ���� ���¿��� [���ư���] ��ư ENTER */
    void inDetailDes_ActiveGoBackImg(bool* name, bool isActive);
    /* �� ���� ���¿��� [���ư���] ��ư CLICK */
    void inResearch_ReturnToResearchScene(bool* name, UIBase* name2, bool isActive);
    /* �� ���� ���¿��� [���ư���] ��ư EXIT */
    void inDetailDes_ReturnToResearch(bool isActive);

    /* �޴� ���¿��� [���ư���] ��ư ENTERT, EXIT */
    void inMenu_ActiveChoiceImg_GoBack(bool isActive);
    /* �޴� ���¿��� [���ư���] ��ư CLICK */
    void inMenu_ReturnToGameScene(bool* name, bool isActive);

    /* �޴� ���¿��� [���� �� ������] ��ư ENTER, EXIT */
    void inMenu_AcitveChoiceImg_SaveAndExit(bool isActive);

	//������//
	UIBase* enemyWaveSkip;
	UIBase* enemyWaveSkipClick;
	Button* enemyWaveSkipButton;

	/* ���� Enemy Wave Skip ENTER ,EXIT */
	void EnemyWaveSkip(bool isActive);

	EnemyManager* enemyManager;
	void SetEnemyManager(EnemyManager* enemymanager) { enemyManager = enemymanager; }

	/* ���� Enemy Wave Skip CLICK*/
	void EnemyWaveSkipClick();
};