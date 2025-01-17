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
	if (position == DM.Get_Player_Position() && DM.Get_Mode() == GAME_MODE)
	{
		DM.Increase_Score(1);
		Destroy();
	}
}

void Target::Draw()
{
	Super::Draw();
}
