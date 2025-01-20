#pragma once

#include "Level/GameLevel.h"
#include "Actor/Player.h"

class Tile_Manager;
class TestLevel : public GameLevel
{
	// RTTI Àû¿ë.
	RTTI_DECLARATIONS(TestLevel, GameLevel)

public:
	TestLevel();
	~TestLevel();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
	Player* m_pPlayer = nullptr;
};