#pragma once

#include "Engine/Engine_Struct.h"
#include "Tile.h"
#include <vector>
#include <list>

using namespace std;

class Tile_Manager
{
	friend class Tile;
public:
	Tile_Manager();
	~Tile_Manager();

public:
	static Tile_Manager& Get() { return *instance; }
	void Draw();
	void Set_ShouldDraw(const Vector2& pos);
	TILE_TYPE Get_Tile_Type(const Vector2& pos);

private:
	static Tile_Manager* instance;

	vector<list<Tile*>> m_vAdjTile;
	vector<Tile*> m_vTile;

	int m_iSizeX = 0;
	int m_iSizeY = 0;
};