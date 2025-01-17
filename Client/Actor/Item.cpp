#include "Item.h"

Item::Item(const Vector2& _position)
	: DrawableActor("O")
{
	this->position = _position;
	color = Color::White;
}

void Item::Update(float delatTime)
{
}
