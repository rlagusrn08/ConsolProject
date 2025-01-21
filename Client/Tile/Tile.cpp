#include "Tile.h"

Tile::Tile(const Vector2& _position)
{
	position = _position;
	color = Color::Blue;
}

void Tile::Draw()
{
	if (m_tInfo.eOption == 1)
		Engine::Get().Draw(position, "w", color);
}

const char* Tile::Serialize()
{
	char* buffer = new char[256];
	snprintf(buffer, 256, "%d %d\n", Position().x, Position().y);
	return buffer;
}

