#include "Ghost.h"
#include "Tile/Tile_Manager.h"
#include "Manager/Data_Manager.h"

Ghost::Ghost(const Vector2& _position)
	: DrawableActor("G")
{
	this->position = _position;
	color = Color::Blue;
}

void Ghost::Update(float deltaTime)
{
	Super::Update(deltaTime);
	Make_Route();
	Move(deltaTime);
}

const char* Ghost::Serialize()
{
	char* buffer = new char[256];
	snprintf(buffer, 256, "G %d %d\n", Position().x, Position().y);
	return buffer;
}

void Ghost::Make_Route()
{
	if (DM.Get_Mode() != GAME_MODE) return;

	if (DM.Get_Detect_Player_Move())
	{
		TM.Start_Astar(position, DM.Get_Player_Position(), m_BestRoute);
	}
}

void Ghost::Move(float deltaTime)
{
	if (DM.Get_Mode() != GAME_MODE) return;

	if (!m_BestRoute.empty())
	{
		Vector2 VTemp = position - m_BestRoute.front()->Position();

		if (VTemp.x == 1 || VTemp.x == -1)
		{
			m_fCurrentSpeed = m_fSpeedX;
		}
		else
		{
			m_fCurrentSpeed = m_fSpeedY;
		}
	}

	m_fMovement += deltaTime * m_fCurrentSpeed;
	if (m_fMovement >= 1.f)
	{
		m_fMovement -= 1.f;
		
		if (!m_BestRoute.empty())
		{
			TM.Set_ShouldDraw(Position());
			SetPosition(m_BestRoute.front()->Position());
			m_BestRoute.pop_front();
		}
	}
}
