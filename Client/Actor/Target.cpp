#include "Target.h"
#include "Manager/Data_Manager.h"
#include "QuadTree/QT_Node.h"

Target::Target(const Vector2& _position)
	: DrawableActor("*", new QT_Node(Bounds(_position.x - 0.5f, _position.y - 0.5f), this))
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
