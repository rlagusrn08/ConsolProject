#include "Tile.h"

Tile::Tile(const Vector2& _position)
{
	position = _position;
}

void Tile::Draw()
{
	if (m_tInfo.eOption == 1)
		Engine::Get().Draw(position, "w", color);
}

