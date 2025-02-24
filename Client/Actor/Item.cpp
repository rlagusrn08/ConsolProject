#include "Item.h"
#include "Manager/Data_Manager.h"
#include "QuadTree/QT_Node.h"

Item::Item(const Vector2& _position)
	: DrawableActor("O", new QT_Node(Bounds(_position.x - 0.5f, _position.y - 0.5f), this))
{
	this->position = _position;
	color = Color::White;
}

void Item::Update(float delatTime)
{
	
}

const char* Item::Serialize()
{
	char* buffer = new char[256];
	snprintf(buffer, 256, "I %d %d\n", Position().x, Position().y);
	return buffer;
}
