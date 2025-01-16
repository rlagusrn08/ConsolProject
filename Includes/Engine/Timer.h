#pragma once

#include "Core.h"

// 초시계 클래스.
class ENGINE_API Timer
{
public:

private:
	// 경과 시간.
	float elapsedTime = 0.0f;

	// 목표 시간.
	float targetTime = 0.0f;
};