#pragma once

#include <Engine/Engine.h>

class Game : public Engine
{
public:
	Game();
	~Game();

	void ToggleMenu();
	void Load_MainMenu();
	void Load_ToolLevel();
	void Load_Level1();
	void Load_GameOverMenu();
	void Load_ClearMenu();

	static Game& Get() { return *instance; }

private:
	bool showMenu = false;

	Level* menuLevel = nullptr;
	Level* backLevel = nullptr;

private:
	static Game* instance;
};