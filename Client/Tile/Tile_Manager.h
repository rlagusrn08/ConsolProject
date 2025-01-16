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
	int Get_Tile_Index(const Vector2& pos);

public:
	//For. Astar
	void Ready_Adj();
	void Clear_Astar_List();
	void Start_Astar(const Vector2& vStart, const Vector2& vGoal);
	bool Make_Route(int iStartIndex, int iGoalIndex);
	void Make_BestList(int iStartIndex, int iGoalIndex);
	bool Check_Open(int iIndex);
	bool Check_Close(int iIndex);

private:
	static Tile_Manager* instance;

	vector<list<Tile*>> m_vAdjTile;
	vector<Tile*> m_vTile;

	int m_iSizeX = 0;
	int m_iSizeY = 0;

private:
	//For. Astar
	list<int> m_OpenList;
	list<int> m_CloseList;
	list<Tile*> m_BestList;

	int m_iStartIndex;
};