#include "stdafx.h"
#include "D2DRenderer.h"

/*****************************************************
## D2DRenderer ##
*******************************************************/
D2DRenderer::D2DRenderer()
	:mD2DFactory(nullptr), mD2DRenderTarget(nullptr), mDWFactory(nullptr)
{
	this->CreateFactory();
	this->CreateRenderTarget();
	this->CreateDefaultBrush();
	this->AddTextFormat(L"맑은고딕");
	this->AddTextFormat(L"배달의민족 한나체 Pro");
	this->AddTextFormat(L"-윤디자인웹돋움");
	this->AddTextFormat(L"fontello");
	mD2DRenderTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
}

/*****************************************************
## ~D2DRenderer ##
******************************************************/
D2DRenderer::~D2DRenderer()
{
	TextIter iter = mFontList.begin();
	for (; iter != mFontList.end(); ++iter)
		NEW_SAFE_RELEASE(iter->second);

	for (UINT i = 0; i < (UINT)DefaultBrush::End; ++i)
		NEW_SAFE_RELEASE(mDefaultBrushList[i]);
	
	NEW_SAFE_RELEASE(mDWFactory);

	NEW_SAFE_RELEASE(mD2DSurface);
	NEW_SAFE_RELEASE(mD2DBitmapRenderTarget);
	NEW_SAFE_RELEASE(mD2DRenderTarget);
	NEW_SAFE_RELEASE(mD2DFactory);
}
/*****************************************************
## BeginRender ##
*******************************************************/
void D2DRenderer::BeginRender(const D2D1::ColorF& backgroundColor)
{
	mD2DRenderTarget->BeginDraw();
	mD2DRenderTarget->Clear(backgroundColor);

	mD2DBitmapRenderTarget->BeginDraw();
	mD2DBitmapRenderTarget->Clear(backgroundColor);
}
/*****************************************************
## EndRender ##
*******************************************************/
void D2DRenderer::EndRender()
{
	mD2DRenderTarget->EndDraw();
}


/*****************************************************
## CreateFactory ##
*******************************************************/
void D2DRenderer::CreateFactory()
{
	//1) D2D 팩토리 생성
	//싱글쓰레드타입으로 
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mD2DFactory);
	assert(SUCCEEDED(hr));
	//2) DWriteFactory 생성
	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(*&mDWFactory),
		(IUnknown**)&mDWFactory
	);
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif
}
/*****************************************************
## CreateRenderTarget ##
*******************************************************/
void D2DRenderer::CreateRenderTarget()
{
	//렌더타겟이란 백버퍼의 역할을 하는 클래스이자 여러 렌더링을 위한 유틸적인 것들이 들어있는 클래스다
	//해서 화면에 뭔가 렌더링을 요청하려면 렌더타겟을 통해서만 가능하다

	HRESULT hr;
	//1) 윈도우 핸들을 통해서 화면 Rect를 받아온다 (GetClientRect)
	RECT clientRect;
	GetClientRect(_hWnd, &clientRect);

	//이전에는 Factory를 통해서 현재 디바이스의 DPI를 받아 왔으나 어떤 이유에서인지 MS에서 해당 함수를 사용하지 못하게 변경함, 자체 API함수로 불러오자
	//mD2DFactory->GetDesktopDpi(&dpiX, &dpiY)

	//2) 디바이스의 DPI정보를 받아온다. (WinAPI 함수)
	FLOAT dpiX = GetDeviceCaps(_hdc, LOGPIXELSX);
	FLOAT dpiY = GetDeviceCaps(_hdc, LOGPIXELSY);

	//3) 렌더타겟을 생성하기 위한 속성값들 초기화
	D2D1_RENDER_TARGET_PROPERTIES renderTargetProperties = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT,
		D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), dpiX, dpiY);

	//4) 렌더타겟의 사이즈 초기화(화면 크기로)
	clientRect = RectMake(0, 0, WINSIZEX, WINSIZEY);
	D2D1_SIZE_U renderTargetSize = D2D1::SizeU(clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
	
	//5) 렌더타겟 생성
	hr = mD2DFactory->CreateHwndRenderTarget(
		renderTargetProperties,
		D2D1::HwndRenderTargetProperties(_hWnd, renderTargetSize),
		&mD2DRenderTarget
	);
	assert(SUCCEEDED(hr));

	//6) 렌더 타겟 백버퍼 생성
	hr = mD2DRenderTarget->CreateCompatibleRenderTarget
	(
		D2D1::SizeF(WINSIZEX, WINSIZEY),
		D2D1::SizeU(WINSIZEX, WINSIZEY),
		&mD2DBitmapRenderTarget
	);

	assert(SUCCEEDED(hr));
}
void D2DRenderer::CreateNewBackBuffer(int width, int height)
{
	HRESULT hr;
	NEW_SAFE_RELEASE(mD2DBitmapRenderTarget);
	hr = mD2DRenderTarget->CreateCompatibleRenderTarget
	(
		D2D1::SizeF(width, height),
		D2D1::SizeU(width, height),
		&mD2DBitmapRenderTarget
	);
	assert(SUCCEEDED(hr));
}
/*****************************************************
## CreateDefaultBrush ##
*******************************************************/
void D2DRenderer::CreateDefaultBrush()
{
	this->mD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black, 1.0f), &mDefaultBrushList[(UINT)DefaultBrush::Black]);
	this->mD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White, 1.0f), &mDefaultBrushList[(UINT)DefaultBrush::White]);
	this->mD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow, 1.0f), &mDefaultBrushList[(UINT)DefaultBrush::Yellow]);
	this->mD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red, 1.0f), &mDefaultBrushList[(UINT)DefaultBrush::Red]);
	this->mD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue, 1.0f), &mDefaultBrushList[(UINT)DefaultBrush::Blue]);
	this->mD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green, 1.0f), &mDefaultBrushList[(UINT)DefaultBrush::Green]);
	this->mD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray, 1.0f), &mDefaultBrushList[(UINT)DefaultBrush::Gray]);
}
/*****************************************************
## AddTextFormat ##
@@ wstring font : 폰트명
@@ float defaultSize : 폰트 사이즈 = 1.f
*******************************************************/
void D2DRenderer::AddTextFormat(const wstring& font, const float& defaultSize)
{
	HRESULT hr;
	IDWriteTextFormat* format = NULL;

	hr = this->mDWFactory->CreateTextFormat(
		font.c_str(),
		NULL,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		defaultSize,
		L"ko",
		&format
	);
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif

	this->mFontList.insert(make_pair(font, format));
}

void D2DRenderer::DrawBackBuffer(float bitmapStartX, float bitmapStartY, float bitmapEndX, float bitmapEndY,
	float screenStartX, float screenStartY, float screenEndX, float screenEndY)
{
	mD2DBitmapRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	mD2DBitmapRenderTarget->EndDraw();
	mD2DBitmapRenderTarget->GetBitmap(&mD2DBitmap);

	D2D1_SIZE_F bitmapSize = D2D1::SizeF(bitmapEndX - bitmapStartX, bitmapEndY - bitmapStartY);
	D2D1_SIZE_F screenSize = D2D1::SizeF(screenEndX - screenStartX, screenEndY - screenStartY);
	D2D1_RECT_F renderTargetArea = D2D1::RectF(screenStartX, screenStartY, screenStartX + screenSize.width, screenStartY + screenSize.height);
	D2D1_RECT_F bitmapArea = D2D1::RectF(bitmapStartX, bitmapStartY, bitmapStartX + bitmapSize.width, bitmapStartY + bitmapSize.height);

	/***************************************
	DrawBitmap(그려질 비트맵, 그릴 렌더타겟의 영역, 알파값, 렌더링 모드, 그려질 비트맵의 영역)
	***************************************/
	mD2DRenderTarget->DrawBitmap(
		mD2DBitmap,
		&renderTargetArea,
		1.f,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		&bitmapArea
	);

	NEW_SAFE_RELEASE(mD2DBitmap);
}


