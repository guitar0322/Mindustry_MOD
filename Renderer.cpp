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
	_targetBitmap = targetClip->GetBitmap();
	_frameWidth = targetClip->GetFrameWidth();
	_frameHeight = targetClip->GetFrameHeight();
	_curFrameX = 0;
	_curFrameY = 0;
	_alpha = 1.f;
}

void Renderer::Render()
{
	int renderStartX = transform->GetX() - _frameWidth / 2;
	int renderStartY = transform->GetY() - _frameHeight / 2;
	//�׷��� ����
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
	BackBuffer->DrawBitmap(_targetBitmap, backbufferArea, _alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, clipArea);
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
�������� ��� ��Ʈ���� ����(Ŭ������)
������ �ε����� 0���� �ʱ�ȭ
newBitmap : ���ο� ��� ��Ʈ��
frameWidth : ���ο� ��Ʈ���� �����Ӵ� ����
frameHeight : ���ο� ��Ʈ���� ���ο� ����
***********************************************/
void Renderer::ChangeTargetBitmap(ID2D1Bitmap* newBitmap, float frameWidth, float frameHeight)
{
	_targetBitmap = newBitmap;
	_frameWidth = frameWidth;
	_frameHeight = frameHeight;
	_curFrameX = 0;
}

/***********************************************
�������� ��� ��Ʈ���� ����(Ŭ������)
newBitmap : ���ο� ��� ��Ʈ��
frameWidth : ���ο� ��Ʈ���� �����Ӵ� ����
frameHeight : ���ο� ��Ʈ���� ���ο� ����
inInitFrmae : true�� ������ �ε����� 0���� �ʱ�ȭ
***********************************************/
void Renderer::ChangeTargetBitmap(ID2D1Bitmap* newBitmap, float frameWidth, float frameHeight, bool isInitFrame)
{
	_targetBitmap = newBitmap;
	_frameWidth = frameWidth;
	_frameHeight = frameHeight;
	if (isInitFrame == true)
	{
		_curFrameX = 0;
	}
}
