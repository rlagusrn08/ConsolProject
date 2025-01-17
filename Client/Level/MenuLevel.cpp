#include "MenuLevel.h"
#include "Game/Game.h"
#include <Define.h>

MenuLevel::MenuLevel()
{
	menuItems.PushBack(new MenuItem("Resume Game", []() { Game::Get().ToggleMenu(); }));
	menuItems.PushBack(new MenuItem("Quit Game", []() { Game::Get().QuitGame(); }));
	length = menuItems.Size();
}

MenuLevel::~MenuLevel()
{
	for (auto* item : menuItems)
	{
		delete item;
	}
}

void MenuLevel::Update(float deltaTime)
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

void MenuLevel::Draw()
{
	Super::Draw();

	ENGINE.Draw(Vector2(0, 0), "Pacman", unselectedColor);

	for (int ix = 0; ix < length; ++ix)
	{
		ENGINE.Draw(Vector2(0, ix + 2), menuItems[ix]->menuText, ix == currentIndex ? selectedColor : unselectedColor);
	}
}