#include "TestLevel.h"
#include "Engine/Engine.h"
#include "Define.h"
#include "Actor/Player.h"
#include <Windows.h>
#include "Tile/Tile_Manager.h"
#include "Actor/Ghost.h"

TestLevel::TestLevel()
{
	ENGINE.SetCursorType(CursorType::NoCursor);
	m_pPlayer = new Player(Vector2(5, 5));
	AddActor(m_pPlayer);
	actors.PushBack(new Ghost(Vector2(1, 1)));
	m_pTile_Manager = new Tile_Manager();
}

TestLevel::~TestLevel()
{
	delete m_pTile_Manager;
}

void TestLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// 예외 처리.
	if (deltaTime > 1.0f)
	{
		return;
	}

	// ESC 키로 종료.
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
	}
}

void TestLevel::Draw()
{
	Super::Draw();

	TM.Draw();
}
