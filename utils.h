#pragma once
#include "GameObject.h"
#include "ParticleSystem.h"
#include "Renderer.h"
#include "AnimationClip.h"
#include "Animator.h"
#include "BoxCollider.h"
#include "UIRenderer.h"
#include "UIMouseEvent.h"
#include "EditText.h"
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
#include "Projectile.h"
#include "EnemyManager.h"

namespace HDY_UTIL
{
	float GetDistance(float x1, float y1, float x2, float y2);
	float GetDistance(const Vector2& v1, const Vector2& v2);

	template <typename T>
	T GetDistance(T a, T b);
	
	float ConvertAngleD2D(const float& angle);
	float ConvertAngleAPI(const float& angle);
	float GetAngle(float x1, float y1, float x2, float y2);
	float GetAngle(Vector2& v1, Vector2& v2);


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
	Vector2 MoveTowardTo(float x1, float y1, float x2, float y2, float speed, int limit = 0);
	Vector2 MoveTowardTo(RECT& rc1, RECT& rc2, float speed, int limit = 0);
}