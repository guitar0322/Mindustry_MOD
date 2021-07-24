#include "stdafx.h"
#include "gameNode.h"

gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

HRESULT gameNode::init()
{
    //_hdc = GetDC(_hWnd);

    SetTimer(_hWnd, 1, 10, NULL);

    return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
    //_hdc = GetDC(_hWnd);
    _managerInit = managerInit;

    if (_managerInit)
    {
        SetTimer(_hWnd, 1, 10, NULL);
        KEYMANAGER->init();
        IMAGEMANAGER->init();
        TAGMANAGER->init();
        TIMEMANAGER->init();
        SCENEMANAGER->Init();
        COLLIDERMANAGER->Init();
        CAMERAMANAGER->Init();
        SOUNDMANAGER->init();
        TXTDATAMANAGER->Init();
        CLIPMANAGER->Init();
        EFFECTMANAGER->Init();
        UIMANAGER->Init();
        MOUSEMANAGER->Init();
    }

    return S_OK;
}

void gameNode::release()
{
    KillTimer(_hWnd, 1);
    KEYMANAGER->release();
    KEYMANAGER->releaseSingleton();

    COLLIDERMANAGER->Release();
    COLLIDERMANAGER->releaseSingleton();

    CAMERAMANAGER->Release();
    CAMERAMANAGER->releaseSingleton();

    TAGMANAGER->release();
    TAGMANAGER->releaseSingleton();

    TIMEMANAGER->release();
    TIMEMANAGER->releaseSingleton();

    SCENEMANAGER->Release();
    SCENEMANAGER->releaseSingleton();

    SOUNDMANAGER->release();
    SOUNDMANAGER->releaseSingleton();

    TXTDATAMANAGER->release();
    TXTDATAMANAGER->releaseSingleton();

    CLIPMANAGER->Release();
    CLIPMANAGER->releaseSingleton();

    EFFECTMANAGER->Release();
    EFFECTMANAGER->releaseSingleton();

    UIMANAGER->Release();
    UIMANAGER->releaseSingleton();

    MOUSEMANAGER->Release();
    MOUSEMANAGER->releaseSingleton();
}

void gameNode::update()
{
    InvalidateRect(_hWnd, NULL, false);
}

void gameNode::render(HDC hdc)
{
    // ���� �ǵ�������
    //================���� �� ���̿� �� �׸��ô�==========================

    //==================================================
    //���⵵ �ǵ�������
}
int delta = 0;
LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC         hdc; //�� �� �߿��մ�...


    switch (iMessage)
    {
    case WM_TIMER:
        //this->update();
        break;

    case WM_CHAR:
        _inputChar = wParam;
        UIMANAGER->OnKeyDown(wParam);
        break;
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);

        this->render(hdc);

        EndPaint(hWnd, &ps);
        break;
    }
    break;
    //���콺 �����̸� ���⼭ �޼��� �߻�
    case WM_MOUSEMOVE:
        _ptMouse.x = static_cast<float>(LOWORD(lParam));
        _ptMouse.y = static_cast<float>(HIWORD(lParam));
        break;
    case WM_MOUSEWHEEL:
        if (MainCam != nullptr)
        {
            int delta = (float)GET_WHEEL_DELTA_WPARAM(wParam);
            MainCam->_zoomScale += (float)GET_WHEEL_DELTA_WPARAM(wParam) / 1200.f;
            if (MainCam->_zoomScale <= 1.f)
                MainCam->_zoomScale = 1.f;
        }
        break;
    case WM_KEYDOWN:

        switch (wParam)
        {
        case VK_ESCAPE:
            /* �ÿ� �ּ� 210720 */
            //PostQuitMessage(0);
            break;
        }
        break;


        //������ â �ν���(?) 
    case WM_DESTROY:
        //������ �����Լ�
        PostQuitMessage(0);
        return 0;
    }


    return (DefWindowProc(hWnd, iMessage, wParam, lParam));

}