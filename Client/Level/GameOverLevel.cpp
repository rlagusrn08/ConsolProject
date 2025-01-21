#include "GameOverLevel.h"
#include "Game/Game.h"
#include <Define.h>
#include "Manager/Data_Manager.h"

GameOverLevel::GameOverLevel()
{
	menuItems.PushBack(new MenuItem("Restart", []() {
		switch (DM.Get_Level())
		{
		case GAMELEVEL1:
			Game::Get().Load_Level1();
			break;
		case GAMELEVEL2:
			Game::Get().Load_Level2();
			break;
		case GAMELEVEL3:
			Game::Get().Load_Level3();
			break;
		}
		}));
	menuItems.PushBack(new MenuItem("MainMenu", []() { Game::Get().Load_MainMenu(); }));
	menuItems.PushBack(new MenuItem("Quit Game", []() { Game::Get().QuitGame(); }));
	length = menuItems.Size();
}

GameOverLevel::~GameOverLevel()
{
	for (auto* item : menuItems)
	{
		delete item;
	}
}

void GameOverLevel::Update(float deltaTime)
{
	if (Game::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().ToggleMenu();
	}

	if (Game::Get().GetKeyDown(VK_UP))
	{
		currentIndex = (currentIndex - 1 + length) % length;
	}
	if (Game::Get().GetKeyDown(VK_DOWN))
	{
		currentIndex = (currentIndex + 1) % length;
	}

	if (Game::Get().GetKeyDown(VK_RETURN))
	{
		menuItems[currentIndex]->onSelected();
	}
}

void GameOverLevel::Draw()
{
	Super::Draw();

	ENGINE.Draw(Vector2(0, 0), "GameOver", unselectedColor);

	for (int ix = 0; ix < length; ++ix)
	{
		ENGINE.Draw(Vector2(0, ix + 2), menuItems[ix]->menuText, ix == currentIndex ? selectedColor : unselectedColor);
	}
}
