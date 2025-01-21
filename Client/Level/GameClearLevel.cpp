#include "GameClearLevel.h"
#include "Game/Game.h"
#include <Define.h>
#include "Manager/Data_Manager.h"

GameClearLevel::GameClearLevel()
{
	if (DM.Get_Level() != GAMELEVEL_END)
	{
		menuItems.PushBack(new MenuItem("Next Level", []() {
			switch (DM.Get_Level())
			{
			case GAMELEVEL2:
				Game::Get().Load_Level2();
				break;
			case GAMELEVEL3:
				Game::Get().Load_Level3();
				break;
			}
			}));
	}
	menuItems.PushBack(new MenuItem("MainMenu", []() { Game::Get().Load_MainMenu(); }));
	menuItems.PushBack(new MenuItem("Quit Game", []() { Game::Get().QuitGame(); }));
	length = menuItems.Size();
}

GameClearLevel::~GameClearLevel()
{
	for (auto* item : menuItems)
	{
		delete item;
	}
}

void GameClearLevel::Update(float deltaTime)
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

void GameClearLevel::Draw()
{
	Super::Draw();

	ENGINE.Draw(Vector2(0, 0), "GameClear!!", unselectedColor);

	for (int ix = 0; ix < length; ++ix)
	{
		ENGINE.Draw(Vector2(0, ix + 2), menuItems[ix]->menuText, ix == currentIndex ? selectedColor : unselectedColor);
	}
}
