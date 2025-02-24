#include "GameLevel.h"
#include "Actor/Actor.h"
#include "Actor/Player.h"
#include "Actor/Target.h"
#include "Actor/Ghost.h"
#include "Actor/Item.h"

#include "Manager/Data_Manager.h"
#include "Tile/Tile_Manager.h"
#include "Game/Game.h"

GameLevel::~GameLevel()
{
	//delete m_pQuadTree;
}

void GameLevel::Load_Actor(const char* path)
{
	// 파일 로드.
	FILE* file = nullptr;
	fopen_s(&file, path, "rb");

	if (file)
	{
		//m_pQuadTree = new QuadTree(Bounds(0, 0, TM.Get_Tile_SizeX(), TM.Get_Tile_SizeY()));

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
			
			Actor* pCurrentActor = nullptr;

			switch (szType)
			{
			case 'P':
			{
				m_pPlayer = new Player(Vector2(iX, iY));
				DM.Set_Player_Pointer(m_pPlayer);
				actors.PushBack(m_pPlayer);
				//m_pQuadTree->Insert(m_pPlayer->Get_QT_Node());
				break;
			}
			case 'T':
				pCurrentActor = new Target(Vector2(iX, iY));
				actors.PushBack(pCurrentActor);
				break;
			case 'I':
				pCurrentActor = new Item(Vector2(iX, iY));
				actors.PushBack(pCurrentActor);
				break;
			case 'G':
				pCurrentActor = new Ghost(Vector2(iX, iY));
				Ghosts.PushBack(pCurrentActor);
				break;
			}

			if (pCurrentActor != nullptr)
			{
				//m_pQuadTree->Insert(pCurrentActor->Get_QT_Node());
			}
		}
		for (auto iter : Ghosts)
		{
			actors.PushBack(iter);
		}

		fclose(file);
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
	//vector<Actor*> v = m_pQuadTree->Query(m_pPlayer->Get_QT_Node());
	//for (auto iter : v)
	//{
	//	if (iter->As<Player>()) continue;
	//
	//	iter->As<DrawableActor>()->Set_Color(Color::Green);
	//}

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
