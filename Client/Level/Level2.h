#pragma once

#include "Level/GameLevel.h"
#include "Actor/Player.h"

class Tile_Manager;
class Level2 : public GameLevel
{
	// RTTI Àû¿ë.
	RTTI_DECLARATIONS(Level2, GameLevel)

public:
	Level2();
	~Level2();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
	Player* m_pPlayer = nullptr;
};