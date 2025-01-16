#include "Ghost.h"
#include "Tile/Tile_Manager.h"

Ghost::Ghost(const Vector2& _position)
	: DrawableActor("¡Ü")
{
	this->position = _position;
	color = Color::Blue;
}

void Ghost::Update(float deltaTime)
{
	Super::Update(deltaTime);

}