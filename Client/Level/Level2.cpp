#include "Level2.h"
#include "Engine/Engine.h"
#include "Define.h"
#include "Actor/Player.h"
#include <Windows.h>
#include "Tile/Tile_Manager.h"
#include "Actor/Ghost.h"
#include "Manager/Data_Manager.h"
#include "Actor/Item.h"
#include "Actor/Target.h"
#include "GameLevel.h"

Level2::Level2()
{
	DM.Set_Level(GAMELEVEL2);
	DM.Reset_Score();
	DM.Set_Ready(true);
	DM.Set_ItemActive(false);
	TM.Clear();
	TM.Load_Tile("../Data/Tile_Level2.txt");
	Load_Actor("../Data/Actor_Level2.txt");
}

Level2::~Level2()
{
	
}

void Level2::Update(float deltaTime)
{
	// 예외 처리.
	if (deltaTime > 1.0f)
	{
		return;
	}

	Super::Update(deltaTime);
	ProcessCollisionPlayerAndActor();
	Check_GameClear();
}

void Level2::Draw()
{
	Super::Draw();

	TM.Draw();
	DM.Draw();
}
