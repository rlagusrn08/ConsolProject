#include "Target.h"
#include "Manager/Data_Manager.h"

Target::Target(const Vector2& _position)
	: DrawableActor("*")
{
	this->position = _position;
	color = Color::White;
}

void Target::Update(float delatTime)
{
	Super::Update(delatTime);
}

void Target::Draw()
{
	Super::Draw();
}

const char* Target::Serialize()
{
	char* buffer = new char[256];
	snprintf(buffer, 256, "T %d %d\n", Position().x, Position().y);
	return buffer;
}
