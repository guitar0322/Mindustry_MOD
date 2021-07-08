#include "stdafx.h"
#include "Outline.h"

void Outline::Init()
{
	renderer = gameObject->GetComponent<Renderer>();
	_lineColor = RGB(255, 230, 89);
	_lineWidth = 10;
}

void Outline::Update()
{
}

void Outline::Render()
{
}

void Outline::SetTargetObject(GameObject* gameObject)
{
	//Renderer* targetRenderer = gameObject->GetComponent<Renderer>();
	//HBRUSH lineBrush = CreateSolidBrush(_lineColor);
	//HBRUSH oBrush;
	//BLENDFUNCTION blendFunc;
	//COLORREF backPixel;
	//blendFunc.BlendOp = AC_SRC_OVER;
	//blendFunc.BlendFlags = 0;
	//blendFunc.AlphaFormat = 0;
	//blendFunc.SourceConstantAlpha = 5;
	//renderer->Resize(targetRenderer->GetWidth() + _lineWidth, targetRenderer->GetHeight() + _lineWidth);
	//oBrush = (HBRUSH)SelectObject(renderer->memDC, lineBrush);
	//PatBlt(renderer->memDC, 0, 0, renderer->GetWidth(), renderer->GetHeight(), PATCOPY);
	//AlphaBlend(renderer->memDC, 0, 0, renderer->GetWidth(), renderer->GetHeight(),
	//	targetRenderer->memDC, 0, 0, targetRenderer->GetWidth(), targetRenderer->GetHeight(), blendFunc);
	//backPixel = GetPixel(renderer->memDC, 0, 0);
	//renderer->SetTransColor(backPixel);
}
