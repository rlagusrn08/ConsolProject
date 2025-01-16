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

			if (i == 0 || j == 0 || i == m_iSizeY - 1 || j == m_iSizeX - 1 || (i % 2 == 0 && j%2 == 0))
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
	m_vTile[temp]->Set_ShouldDraw();
}

TILE_TYPE Tile_Manager::Get_Tile_Type(const Vector2& pos)
{
	if (pos.y < 0 || pos.x < 0 || pos.y >= Engine::Get().ScreenSize().y || pos.y >= Engine::Get().ScreenSize().x) return TILE_END;
	int temp = pos.y * m_iSizeX + pos.x;
	return m_vTile[temp]->Get_TileInfo().eOption;
}
