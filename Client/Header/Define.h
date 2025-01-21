#pragma once

using namespace std;

enum GAMELEVEL {
	GAMELEVEL1,
	GAMELEVEL2,
	GAMELEVEL3,
	GAMELEVEL_END,
};

#define ENGINE Engine::Get()
#define TM Tile_Manager::Get()
#define DM Data_Manager::Get()