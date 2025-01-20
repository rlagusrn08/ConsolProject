#pragma once

#include "Level/Level.h"

class GameLevel : public Level
{
	// RTTI Àû¿ë.
	RTTI_DECLARATIONS(GameLevel, Level)

protected:
	void Load_Actor(const char* path);
	void Clear_Actor();

};