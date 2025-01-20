#include "GameLevel.h"
#include "Actor/Actor.h"
#include "Actor/Player.h"
#include "Actor/Target.h"
#include "Actor/Ghost.h"
#include "Actor/Item.h"

#include "Manager/Data_Manager.h"
#include "Actor/Item.h"

void GameLevel::Load_Actor(const char* path)
{
	// 파일 로드.
	FILE* file = nullptr;
	fopen_s(&file, path, "rb");

	if (file)
	{
		Clear_Actor();

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
				actors.PushBack(new Ghost(Vector2(iX, iY)));
				break;
			}
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

void GameLevel::ProcessCollisionPlayerAndItem()
{
	for (auto iter : actors)
	{
		Item* item = iter->As<Item>();
		if (item && item->Position() == DM.Get_Player_Position())
		{
			item->Destroy();
			m_pPlayer->Intersect(item);
		}
	}
}
