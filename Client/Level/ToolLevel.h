#pragma once

#include "Level/GameLevel.h"
#include "Actor/Player.h"

class Tile_Manager;
class ToolLevel : public GameLevel
{
	// RTTI Àû¿ë.
	RTTI_DECLARATIONS(ToolLevel, GameLevel)

public:
	ToolLevel();
	~ToolLevel();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	void Get_KeyDown();
	bool Find_Actor(const Vector2& vPosition);
	void Delete_Actor(const Vector2& vPosition);
	void Save_Actor();
	
private:
	Tile_Manager* m_pTile_Manager = nullptr;
	Player* m_pPlayer = nullptr;
};