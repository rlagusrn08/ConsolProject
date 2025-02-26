#pragma once

#include "Actor/DrawableActor.h"
#include "Struct.h"

class Player : public DrawableActor
{
	enum MOVE_DIRECTION
	{
		MOVE_UP,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT,
		MOVE_NONE
	};

	RTTI_DECLARATIONS(Player, DrawableActor)

public:
	Player(const Vector2& _position);

public:
	virtual void Update(float deltaTime) override;
	virtual const char* Serialize() override;

public:
	void Get_KeyDown();
	void Game_Move(float deltaTime);
	void Tool_Move(float deltaTime);
	void Check_Active_Item(float deltaTime);
	virtual void Intersect(Actor* other);

private:
	MOVE_DIRECTION m_eDir = { MOVE_NONE };
	const float m_fSpeedX = 7.5f;
	const float m_fSpeedY = 5.f;
	float m_fCurrentSpeed = 100;
	float m_fMovement = 0.f;
	DurationTimeInfo m_tItemDurationTime;
};