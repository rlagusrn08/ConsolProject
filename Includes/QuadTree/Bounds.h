#pragma once
#include "Core.h"

// �簢�� ������ ǥ���ϴ� Ŭ����.
class ENGINE_API Bounds
{
public:
	Bounds(float x, float y, float width = 0.0f, float height = 0.0f)
		: x(x), y(y), width(width), height(height)
	{
	}

	// Getter.
	float X() const { return x; }
	float Y() const { return y; }
	float Width() const { return width; }
	float Height() const { return height; }

	float MaxX() const { return x + width; }
	float MaxY() const { return y + height; }

	// ��ħ ���� �Լ�.
	bool Intersects(const Bounds& other) const;

private:
	// ���ʻ�� ����.
	float x = 0;
	float y = 0;
	float width = 1;
	float height = 1;
};