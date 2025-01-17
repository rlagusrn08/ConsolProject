#pragma once

#include "Level/Level.h"
#include "Actor/Player.h"

class Tile_Manager;
class ToolLevel : public Level
{
	// RTTI ����.
	RTTI_DECLARATIONS(ToolLevel, Level)

public:
	ToolLevel();
	~ToolLevel();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	void Get_KeyDown();

private:
	Tile_Manager* m_pTile_Manager = nullptr;
	Player* m_pPlayer = nullptr;
};