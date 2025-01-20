#pragma once
#include "Level/Level.h"
#include "Container/List.h"
#include "Struct.h"

class GameClearLevel : public Level
{
	RTTI_DECLARATIONS(GameClearLevel, Level)

public:
	GameClearLevel();
	~GameClearLevel();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
	int currentIndex = 0;
	Color selectedColor = Color::Green;
	Color unselectedColor = Color::White;

	List<MenuItem*> menuItems;
	int length = 0;
};