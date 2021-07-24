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
class PlayerControler;

class UIControler
{
private:
    int _selectCategoryIdx;
    int _selectPropIdx;
    int _previewNum;
    Vector2 _deleteStart;
    bool _previewDir;
    Vector2 _worldStartPtMouse;
    vector<string> _clipArr[CATEGORY_NUM];
    vector<ImageObject> _previewV;
    PROPDIR _dir;
    Rect _deleteRc;
    PlayerControler* _playerControler;
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
    void LinkPlayerControler(PlayerControler* playerControler) { _playerControler = playerControler; }

    /* �ÿ� */
    bool* isMineral;

    /* ������ */
    UIBase* coreDBIcon;                         // �ھ� �����ͺ��̽� ������
    UIBase* researchIcon;                       // ���� ������
    UIBase* inGame_TouchToIcon;                 // ����ȭ�� ������ ī�װ� �����ܿ� ENTER ���� ��� ������ ȸ�� �̹���

    // ����
    /* ��ü �ڿ� ��ư (ȸ��) */
    int     all_Resources_Count;

    UIBase* all_Resources_Open1_Img;            // ��ü �ڿ� [����] 1��
    UIBase* all_Resources_Open2_Img;            // ��ü �ڿ� [����] 2��
    UIBase* all_Resources_Open3_Img;            // ��ü �ڿ� [����] 3��
    UIBase* all_Resources_Close_Img;            // ��ü �ڿ� [����]
    UIBase* all_Resources_Img;                  // ��ü �ڿ� ��ư (ȸ��)
    UIBase* all_Resources_Text;                 // ��ü �ڿ� �ؽ�Ʈ

    /* ? */
    UIBase* choiceImg;
    UIBase* lockImg;
    UIBase* inResearchChoiceImg;

    /* ���� */
    UIBase* research_goBackIdleImg;             // ���� [�ڷΰ���] �⺻ ���� �̹���
    UIBase* research_goBackChoiceImg;           // ���� [�ڷΰ���] ���� ���� �̹���
    UIBase* coreDBIdleImg;                      // ���� [�ھ� �����ͺ��̽�] �⺻ ���� �̹���
    UIBase* coreDBChoiceImg;                    // ���� [�ھ� �����ͺ��̽�] ���� ���� �̹���

    /* �󼼺��� */
    UIBase* detailDes_GoBackIdleImg;            // ���� - �󼼺��� [�ڷΰ���] �⺻ ���� �̹���
    UIBase* detailDes_GoBackChoiceImg;          // ���� - �󼼺��� [�ڷΰ���] ���� ���� �̹���

    // �޴�
    UIBase* menu_GoBackIdleImg;                 // �޴� [���ư���] �⺻ ���� �̹���
    UIBase* menu_GoBackChoiceImg;               // �޴� [���ư���] ���� ���� �̹���
    UIBase* menu_SettingIdleImg;                // �޴� [����] �⺻ ���� �̹���
    UIBase* menu_SettingChoiceImg;              // �޴� [����] ���� ���� �̹���
    UIBase* menu_SaveAndExitIdleImg;            // �޴� [���� �� ������] �⺻ ���� �̹���
    UIBase* menu_SaveAndExitChoiceImg;          // �޴� [���� �� ������] ���� ���� �̹���
    Button* menu_SaveAndExitButton;             // �޴� [���� �� ������] ��ư

    /* ������ ����? */
    UIBase* menu_ReallyEnd_Img;                 // ������ �����Ͻðڽ��ϱ�? �̹���
    UIBase* menu_ReallyEnd_Check_Idle;          // ������ �����Ͻðڽ��ϱ�? [Ȯ��] �⺻ ���� �̹���
    UIBase* menu_ReallyEnd_Check_Choice;        // ������ �����Ͻðڽ��ϱ�? [Ȯ��] ���� ���� �̹���
    UIBase* menu_ReallyEnd_Cancle_Idle;         // ������ �����Ͻðڽ��ϱ�? [���] �⺻ ���� �̹���b
    UIBase* menu_ReallyEnd_Cancle_Choice;       // ������ �����Ͻðڽ��ϱ�? [���] ���� ���� �̹���

    /* Ŀ�� (����) ���� �Լ� */
    void inGame_Crash_To_Mineral_Cursor();

    /* ���� ���¿��� [������] ENTERT, EXIT */
    void inGame_Acitve_Choice_Img(GameObject* clickedButton, bool isAcitve);

    /* ���� ���¿��� [���� ������] CLICK */
    void inGame_Acitve_State(bool* name, bool isAcitve);

    void inResearch_ActiveChoiceImg(Transform* menuTr, bool isActive);

    /* ���� ���¿��� [��ü�ڿ�] ��ư EVENT */
    void inResearch_Active_Choice_Img(bool* name);
    /* ���� ���¿��� [��ü�ڿ�] ��ư CLICK*/
    void inResearch_Active_all_Resources_Click_Event(bool* name);
    /* ���� ���¿��� [��ü�ڿ�] ��ư EXIT */
    void inResearch_InActive_Choice_Img();
    
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

    /* ���� ����ٰ� �߰��ϼ��� */
    /* �޴� ���¿��� [����] ��ư ENTERT, EXIT */
    /* �޴� ���¿��� [����] ��ư CLICK */

    /* �޴� ���¿��� [���� �� ������] ��ư ENTER, EXIT */
    void inMenu_AcitveChoiceImg_SaveAndExit(bool isActive);
    /* �޴� ���¿��� [���� �� ������] ��ư CLICK */
    void inMenu_AcitveRellayEnd(bool* name, bool isAcitve);

    /* ������ �����Ͻðڽ��ϱ�? ���¿��� [���] ��ư ENTERT, EXIT */
    void inReallyEnd_Active_CancleImg(bool* name, bool isActive);
    /* ������ �����Ͻðڽ��ϱ�? ���¿��� [���] ��ư CLICK */
    void inReallyEnd_Return_To_MenuState(bool* name, bool isAcitve);

    /* ������ �����Ͻðڽ��ϱ�? ���¿��� [Ȯ��] ��ư ENTERT, EXIT */
    void inReallyEnd_Active_CheckImg(bool* name, bool isActive);
    /* ������ �����Ͻðڽ��ϱ�? ���¿��� [Ȯ��] ��ư CLICK */
    void inReallyEnd_Return_To_TilteScene(bool* isQuit);

    //������//
    UIBase* enemyWaveSkip;
    UIBase* enemyWaveSkipClick;
    Button* enemyWaveSkipButton;
    
    /* ���� Enemy Wave Skip ENTER ,EXIT */
    void EnemyWaveSkip();
    void EnemyWaveSkipExit();
    
    EnemyManager* enemyManager;
    void SetEnemyManager(EnemyManager* enemymanager) { enemyManager = enemymanager; }
    
    /* ���� Enemy Wave Skip CLICK*/
    void EnemyWaveSkipClick();
};