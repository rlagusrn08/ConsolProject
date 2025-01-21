#include "Level3.h"
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

Level3::Level3()
{
	DM.Set_Level(GAMELEVEL3);
	DM.Reset_Score();
	DM.Set_Ready(true);
	DM.Set_ItemActive(false);
	TM.Clear();
	TM.Load_Tile("../Data/Tile_Level3.txt");
	Load_Actor("../Data/Actor_Level3.txt");
}

Level3::~Level3()
{
	
}

void Level3::Update(float deltaTime)
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

void Level3::Draw()
{
	Super::Draw();

	TM.Draw();
	DM.Draw();
}
