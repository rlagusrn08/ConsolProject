﻿#include "Player.h"
#include "Include.h"
#include "Tile/Tile_Manager.h"
#include "Manager/Data_Manager.h"
#include "Game/Game.h"

Player::Player(const Vector2& _position)
	: DrawableActor("O")
{
	this->position = _position;
	color = Color::Yellow;
}

void Player::Update(float deltaTime)
{
	Super::Update(deltaTime);

	Get_KeyDown();
	Move(deltaTime);

}

void Player::Get_KeyDown()
{
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		//Engine::Get().QuitGame();
		// 메뉴 토글.
		Game::Get().ToggleMenu();
	}

	Vector2 newPosition;
	if (ENGINE.GetKeyDown(VK_LEFT))
	{
		newPosition = Vector2(Position().x - 1, Position().y);
		if (TM.Get_Tile_Type(newPosition) == TILE_NORMAL)
		{
			m_eDir = MOVE_LEFT;
			m_fCurrentSpeed = m_fSpeedX;
			Change_Image("L");
		}
	}
	else if (ENGINE.GetKeyDown(VK_RIGHT))
	{
		newPosition = Vector2(Position().x + 1, Position().y);
		if (TM.Get_Tile_Type(newPosition) == TILE_NORMAL)
		{
			m_eDir = MOVE_RIGHT;
			m_fCurrentSpeed = m_fSpeedX;
			Change_Image("R");
		}
	}
	else if (ENGINE.GetKeyDown(VK_UP))
	{
		newPosition = Vector2(Position().x, Position().y - 1);
		if (TM.Get_Tile_Type(newPosition) == TILE_NORMAL)
		{
			m_eDir = MOVE_UP;
			m_fCurrentSpeed = m_fSpeedY;
			Change_Image("U");
		}
	}
	else if (ENGINE.GetKeyDown(VK_DOWN))
	{
		newPosition = Vector2(Position().x, Position().y + 1);
		if (TM.Get_Tile_Type(newPosition) == TILE_NORMAL)
		{
			m_eDir = MOVE_DOWN;
			m_fCurrentSpeed = m_fSpeedY;
			Change_Image("D");
		}
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
			DM.Set_Detect_Player_Move(true);
			SetPosition(newPosition);
		}
	}
	else
	{
		DM.Set_Detect_Player_Move(false);
	}

}
