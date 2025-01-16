#include "Player.h"
#include "Include.h"
#include "Tile/Tile_Manager.h"



Player::Player(const Vector2& _position)
	: DrawableActor("C")
{
	this->position = _position;
	color = Color::White;
}

void Player::Update(float deltaTime)
{
	Super::Update(deltaTime);

	Get_KeyDown();
	Move(deltaTime);

}

void Player::Get_KeyDown()
{
	Vector2 newPosition;
	if (ENGINE.GetKeyDown(VK_LEFT))
	{
		newPosition = Vector2(Position().x - 1, Position().y);
		if (TM.Get_Tile_Type(newPosition) == TILE_NORMAL)
		{
			m_eDir = MOVE_LEFT;
			m_fCurrentSpeed = m_fSpeedX;
			Change_Image("⊃");
		}
	}
	else if (ENGINE.GetKeyDown(VK_RIGHT))
	{
		newPosition = Vector2(Position().x + 1, Position().y);
		if (TM.Get_Tile_Type(newPosition) == TILE_NORMAL)
		{
			m_eDir = MOVE_RIGHT;
			m_fCurrentSpeed = m_fSpeedX;
			Change_Image("⊂");
		}
	}
	else if (ENGINE.GetKeyDown(VK_UP))
	{
		newPosition = Vector2(Position().x, Position().y - 1);
		if (TM.Get_Tile_Type(newPosition) == TILE_NORMAL)
		{
			m_eDir = MOVE_UP;
			m_fCurrentSpeed = m_fSpeedY;
			Change_Image("∪");
		}
	}
	else if (ENGINE.GetKeyDown(VK_DOWN))
	{
		newPosition = Vector2(Position().x, Position().y + 1);
		if (TM.Get_Tile_Type(newPosition) == TILE_NORMAL)
		{
			m_eDir = MOVE_DOWN;
			m_fCurrentSpeed = m_fSpeedY;
			Change_Image("∩");
		}
	}

	// TODO : Delete
	if (ENGINE.GetKeyDown(VK_SPACE))
	{
		TM.Start_Astar(Vector2(1, 1), Position());
	}
}

void Player::Move(float deltaTime)
{
	if (m_eDir == MOVE_NONE) return;

	
	m_fMovement += deltaTime * m_fCurrentSpeed;
	if (m_fMovement >= 1.f)
	{
		m_fMovement -= 1.f;
		Vector2 newPosition;
		if (m_eDir == MOVE_LEFT)
		{
			newPosition = Vector2(Position().x - 1, Position().y);
		}
		else if (m_eDir == MOVE_RIGHT)
		{
			newPosition = Vector2(Position().x + 1, Position().y);
		}
		else if (m_eDir == MOVE_UP)
		{
			newPosition = Vector2(Position().x, Position().y - 1);
		}
		else if (m_eDir == MOVE_DOWN)
		{
			newPosition = Vector2(Position().x, Position().y + 1);
		}

		if (TM.Get_Tile_Type(newPosition) == TILE_NORMAL)
		{
			TM.Set_ShouldDraw(Position());
			SetPosition(newPosition);
		}
	}

}
