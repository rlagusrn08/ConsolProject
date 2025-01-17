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

TestLevel::TestLevel()
{
	ENGINE.SetCursorType(CursorType::NoCursor);
	m_pPlayer = new Player(Vector2(5, 5));
	DM.Set_Player_Pointer(m_pPlayer);
	AddActor(m_pPlayer);
	actors.PushBack(new Target(Vector2(1, 1)));
	actors.PushBack(new Item(Vector2(3, 1)));
	actors.PushBack(new Target(Vector2(5, 1)));
	actors.PushBack(new Target(Vector2(7, 1)));

	
}

TestLevel::~TestLevel()
{
	TM.Clear();
}

void TestLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// 예외 처리.
	if (deltaTime > 1.0f)
	{
		return;
	}
}

void TestLevel::Draw()
{
	Super::Draw();

	TM.Draw();
	DM.Draw();
}
