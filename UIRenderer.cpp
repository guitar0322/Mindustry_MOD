#include "stdafx.h"
#include "UIRenderer.h"

UIRenderer::UIRenderer()
{
}

UIRenderer::~UIRenderer()
{
}

void UIRenderer::Init(string clipName)
{
	AnimationClip* targetClip = CLIPMANAGER->FindClip(clipName);
	if (targetClip == nullptr)
	{
		throw("UIrenderer Init error. Invalid AnimationClip");
	}
	_targetBitmap = targetClip->GetBitmap();
	_frameWidth = targetClip->GetFrameWidth();
	_frameHeight = targetClip->GetFrameHeight();
	_curFrameX = 0;
	_curFrameY = 0;
	_alpha = 1.f;
	_rc = RectMakePivot(transform->position, Vector2(_frameWidth, _frameHeight), Pivot::Center);
}

void UIRenderer::Update()
{
	_rc = RectMakePivot(transform->position, Vector2(_frameWidth, _frameHeight), Pivot::Center);
}

void UIRenderer::Render()
{
	int startX = transform->GetX() - _frameWidth / 2;
	int startY = transform->GetY() - _frameHeight / 2;
	D2D1_SIZE_F bitmapSize = _targetBitmap->GetSize();
	//그려질 영역
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
			startX,
			startY,
			startX + _frameWidth,
			startY + _frameHeight
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
	D2DRENDERER->GetRenderTarget()->SetTransform(rotation * scale);
	D2DRENDERER->GetRenderTarget()->DrawBitmap(_targetBitmap, backbufferArea, _alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, clipArea);
}