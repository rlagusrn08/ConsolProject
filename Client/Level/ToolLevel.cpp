#include "ToolLevel.h"
#include "Manager/Data_Manager.h"
#include "Tile/Tile_Manager.h"
#include "Actor/Ghost.h"
#include "Actor/Target.h"
#include "Actor/Item.h"

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
	if (ENGINE.GetKeyDown('1')) // 1 wall
	{
		Delete_Actor(DM.Get_Player_Position());

		TM.Insert_Tile(DM.Get_Player_Position());
	}
	if (ENGINE.GetKeyDown('2')) // 2 score
	{
		TM.Delete_Tile(DM.Get_Player_Position());
		Delete_Actor(DM.Get_Player_Position());

		actors.PushBack(new Target(DM.Get_Player_Position()));
	}
	if (ENGINE.GetKeyDown('3')) // 2 score
	{
		TM.Delete_Tile(DM.Get_Player_Position());
		Delete_Actor(DM.Get_Player_Position());

		actors.PushBack(new Item(DM.Get_Player_Position()));
	}
	if (ENGINE.GetKeyDown('4')) // 2 score
	{
		TM.Delete_Tile(DM.Get_Player_Position());
		Delete_Actor(DM.Get_Player_Position());

		actors.PushBack(new Ghost(DM.Get_Player_Position()));
	}

	if (ENGINE.GetKeyDown('S')) // save
	{
		TM.Save_Tile();
	}
	if (ENGINE.GetKeyDown('L')) // save
	{
		TM.Load_Tile("../Data/Tile.txt");
	}
	if (ENGINE.GetKeyDown(VK_DELETE)) // delete
	{
		TM.Delete_Tile(DM.Get_Player_Position());
		Delete_Actor(DM.Get_Player_Position());
	}
}

bool ToolLevel::Find_Actor(const Vector2& vPosition)
{
	for (auto iter : actors)
	{
		if (iter->As<Player>()) continue;
		if (vPosition.x == iter->Position().x && vPosition.y == iter->Position().y)
			return true;
	}

	return false;
}

void ToolLevel::Delete_Actor(const Vector2& vPosition)
{
	for (auto iter = actors.begin();
		iter != actors.end();
		iter++)
	{
		if ((*iter)->As<Player>()) continue;
		if (vPosition.x == (*iter)->Position().x && vPosition.y == (*iter)->Position().y)
		{
			(*iter)->Destroy();
			break;
		}
	}
}


void ToolLevel::Draw()
{
	Super::Draw();
	TM.Draw();
	DM.Draw();
}

