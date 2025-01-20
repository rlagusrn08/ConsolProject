#include "GameLevel.h"
#include "Actor/Actor.h"
#include "Actor/Player.h"
#include "Actor/Target.h"
#include "Actor/Ghost.h"
#include "Actor/Item.h"

#include "Manager/Data_Manager.h"
#include "Game/Game.h"

void GameLevel::Load_Actor(const char* path)
{
	// 파일 로드.
	FILE* file = nullptr;
	fopen_s(&file, path, "rb");

	if (file)
	{
		Clear_Actor();

		List<Actor*> Ghosts;
		char buffer[256];

		while (!feof(file))
		{
			fgets(buffer, 256, file);
			char szType = '\0';
			int iX = -1, iY = -1;
			sscanf_s(buffer, "%c %d %d", &szType, sizeof(char), &iX, &iY);

			if (szType == '\0' || iX == -1 || iY == -1) break;
			
			switch (szType)
			{
			case 'P':
			{
				m_pPlayer = new Player(Vector2(iX, iY));
				DM.Set_Player_Pointer(m_pPlayer);
				actors.PushBack(m_pPlayer);
				break;
			}
			case 'T':
				actors.PushBack(new Target(Vector2(iX, iY)));
				break;
			case 'I':
				actors.PushBack(new Item(Vector2(iX, iY)));
				break;
			case 'G':
				Ghosts.PushBack(new Ghost(Vector2(iX, iY)));
				break;
			}
		}
		for (auto iter : Ghosts)
		{
			actors.PushBack(iter);
		}
	}
}

void GameLevel::Clear_Actor()
{
	for (auto iter : actors)
	{
		iter->Destroy();
	}
}

void GameLevel::ProcessCollisionPlayerAndActor()
{
	for (auto iter : actors)
	{
		if (iter->As<Player>()) continue;

		if (iter->Position() == DM.Get_Player_Position())
		{
			m_pPlayer->Intersect(iter);
		}
	}
}

void GameLevel::Check_GameClear()
{
	for (auto iter : actors)
	{
		if (iter->As<Target>()) return;
	}
	Game::Get().Load_ClearMenu();
}
