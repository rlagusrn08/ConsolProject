#include "PreCompiledHeader.h"
#include "Tile_Manager.h"
#include "Engine/Engine.h"
#include <algorithm>
#include "Manager/Data_Manager.h"

// 스태틱 변수 초기화.
Tile_Manager* Tile_Manager::instance = nullptr;

Tile_Manager::Tile_Manager()
{
	instance = this;
	// temp
	m_iSizeX = 40;
	m_iSizeY = 20;

	int index = 0;
	for (int i = 0; i < m_iSizeY; i++)
	{
		for (int j = 0; j < m_iSizeX; j++)
		{
			Tile* pTile = new Tile(Vector2(j, i));

			if (i == 0 || j == 0 || i == m_iSizeY - 1 || j == m_iSizeX - 1 || (i % 2 == 0 && j % 2 == 0))
			{
				pTile->Get_TileInfo().eOption = TILE_WALL;
			}
			else
			{
				pTile->Get_TileInfo().eOption = TILE_NORMAL;
			}

			pTile->SetPosition(Vector2(j, i));
			pTile->Get_TileInfo().iIndex = index++;
			m_vTile.push_back(pTile);
		}
	}

	Ready_Adj();
}

Tile_Manager::~Tile_Manager()
{
	for (int i = 0; i < m_vTile.size();i++)
	{
		SafeDelete(m_vTile[i]);
	}
}

void Tile_Manager::Draw()
{
	for (int i = 0; i < m_vTile.size();i++)
	{
		m_vTile[i]->Draw();	
	}
}

void Tile_Manager::Clear()
{
	for (int i = 0; i < m_vTile.size();i++)
	{
		SafeDelete(m_vTile[i]);
	}
	m_vTile.clear();
	m_vTile.shrink_to_fit();
}

void Tile_Manager::Set_ShouldDraw(const Vector2& pos)
{
	if (pos.y < 0 || pos.x < 0 || pos.y >= Engine::Get().ScreenSize().y || pos.y >= Engine::Get().ScreenSize().x) return;
	int temp = pos.y * m_iSizeX + pos.x;
	m_vTile[Get_Tile_Index(pos)]->Set_ShouldDraw();
}

TILE_TYPE Tile_Manager::Get_Tile_Type(const Vector2& pos)
{
	if (pos.y < 0 || pos.x < 0 || pos.y >= Engine::Get().ScreenSize().y || pos.y >= Engine::Get().ScreenSize().x) return TILE_END;
	return m_vTile[Get_Tile_Index(pos)]->Get_TileInfo().eOption;
}

int Tile_Manager::Get_Tile_Index(const Vector2& pos)
{
	return pos.y * m_iSizeX + pos.x;
}

void Tile_Manager::Insert_Tile(const Vector2& vPosition)
{
	if (DM.Get_Mode() != TOOL_MODE) return;
	if (Find_Tile(vPosition)) return;

	Tile* pTile = new Tile(Vector2(vPosition.x, vPosition.y));
	pTile->Get_TileInfo().eOption = TILE_WALL;
	m_vTile.push_back(pTile);
}

bool Tile_Manager::Find_Tile(const Vector2& vPosition)
{
	if (DM.Get_Mode() != TOOL_MODE) return false;

	for (auto iter : m_vTile)
	{
		if(vPosition.x == iter->Position().x && vPosition.y == iter->Position().y)
			return true;
	}

	return false;
}

void Tile_Manager::Delete_Tile(const Vector2& vPosition)
{
	for (auto iter = m_vTile.begin();
		iter != m_vTile.end();
		iter++)
	{
		if (vPosition.x == (*iter)->Position().x && vPosition.y == (*iter)->Position().y)
		{
			SafeDelete((*iter));
			m_vTile.erase(iter);
			break;
		}
	}
}

void Tile_Manager::Save_Tile()
{
	int maxX = 0, maxY = 0;
	for (auto iter : m_vTile)
	{
		if (iter->Get_TileInfo().eOption == 0) continue;
		if (maxX < iter->Position().x) maxX = iter->Position().x;
		if (maxY < iter->Position().y) maxY = iter->Position().y;
	}

	char buffer[1000001];
	memset(buffer, 0, 1000001);


	char* Point = new char[256];
	snprintf(Point, 256, "%d %d\n", maxX, maxY);
	strcat_s(buffer, Point);
	delete[] Point;

	for (auto iter : m_vTile)
	{
		if (iter->Get_TileInfo().eOption == 0) continue;
		const char* data = iter->Serialize();
		strcat_s(buffer, data);
		delete data;
	}

	// 파일 저장.
	FILE* file = nullptr;
	fopen_s(&file, "../Data/Tile.txt", "wb");
	if (file)
	{
		fwrite(buffer, strlen(buffer) + 1, 1, file);
		fclose(file);
	}
}

void Tile_Manager::Load_Tile(const char* path)
{
	// 파일 로드.
	FILE* file = nullptr;
	fopen_s(&file, path, "rb");

	if (file)
	{
		Clear();
		char buffer[256];
		
		fgets(buffer, 256, file);

	
		sscanf_s(buffer, "%d %d", &m_iSizeX, &m_iSizeY);

		m_iSizeX++;
		m_iSizeY++;

		int index = 0;
		for (int i = 0; i < m_iSizeY; i++)
		{
			for (int j = 0; j < m_iSizeX; j++)
			{
				Tile* pTile = new Tile(Vector2(j, i));
				pTile->Get_TileInfo().iIndex = index++;
				pTile->Get_TileInfo().eOption = TILE_NORMAL;
				m_vTile.push_back(pTile);
			}
		}

		while (!feof(file))
		{
			fgets(buffer, 256, file);
			int iX = -1, iY = -1;
			sscanf_s(buffer, "%d %d", &iX, &iY);

			if (iX == -1 || iY == -1) break;
			m_vTile[Get_Tile_Index(Vector2(iX, iY))]->Set_Type(TILE_TYPE::TILE_WALL);
		}
		Ready_Adj();
		// 파일 닫기.
		fclose(file);
	}
}

void Tile_Manager::Ready_Adj()
{
	m_vAdjTile.clear();
	m_vAdjTile.shrink_to_fit();
	m_vAdjTile.resize(m_vTile.size());

	for (int i = 0; i < m_iSizeY; i++)
	{
		for (int j = 0; j < m_iSizeX; j++)
		{
			int iIndex = i * m_iSizeX + j;

			if (i > 0)
			{
				if (!m_vTile[iIndex - m_iSizeX]->Get_TileInfo().eOption)
					m_vAdjTile[iIndex].push_back(m_vTile[iIndex - m_iSizeX]);
			}

			if (j > 0)
			{
				if (!m_vTile[iIndex - 1]->Get_TileInfo().eOption)
					m_vAdjTile[iIndex].push_back(m_vTile[iIndex - 1]);
			}

			if (j < m_iSizeX - 1)
			{
				if (!m_vTile[iIndex + 1]->Get_TileInfo().eOption)
					m_vAdjTile[iIndex].push_back(m_vTile[iIndex + 1]);
			}

			if (i < m_iSizeY - 1)
			{
				if (!m_vTile[iIndex + m_iSizeX]->Get_TileInfo().eOption)
					m_vAdjTile[iIndex].push_back(m_vTile[iIndex + m_iSizeX]);
			}
		}
	}
}

void Tile_Manager::Clear_Astar_List(list<Tile*>& OutputList)
{
	m_OpenList.clear();
	m_CloseList.clear();
	m_BestList.clear();
	OutputList.clear();
}

void Tile_Manager::Start_Astar(const Vector2& vStart, const Vector2& vGoal, list<Tile*>& OutputList)
{
	Clear_Astar_List(OutputList);

	if (m_vTile.empty()) return;

	m_iStartIndex = Get_Tile_Index(vStart);
	int iGoalIndex = Get_Tile_Index(vGoal);

	if (m_iStartIndex < 0 || (size_t)m_iStartIndex >= m_vTile.size() ||
		iGoalIndex < 0 || (size_t)iGoalIndex >= m_vTile.size())
		return;
	if (m_iStartIndex == iGoalIndex)
		return;
	if (m_vTile[iGoalIndex]->Get_TileInfo().eOption == 1)
		return;

	if (Make_Route(m_iStartIndex, iGoalIndex))
	{
		Make_BestList(m_iStartIndex, iGoalIndex, OutputList);
		//TODO : Delete This
		for (auto iter : m_BestList)
		{
			iter->Set_DebugDraw();
		}
	}
}

bool Tile_Manager::Make_Route(int iStartIndex, int iGoalIndex)
{
	if (!m_OpenList.empty())
	{
		m_OpenList.pop_front();
	}

	m_CloseList.push_back(iStartIndex);

	for (auto iter : m_vAdjTile[iStartIndex])
	{
		if (iGoalIndex == iter->Get_TileInfo().iIndex)
		{
			iter->Get_TileInfo().iParentIndex = iStartIndex;
			return true;
		}
		
		if (Check_Open(iter->Get_TileInfo().iIndex) == false &&
			Check_Close(iter->Get_TileInfo().iIndex) == false)
		{
			iter->Get_TileInfo().iParentIndex = iStartIndex;
			m_OpenList.push_back(iter->Get_TileInfo().iIndex);
		}
	}

	if (m_OpenList.empty())
		return false;

	int iOriginStart = iStartIndex;

	m_OpenList.sort([&](int iDst, int iSrc)
		{
			Vector2 vPCost1 = m_vTile[iOriginStart]->Position() - m_vTile[iDst]->Position();
			Vector2 vPCost2 = m_vTile[iOriginStart]->Position() - m_vTile[iSrc]->Position();

			Vector2 vGCost1 = m_vTile[iGoalIndex]->Position() - m_vTile[iDst]->Position();
			Vector2 vGCost2 = m_vTile[iGoalIndex]->Position() - m_vTile[iSrc]->Position();

			float fCost1 = vPCost1.Length() + vGCost1.Length();
			float fCost2 = vPCost2.Length() + vGCost2.Length();

			return fCost1 < fCost2;
		});

	return Make_Route(m_OpenList.front(), iGoalIndex);
}

void Tile_Manager::Make_BestList(int iStartIndex, int iGoalIndex, list<Tile*>& OutputList)
{
	OutputList.push_back(m_vTile[iGoalIndex]);
	m_BestList.push_front(m_vTile[iGoalIndex]);

	int iRouteIndex = m_vTile[iGoalIndex]->Get_TileInfo().iParentIndex;

	while (true)
	{
		if (iRouteIndex == iStartIndex)
			break;

		m_BestList.push_front(m_vTile[iRouteIndex]);
		OutputList.push_front(m_vTile[iRouteIndex]);
		iRouteIndex = m_vTile[iRouteIndex]->Get_TileInfo().iParentIndex;
	}
}

bool Tile_Manager::Check_Open(int iIndex)
{
	for (int iOpenIndex : m_OpenList)
	{
		if (iIndex == iOpenIndex)
			return true;
	}
	return false;
}

bool Tile_Manager::Check_Close(int iIndex)
{
	for (int iCloseIndex : m_CloseList)
	{
		if (iIndex == iCloseIndex)
			return true;
	}

	return false;
}
