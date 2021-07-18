#include "stdafx.h"
#include "ClipManager.h"
#include "AnimationClip.h"
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

	//��Ƽ����Ʈ string�� �����ڵ� wstring ���� ��ȯ
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

//AddClip���� �߰��� clipName���� AnimationClip�� ã����, ã�� ������ ��� nullptr�� ��ȯ
AnimationClip* ClipManager::FindClip(string clipName)
{
    _clipMapIter = _clipMap.find(clipName);

    //ã�Ҵ�!
    if (_clipMapIter != _clipMap.end())
    {
        return _clipMapIter->second;
    }

    return nullptr;
}

ID2D1Bitmap* ClipManager::CreateBitmapFromFile(wstring &filePath)
{
	//���ڴ� ����
	IWICBitmapDecoder* ipDecoder = nullptr;
	HRESULT hr;
	hr = mWicFactory->CreateDecoderFromFilename(filePath.c_str(), NULL, GENERIC_READ,
		WICDecodeMetadataCacheOnDemand, &ipDecoder);
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif
	//���ڴ����� �����Ӿ���
	IWICBitmapFrameDecode* ipFrame = nullptr;
	hr = ipDecoder->GetFrame(0, &ipFrame);
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif
	//�������� ������� ���� ������ ����
	IWICFormatConverter* convertedSrcBmp = nullptr;
	hr = mWicFactory->CreateFormatConverter(&convertedSrcBmp);
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif
	//������ �ʱ�ȭ
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
	//����Ʈ�� �����͸� ������� ���� Direct2D�� ��Ʈ���� ����
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
