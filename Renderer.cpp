#include "stdafx.h"
#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Init(string clipName)
{
	AnimationClip* targetClip = CLIPMANAGER->FindClip(clipName);
	if (targetClip == nullptr)
	{
		throw("renderer Init error");
	}
	_clipName = clipName;
	_targetBitmap = targetClip->GetBitmap();
	_frameWidth = targetClip->GetFrameWidth();
	_frameHeight = targetClip->GetFrameHeight();
	_curFrameX = 0;
	_curFrameY = 0;
	_alpha = 1.f;
}

void Renderer::Init(float width, float height)
{
	_frameWidth = width;
	_frameHeight = height;
	_curFrameX = 0;
	_curFrameY = 0;
	_alpha = 1.f;
	_clipName = "";
}

void Renderer::Render()
{
	int renderStartX = transform->GetX() - _frameWidth / 2;
	int renderStartY = transform->GetY() - _frameHeight / 2;
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		D2DRENDERER->DrawRectangle(_rc, D2DRenderer::DefaultBrush::Gray);
	}
	D2D1_RECT_F clipArea = 
		D2D1::RectF
		(
			_curFrameX * _frameWidth, 
			_curFrameY * _frameHeight, 
			(_curFrameX + 1) * _frameWidth,
			(_curFrameY + 1) * _frameHeight
		);
	//그릴 영역
	D2D1_RECT_F backbufferArea 
		= D2D1::RectF
		(
			renderStartX, 
			renderStartY, 
			renderStartX + _frameWidth, 
			renderStartY + _frameHeight
		);

	D2D1_MATRIX_3X2_F rotation = D2D1::Matrix3x2F::Rotation(
		transform->angle,
		D2D1::Point2F(transform->GetX(), transform->GetY())
	);

	D2D1_MATRIX_3X2_F scale = D2D1::Matrix3x2F::Scale(
		transform->GetScaleX(),
		transform->GetScaleY(),
		D2D1::Point2F(transform->GetX(), transform->GetY())
	);
	BackBuffer->SetTransform(rotation * scale);

	if (_targetBitmap == nullptr)
	{
		BackBuffer->SetTransform(D2D1::Matrix3x2F::Identity());
		return;
	}
	BackBuffer->DrawBitmap(_targetBitmap, backbufferArea, _alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, clipArea);
	BackBuffer->SetTransform(D2D1::Matrix3x2F::Identity());
}


void Renderer::Update()
{
	_rc = RectMakePivot(transform->position, Vector2(_frameWidth, _frameHeight), Pivot::Center);
}

void Renderer::Release()
{
}

void Renderer::OnEnable()
{
	_rc = RectMakePivot(transform->position, Vector2(_frameWidth, _frameHeight), Pivot::Center);
}

void Renderer::OnDisable()
{
}

/***********************************************
렌더러의 대상 비트맵을 변경(클립변경)
프레임 인덱스를 0으로 초기화
newBitmap : 새로운 대상 비트맵
frameWidth : 새로운 비트맵의 프레임당 넓이
frameHeight : 새로운 비트맵의 새로운 높이
***********************************************/
void Renderer::ChangeTargetBitmap(string clipName)
{
	AnimationClip* targetClip = CLIPMANAGER->FindClip(clipName);
	if (targetClip == nullptr)
	{
		throw("renderer error");
	}
	_clipName = clipName;
	_targetBitmap = targetClip->GetBitmap();
	_frameWidth = targetClip->GetFrameWidth();
	_frameHeight = targetClip->GetFrameHeight();
	_curFrameX = 0;
}

/***********************************************
렌더러의 대상 비트맵을 변경(클립변경)
newBitmap : 새로운 대상 비트맵
frameWidth : 새로운 비트맵의 프레임당 넓이
frameHeight : 새로운 비트맵의 새로운 높이
inInitFrmae : true면 프레임 인덱스를 0으로 초기화
***********************************************/
void Renderer::ChangeTargetBitmap(string clipName, int startFrame)
{
	AnimationClip* targetClip = CLIPMANAGER->FindClip(clipName);
	if (targetClip == nullptr)
	{
		throw("renderer error");
	}
	_clipName = clipName;
	_targetBitmap = targetClip->GetBitmap();
	_frameWidth = targetClip->GetFrameWidth();
	_frameHeight = targetClip->GetFrameHeight();
	_curFrameX = startFrame;
}
