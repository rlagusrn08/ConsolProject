#include "Player.h"
#include "Include.h"
#include "Tile/Tile_Manager.h"
#include "Manager/Data_Manager.h"
#include "Game/Game.h"
#include "Item.h"
#include "Ghost.h"
#include "Target.h"
#include "Game/Game.h"

Player::Player(const Vector2& _position)
	: DrawableActor("C")
{
	this->position = _position;
	color = Color::Yellow;

	m_tItemDurationTime.DurationTime = 8.f;
	m_tItemDurationTime.AccDurationTime = 0.f;
}

void Player::Update(float deltaTime)
{
	Super::Update(deltaTime);

	Check_Active_Item(deltaTime);
	Get_KeyDown();
	Game_Move(deltaTime);
	Tool_Move(deltaTime);
}

void Player::Get_KeyDown()
{
	if (DM.Get_Mode() != MODE::GAME_MODE) return;
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

void Player::Game_Move(float deltaTime)
{
	if (m_eDir == MOVE_NONE || DM.Get_Mode() != MODE::GAME_MODE) return;

	
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
			DM.Set_Detect_Player_Move(true);
			SetPosition(newPosition);
		}
	}
	else
	{
		DM.Set_Detect_Player_Move(false);
	}

}

void Player::Tool_Move(float deltaTime)
{
	if (DM.Get_Mode() != MODE::TOOL_MODE) return;

	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		//Engine::Get().QuitGame();
		// 메뉴 토글.
		Game::Get().ToggleMenu();
	}

	if (ENGINE.GetKeyDown(VK_LEFT) && position.x > 0)
	{
		position = Vector2(Position().x - 1, Position().y);
	}
	else if (ENGINE.GetKeyDown(VK_RIGHT) && position.x < ENGINE.ScreenSize().x-1)
	{
		position = Vector2(Position().x + 1, Position().y);
	}
	else if (ENGINE.GetKeyDown(VK_UP) && position.y > 0)
	{
		position = Vector2(Position().x, Position().y - 1);
	}
	else if (ENGINE.GetKeyDown(VK_DOWN) && position.y < ENGINE.ScreenSize().y-2)
	{
		position = Vector2(Position().x, Position().y + 1);
	}
	SetPosition(position);
}

void Player::Check_Active_Item(float deltaTime)
{
	if (DM.Get_ItemActive())
	{
		m_tItemDurationTime.AccDurationTime += deltaTime;
		if (m_tItemDurationTime.AccDurationTime >= m_tItemDurationTime.DurationTime)
		{
			DM.Set_ItemActive(false);
		}
	}
}

void Player::Intersect(Actor* other)
{
	if (other->As<Item>())
	{
		DM.Set_ItemActive(true);
		other->Destroy();
		m_tItemDurationTime.AccDurationTime = 0.f;
		return;
	}

	if (other->As<Target>())
	{
		other->Destroy();
		DM.Increase_Score(1);
		return;
	}

	if (other->As<Ghost>())
	{
		if (DM.Get_ItemActive())
		{
			other->Destroy();
			DM.Increase_Score(100);
		}
		else
		{
			Game::Get().Load_GameOverMenu();
		}
	}
}

const char* Player::Serialize()
{
	char* buffer = new char[256];
	snprintf(buffer, 256, "P %d %d\n", Position().x, Position().y);
	return buffer;
}
