#pragma once

#include "Actor/DrawableActor.h"

class Ghost : public DrawableActor
{
	RTTI_DECLARATIONS(Ghost, DrawableActor)

public:
	Ghost(const Vector2& _position);

public:
	virtual void Update(float delatTime);
};