#include "MainMenuLevel.h"
#include "Game/Game.h"
#include <Define.h>

MainMenuLevel::MainMenuLevel()
{
	menuItems.PushBack(new MenuItem("Start Game", []() { Game::Get().Load_Level1(); }));
	menuItems.PushBack(new MenuItem("Tool Mode", []() { Game::Get().Load_ToolLevel(); }));
	menuItems.PushBack(new MenuItem("Quit Game", []() { Game::Get().QuitGame(); }));
	length = menuItems.Size();
}

MainMenuLevel::~MainMenuLevel()
{
	for (auto* item : menuItems)
	{
		delete item;
	}
}

void MainMenuLevel::Update(float deltaTime)
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

void MainMenuLevel::Draw()
{
	Super::Draw();

	ENGINE.Draw(Vector2(0, 0), "Pacman", unselectedColor);

	for (int ix = 0; ix < length; ++ix)
	{
		ENGINE.Draw(Vector2(0, ix + 2), menuItems[ix]->menuText, ix == currentIndex ? selectedColor : unselectedColor);
	}
}