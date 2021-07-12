#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
enum class Pivot : int
{
	LeftTop, Center, BottomCenter
};

namespace Direction
{
	enum Enum : int
	{
		Left = 1,
		Top = 2,
		Right = 4,
		Bottom = 8,
		LeftTop = Left | Top,
		LeftBottom = Left | Bottom,
		RightTop = Right | Top,
		RightBottom = Right | Bottom,
		End = 0
	};

}

//매니저 헤더 파일
#include "ManagerHeader.h"

//라이브러리 헤더 파일
#include "LibraryHeader.h"
#include "Vector2.h"
#include "Math.h"
#include "Geometry.h"

using namespace MyGeometry;
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>
#include <typeinfo>
#include <vector>
#include <assert.h>
#include "D2DRenderer.h"
#include "commonMacroFunction.h"
#include "randomFunction.h"

#include "utils.h"

using namespace std;
using namespace HDY_UTIL;

//==================================
// ## 매크로 처리 ## 21.04.23 ##
//==================================

#define WINNAME (LPTSTR)(TEXT("28기 API"))
#define WINSTARTX 10	//윈도우 창 시작좌표 (left)
#define WINSTARTY 0	//윈도우 창 시작좌표 (top)
#define WINSIZEX 1350	//윈도우 가로크기
#define WINSIZEY 852	//윈도우 세로크기
#define WINSTYLE WS_CAPTION | WS_SYSMENU

#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define COLLIDERMANAGER ColliderManager::getSingleton()
#define CAMERAMANAGER CameraManager::getSingleton()
#define TAGMANAGER TagManager::getSingleton()
#define DATAMANAGER TextDataManager::getSingleton()
#define TIMEMANAGER TimeManager::getSingleton()
#define SCENEMANAGER SceneManager::getSingleton()
#define ZORDER ZOrderManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
#define TXTDATAMANAGER TextDataManager::getSingleton()
#define CLIPMANAGER ClipManager::getSingleton()
#define EFFECTMANAGER EffectManager::getSingleton()
#define D2DRENDERER D2DRenderer::GetInstance()

#define MainCam CAMERAMANAGER->GetMainCam()
#define BackBuffer D2DRenderer::GetInstance()->GetBackBuffer()
#define MAPWIDTH BackBuffer->GetSize().width
#define MAPHEIGHT BackBuffer->GetSize().height

#define SAFE_DELETE(p)		{if(p) {delete(p); (p) = NULL;}}
#define SAFE_RELEASE(p)		{if(p) {(p)->release(); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p) {if(p) {delete[](p); (p) = NULL;}}
#define NEW_SAFE_RELEASE(p) {if(p){p->Release(); (p) = NULL;}}


//==================================
// ## extern ## 21.04.28 ##
//==================================
extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern Vector2 _ptMouse;
extern char debug[3][128];
extern char error[128];
extern HDC _hdc;