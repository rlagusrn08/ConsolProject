#include "Tile.h"
#include "Manager/Data_Manager.h"

Tile::Tile(const Vector2& _position)
{
	position = _position;
	color = Color::Blue;
}

void Tile::Draw()
{
	if (m_tInfo.eOption == TILE_WALL)
		Engine::Get().Draw(position, "w", color);

	if (m_tInfo.eOption == TILE_NORMAL && m_bDebugDraw)
	{
		m_bDebugDraw = false;
		if(position != DM.Get_Player_Position()) 
			Engine::Get().Draw(position, "X", Color::Green);
	}
	else if (m_tInfo.eOption == TILE_NORMAL && m_bDebugDraw)
	{
		Engine::Get().Draw(position, " ", color);
	}
}

const char* Tile::Serialize()
{
	char* buffer = new char[256];
	snprintf(buffer, 256, "%d %d\n", Position().x, Position().y);
	return buffer;
}

