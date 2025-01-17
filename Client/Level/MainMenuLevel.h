#pragma once

#include "Level/Level.h"
#include "Container/List.h"
#include "Struct.h"

class MainMenuLevel : public Level
{
	RTTI_DECLARATIONS(MainMenuLevel, Level)

public:
	MainMenuLevel();
	~MainMenuLevel();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
	int currentIndex = 0;
	Color selectedColor = Color::Green;
	Color unselectedColor = Color::White;

	List<MenuItem*> menuItems;
	int length = 0;
};