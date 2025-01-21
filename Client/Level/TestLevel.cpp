#include "TestLevel.h"
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

TestLevel::TestLevel()
{
	DM.Reset_Score();
	DM.Set_ItemActive(false);
	TM.Clear();
	TM.Load_Tile("../Data/Tile.txt");
	Load_Actor("../Data/Actor.txt");
}

TestLevel::~TestLevel()
{
	
}

void TestLevel::Update(float deltaTime)
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

void TestLevel::Draw()
{
	Super::Draw();

	TM.Draw();
	DM.Draw();
}
