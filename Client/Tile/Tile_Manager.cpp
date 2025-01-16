#include "PreCompiledHeader.h"
#include "Tile_Manager.h"
#include "Engine/Engine.h"


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

			pTile->Get_TileInfo().vPos = Vector2(j, i);
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

void Tile_Manager::Ready_Adj()
{
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

void Tile_Manager::Clear_Astar_List()
{
	m_OpenList.clear();
	m_CloseList.clear();
	m_BestList.clear();
}

void Tile_Manager::Start_Astar(const Vector2& vStart, const Vector2& vGoal)
{
	Clear_Astar_List();

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
		Make_BestList(m_iStartIndex, iGoalIndex);
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
	
	return true;
}

void Tile_Manager::Make_BestList(int iStartIndex, int iGoalIndex)
{
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
