#include "Game.h"

#include "Level/MenuLevel.h"
#include "Manager/Data_Manager.h"
#include "Level/TestLevel.h"
#include "Level/MainMenuLevel.h"
#include "Level/ToolLevel.h"
#include "Level/GameOverLevel.h"
#include "Level/GameClearLevel.h"

Game* Game::instance = nullptr;

Game::Game()
	: Engine()
{
	instance = this;

	menuLevel = new MenuLevel();
}

Game::~Game()
{
	if (showMenu)
	{
		delete backLevel;
		backLevel = nullptr;
		mainLevel = nullptr;
	}
	else
	{
		delete mainLevel;
		mainLevel = nullptr;
	}

	delete menuLevel;
	menuLevel = nullptr;
}

void Game::ToggleMenu()
{
	system("cls");
	//Clear();
	showMenu = !showMenu;
	if (showMenu)
	{
		backLevel = mainLevel;
		mainLevel = menuLevel;
	}
	else
	{
		mainLevel = backLevel;
	}
}

void Game::Load_MainMenu()
{
	DM.Set_Mode(MODE::MENU_MODE);
	if (showMenu)
	{
		showMenu = false;
		mainLevel = backLevel;
	}

	ENGINE.ChangeLevel(new MainMenuLevel());
}

void Game::Load_ToolLevel()
{
	DM.Set_Mode(MODE::TOOL_MODE);
	ENGINE.ChangeLevel(new ToolLevel());
}

void Game::Load_Level1()
{
	DM.Set_Mode(MODE::GAME_MODE);
	ENGINE.ChangeLevel(new TestLevel());
}

void Game::Load_GameOverMenu()
{
	DM.Set_Mode(MODE::MENU_MODE);
	ENGINE.ChangeLevel(new GameOverLevel());
}

void Game::Load_ClearMenu()
{
	DM.Set_Mode(MODE::MENU_MODE);
	ENGINE.ChangeLevel(new GameClearLevel());
}
