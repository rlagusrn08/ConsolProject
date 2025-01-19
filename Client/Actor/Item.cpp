#include "Item.h"
#include "Manager/Data_Manager.h"

Item::Item(const Vector2& _position)
	: DrawableActor("O")
{
	this->position = _position;
	color = Color::White;
}

void Item::Update(float delatTime)
{
	if (position == DM.Get_Player_Position() && DM.Get_Mode() == GAME_MODE)
	{
		DM.Increase_Score(1);
		Destroy();
	}
}

const char* Item::Serialize()
{
	char* buffer = new char[256];
	snprintf(buffer, 256, "I %d %d\n", Position().x, Position().y);
	return buffer;
}
