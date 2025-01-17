#include "Target.h"

Target::Target(const Vector2& _position)
	: DrawableActor("*")
{
	this->position = _position;
	color = Color::White;
}

void Target::Update(float delatTime)
{
}

void Target::Draw()
{
	Super::Draw();
}
