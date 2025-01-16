#pragma once

#include "Level/Level.h"

class Tile_Manager;
class TestLevel : public Level
{
	// RTTI Àû¿ë.
	RTTI_DECLARATIONS(TestLevel, Level)

public:
	TestLevel();
	~TestLevel();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
	Tile_Manager* m_pTile_Manager = nullptr;
};