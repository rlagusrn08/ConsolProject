#pragma once

#include "Actor/DrawableActor.h"

class Item : public DrawableActor
{
	RTTI_DECLARATIONS(Item, DrawableActor)

public:
	Item(const Vector2& _position);

public:
	virtual void Update(float delatTime);
	virtual const char* Serialize() override;
};