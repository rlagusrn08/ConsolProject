#include <iostream>

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#include "Engine/Engine.h"
#include "Manager/Data_Manager.h"
#include "Tile/Tile_Manager.h"
#include "Game/Game.h"
#include "Level/MainMenuLevel.h"

Engine* engine = nullptr;

int main()
{
	CheckMemoryLeak();
	srand((unsigned)time(NULL));

	//Set Manager
	Data_Manager dm;
	Tile_Manager tm;

	Game game;
	game.LoadLevel(new MainMenuLevel());
	game.Run();
 }