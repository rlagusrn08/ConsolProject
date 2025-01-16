#pragma once

#include "Engine/Engine_Struct.h"
#include <vector>
#include <list>

using namespace std;

class ENGINE_API Tile_Manager
{
public:
	Tile_Manager();
	~Tile_Manager();

public:
	void Draw();
	TILE_TYPE Get_Tile_Type(const Vector2& pos);

private:
	static Tile_Manager* instance;

	vector<list<TILE*>> m_vAdjTile;
	vector<TILE*> m_vTile;

	int m_iSizeX = 0;
	int m_iSizeY = 0;
};