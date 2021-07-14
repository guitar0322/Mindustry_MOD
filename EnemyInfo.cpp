#include "stdafx.h"
#include "EnemyInfo.h"

EnemyInfo::EnemyInfo()
{
}

EnemyInfo::~EnemyInfo()
{
}

void EnemyInfo::Init()
{
	_angle = GetAngle(transform->position, _testCoreTransform->position);
}

void EnemyInfo::Update()
{
	_angle = GetAngle(transform->position, _testCoreTransform->position);
}
