#include "stdafx.h"
#include "ClipManager.h"
#include <io.h>

ClipManager::ClipManager()
	: mWicFactory(nullptr)
{
	CoInitialize(NULL);
	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&mWicFactory));
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif
}

ClipManager::~ClipManager()
{
}

void ClipManager::Init()
{
}
void ClipManager::Release()
{
}

AnimationClip* ClipManager::AddClip(string clipName, string filePath, int width, int height, int frameNumX, int frameNumY, float frameTerm)
{
	AnimationClip* clip = FindClip(clipName);

	if (clip != nullptr)
		return clip;

	//멀티바이트 string을 유니코드 wstring 으로 변환
	wstring clipNameW;
	clipNameW.assign(filePath.begin(), filePath.end());

	ID2D1Bitmap* clipBitmap = CreateBitmapFromFile(clipNameW);

	clip = new AnimationClip();
	clip->SetLoadName(clipName);

	clip->Init(clipBitmap, width, height, frameNumX, frameNumY, frameTerm, true);
	_clipMap.insert(pair<string, AnimationClip*>(clipName, clip));

	return clip;
}

AnimationClip* ClipManager::AddClip(string clipName, string filePath, int width, int height)
{
	AnimationClip* clip = FindClip(clipName);

	if (clip != nullptr)
		return clip;

	wstring clipNameW;
	clipNameW.assign(filePath.begin(), filePath.end());

	ID2D1Bitmap* clipBitmap = CreateBitmapFromFile(clipNameW);

	clip = new AnimationClip();
	clip->SetLoadName(clipName);

	clip->Init(clipBitmap, width, height, 1, 1, Math::IntMax, true);
	_clipMap.insert(pair<string, AnimationClip*>(clipName, clip));

	return clip;
}

//AddClip에서 추가한 clipName으로 AnimationClip을 찾아줌, 찾지 못했을 경우 nullptr을 반환
AnimationClip* ClipManager::FindClip(string clipName)
{
    _clipMapIter = _clipMap.find(clipName);

    //찾았다!
    if (_clipMapIter != _clipMap.end())
    {
        return _clipMapIter->second;
    }

    return nullptr;
}

ID2D1Bitmap* ClipManager::CreateBitmapFromFile(wstring &filePath)
{
	//디코더 생성
	IWICBitmapDecoder* ipDecoder = nullptr;
	HRESULT hr;
	hr = mWicFactory->CreateDecoderFromFilename(filePath.c_str(), NULL, GENERIC_READ,
		WICDecodeMetadataCacheOnDemand, &ipDecoder);
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif
	//디코더에서 프레임얻음
	IWICBitmapFrameDecode* ipFrame = nullptr;
	hr = ipDecoder->GetFrame(0, &ipFrame);
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif
	//프레임을 기반으로 포맷 컨버터 생성
	IWICFormatConverter* convertedSrcBmp = nullptr;
	hr = mWicFactory->CreateFormatConverter(&convertedSrcBmp);
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif
	//컨버터 초기화
	hr = convertedSrcBmp->Initialize
	(
		ipFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0f,
		WICBitmapPaletteTypeCustom
	);
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif
	//컨버트된 데이터를 기반으로 실제 Direct2D용 비트맵을 생성
	ID2D1Bitmap* ipResult = nullptr;
	hr = D2DRenderer::GetInstance()->GetRenderTarget()->CreateBitmapFromWicBitmap
	(
		convertedSrcBmp,
		nullptr,
		&ipResult
	);
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif

	NEW_SAFE_RELEASE(convertedSrcBmp);
	NEW_SAFE_RELEASE(ipFrame);
	NEW_SAFE_RELEASE(ipDecoder);

	return ipResult;
}
