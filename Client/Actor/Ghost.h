#pragma once

#include "Actor/DrawableActor.h"
#include "Tile/Tile.h"
#include <list>

class Tile;
class Ghost : public DrawableActor
{
	RTTI_DECLARATIONS(Ghost, DrawableActor)

public:
	Ghost(const Vector2& _position);

public:
	virtual void Update(float delatTime);
	virtual const char* Serialize() override;
	void Make_Route();
	void Move(float deltaTime);
private:
	list<Tile*> m_BestRoute;

	const float m_fSpeedX = 5.5f;
	const float m_fSpeedY = 3.f;
	float m_fCurrentSpeed = 0,f;
	float m_fMovement = 0.f;
};