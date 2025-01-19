#pragma once
#include "Include.h"
#include "Actor/DrawableActor.h"

enum TILE_TYPE
{
	TILE_NORMAL,
	TILE_WALL,
	TILE_END,
};

class Tile : public DrawableActor
{
public:
	typedef struct tagTile
	{
		int iIndex;
		int iParentIndex;
		TILE_TYPE eOption;
	}TILEINFO;

	RTTI_DECLARATIONS(Tile, DrawableActor)

public:
	Tile(const Vector2& _position);

public:
	virtual void Draw() override;
	void Set_ShouldDraw() { m_bShouldDraw = true; };
	void Set_DebugDraw() { m_bShouldDraw = true; m_bDebugDraw = true; }
	void Set_Type(TILE_TYPE _eType) { m_tInfo.eOption = _eType; }
	TILEINFO& Get_TileInfo() { return m_tInfo; }
	virtual const char* Serialize() override;

private:
	TILEINFO m_tInfo;
	bool m_bShouldDraw = true;

	//Todo : Delete
	bool m_bDebugDraw = false;
};
