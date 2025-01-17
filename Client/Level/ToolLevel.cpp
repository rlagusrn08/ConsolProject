#include "ToolLevel.h"
#include "Manager/Data_Manager.h"
#include "Tile/Tile_Manager.h"

ToolLevel::ToolLevel()
{
	TM.Clear();
	m_pPlayer = new Player(Vector2(0, 0));
	DM.Set_Player_Pointer(m_pPlayer);
	actors.PushBack(m_pPlayer);
}

ToolLevel::~ToolLevel()
{
	TM.Clear();
}

void ToolLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	Get_KeyDown();
	// 예외 처리.
	if (deltaTime > 1.0f)
	{
		return;
	}
}

void ToolLevel::Get_KeyDown()
{
	if (ENGINE.GetKeyDown('1')) // 1
	{
		
	}
}


void ToolLevel::Draw()
{
	Super::Draw();
	TM.Draw();
	DM.Draw();
}

