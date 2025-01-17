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
