#pragma once

#include "Actor/DrawableActor.h"

class Target : public DrawableActor
{
	RTTI_DECLARATIONS(Target, DrawableActor)

public:
	Target(const Vector2& _position);

public:
	virtual void Update(float delatTime);
	virtual void Draw();
	virtual const char* Serialize() override;
};