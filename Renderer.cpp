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
	_isStatic = false;
	_clipName = clipName;
	_targetBitmap = targetClip->GetBitmap();
	_frameWidth = targetClip->GetFrameWidth();
	_frameHeight = targetClip->GetFrameHeight();
	_curFrameX = 0;
	_curFrameY = 0;
	_alpha = 1.f;
	_clipX = 0;
	_clipY = 0;
	_rc = RectMakePivot(transform->position, Vector2(_frameWidth, _frameHeight), Pivot::Center);
}

void Renderer::Init(float width, float height)
{
	_isStatic = false;
	_frameWidth = width;
	_frameHeight = height;
	_curFrameX = 0;
	_curFrameY = 0;
	_alpha = 1.f;
	_clipName = "";
	_clipX = 0;
	_clipY = 0;
	_rc = RectMakePivot(transform->position, Vector2(_frameWidth, _frameHeight), Pivot::Center);
}

void Renderer::Render()
{
	//if (_isStatic == true)
	//	return;
	int renderStartX = transform->GetX() - _frameWidth / 2;
	int renderStartY = transform->GetY() - _frameHeight / 2;

	//if (IntersectRect(&MainCam->GetRenderRc(), &_rc) == false)
	//{
	//	return;
	//}

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		D2DRENDERER->DrawRectangle(_rc);
	}
	D2D1_RECT_F clipArea = 
		D2D1::RectF
		(
			_curFrameX * _frameWidth + _clipX,
			_curFrameY * _frameHeight + +_clipY,
			(_curFrameX + 1) * _frameWidth,
			(_curFrameY + 1) * _frameHeight
		);
	//�׸� ����
	D2D1_RECT_F backbufferArea 
		= D2D1::RectF
		(
			renderStartX + _clipX,
			renderStartY + _clipY,
			renderStartX + _frameWidth + _clipX,
			renderStartY + _frameHeight + _clipY
		);

	D2D1_MATRIX_3X2_F scale = D2D1::Matrix3x2F::Scale(
			transform->GetScaleX(),
			transform->GetScaleY(),
			D2D1::Point2F(transform->GetX(), transform->GetY())
		);

	D2D1_MATRIX_3X2_F rotation = D2D1::Matrix3x2F::Rotation(
			transform->angle,
			D2D1::Point2F(transform->GetX(), transform->GetY())
		);

	BackBuffer->SetTransform(scale * rotation);

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

void Renderer::RenderStatic()
{
	int renderStartX = transform->GetX() - _frameWidth / 2;
	int renderStartY = transform->GetY() - _frameHeight / 2;
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		D2DRENDERER->DrawRectangle(_rc);
	}
	D2D1_RECT_F clipArea =
		D2D1::RectF
		(
			_curFrameX * _frameWidth,
			_curFrameY * _frameHeight,
			(_curFrameX + 1) * _frameWidth,
			(_curFrameY + 1) * _frameHeight
		);
	//�׸� ����
	D2D1_RECT_F backbufferArea
		= D2D1::RectF
		(
			renderStartX,
			renderStartY,
			renderStartX + _frameWidth,
			renderStartY + _frameHeight
		);

	D2D1_MATRIX_3X2_F scale = D2D1::Matrix3x2F::Identity();

	if (Math::FloatEqual(transform->GetScaleX(), 1.f) == false || Math::FloatEqual(transform->GetScaleY(), 1.f) == false)
	{
		scale = D2D1::Matrix3x2F::Scale(
			transform->GetScaleX(),
			transform->GetScaleY(),
			D2D1::Point2F(transform->GetX(), transform->GetY())
		);
	}
	D2D1_MATRIX_3X2_F rotation = D2D1::Matrix3x2F::Identity();
	if (transform->angle != 0)
	{
		rotation = D2D1::Matrix3x2F::Rotation(
			transform->angle,
			D2D1::Point2F(transform->GetX(), transform->GetY())
		);
	}

	StaticBuffer->SetTransform(scale * rotation);

	if (_targetBitmap == nullptr)
	{
		StaticBuffer->SetTransform(D2D1::Matrix3x2F::Identity());
		return;
	}
	StaticBuffer->DrawBitmap(_targetBitmap, backbufferArea, _alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, clipArea);
	StaticBuffer->SetTransform(D2D1::Matrix3x2F::Identity());
}

void Renderer::DrawFillRect(D2D1::ColorF::Enum color)
{
	if (gameObject->isActive == false || enable == false) return;
	D2DRENDERER->FillRectangleBack(_rc, color, _alpha);
}

/***********************************************
�������� ��� ��Ʈ���� ����(Ŭ������)
������ �ε����� 0���� �ʱ�ȭ
newBitmap : ���ο� ��� ��Ʈ��
frameWidth : ���ο� ��Ʈ���� �����Ӵ� ����
frameHeight : ���ο� ��Ʈ���� ���ο� ����
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
�������� ��� ��Ʈ���� ����(Ŭ������)
newBitmap : ���ο� ��� ��Ʈ��
frameWidth : ���ο� ��Ʈ���� �����Ӵ� ����
frameHeight : ���ο� ��Ʈ���� ���ο� ����
inInitFrmae : true�� ������ �ε����� 0���� �ʱ�ȭ
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
