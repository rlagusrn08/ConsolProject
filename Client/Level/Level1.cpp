#include "Level1.h"
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

Level1::Level1()
{
	DM.Set_Level(GAMELEVEL1);
	DM.Reset_Score();
	DM.Set_Ready(true);
	DM.Set_ItemActive(false);
	TM.Clear();
	TM.Load_Tile("../Data/Tile_Level1.txt");
	Load_Actor("../Data/Actor_Level1.txt");
}

Level1::~Level1()
{
}

void Level1::Update(float deltaTime)
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

void Level1::Draw()
{
	Super::Draw();

	TM.Draw();
	DM.Draw();
}
