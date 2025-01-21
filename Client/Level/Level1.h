#pragma once

#include "Level/GameLevel.h"
#include "Actor/Player.h"

class Tile_Manager;
class Level1 : public GameLevel
{
	// RTTI Àû¿ë.
	RTTI_DECLARATIONS(Level1, GameLevel)

public:
	Level1();
	~Level1();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
	Player* m_pPlayer = nullptr;
};