#include <iostream>

#include "Engine/Engine.h"
#include "Level/TestLevel.h"
#include "Manager/Data_Manager.h"
#include "Game/Game.h"
#include "Level/MenuLevel.h"

Engine* engine = nullptr;

int main()
{
	CheckMemoryLeak();

	//Set Manager
	Data_Manager dm;

	Game game;
	game.LoadLevel(new TestLevel());
	game.Run();
 }