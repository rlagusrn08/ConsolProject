#pragma once

#include "Level/GameLevel.h"
#include "Actor/Player.h"

class Tile_Manager;
class Level3 : public GameLevel
{
	// RTTI Àû¿ë.
	RTTI_DECLARATIONS(Level3, GameLevel)

public:
	Level3();
	~Level3();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
	Player* m_pPlayer = nullptr;
};