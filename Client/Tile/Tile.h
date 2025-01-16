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
		Vector2 vPos;

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
	TILEINFO& Get_TileInfo() { return m_tInfo; }

private:
	TILEINFO m_tInfo;
	bool m_bShouldDraw = true;
};
