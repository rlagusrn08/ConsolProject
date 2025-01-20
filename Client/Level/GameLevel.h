#pragma once

#include "Level/Level.h"

class Player;
class GameLevel : public Level
{
	// RTTI ����.
	RTTI_DECLARATIONS(GameLevel, Level)

protected:
	void Load_Actor(const char* path);
	void Clear_Actor();
	void ProcessCollisionPlayerAndItem();

private:
	Player* m_pPlayer = nullptr;
};