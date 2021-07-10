#pragma once
#include "GameObject.h"
#include "ParticleSystem.h"
#include "Renderer.h"
#include "AnimationClip.h"
#include "Animator.h"
#include "BoxCollider.h"
#include "UIRenderer.h"
#include "Cam.h"
#include "Camera.h"
#include "UIBase.h"
#include "Text.h"
#include "Box.h"
#include "Zone.h"
#include "ImageObject.h"
#include "Character.h"
#include "ZOrder.h"
#include "DebugText.h"
#include <typeinfo>
#include "EnemyObject.h"

namespace HDY_UTIL
{
	float GetDistance(float x1, float y1, float x2, float y2);
	template <typename T>
	T GetDistance(T x1, T x2);

	float GetAngle(float x1, float y1, float x2, float y2);

	Vector2 WorldToScreen(Vector2 worldPoint);
	Vector2 WorldToScreen(float x, float y);
	Vector2 ScreenToWorld(Vector2 screenPoint);
	Vector2 ScreenToWorld(float x, float y);

	int GetCenterX(RECT rc);
	int GetCenterY(RECT rc);
	POINT GetCenter(RECT rc);
	POINTF GetCenterF(RECT rc);
	int GetWidth(RECT rc);
	int GetHeight(RECT rc);
	template <typename T>
	T GetCenter(T a, T b);
	POINTF GetCollisionPoint(RECT rc1, RECT rc2);
	POINTF MoveTowardTo(float x1, float y1, float x2, float y2, float speed, int limit = 0);
	POINTF MoveTowardTo(RECT& rc1, RECT& rc2, float speed, int limit = 0);
}