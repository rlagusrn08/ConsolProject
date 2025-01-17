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
	void Clear();
	void Set_ShouldDraw(const Vector2& pos);
	TILE_TYPE Get_Tile_Type(const Vector2& pos);
	int Get_Tile_Index(const Vector2& pos);
	int Get_Tile_SizeX() { return m_iSizeX; }
	int Get_Tile_SizeY() { return m_iSizeY; }
	
public:
	//For. Astar
	void Start_Astar(const Vector2& vStart, const Vector2& vGoal, list<Tile*>& OutputList);

public:
	//For. Tool
	void Insert_Tile(const Vector2& vPosition);
	bool Find_Tile(const Vector2& vPosition);
	void Delete_Tile(const Vector2& vPosition);
	void Save_Tile();
	void Load_Tile(const char* path);
private:
	void Ready_Adj();
	void Clear_Astar_List(list<Tile*>& OutputList);
	bool Make_Route(int iStartIndex, int iGoalIndex);
	void Make_BestList(int iStartIndex, int iGoalIndex, list<Tile*>& OutputList);
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