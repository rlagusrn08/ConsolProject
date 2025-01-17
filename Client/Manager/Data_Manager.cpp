#include "Data_Manager.h"
#include "Engine/Engine.h"

Data_Manager* Data_Manager::instance = nullptr;

Data_Manager::Data_Manager()
{
	instance = this;
}

Data_Manager::~Data_Manager()
{
}

void Data_Manager::Draw()
{
	if (currentMode == MODE::GAME_MODE)
	{
		Vector2 UIPosition = Vector2(0, ENGINE.ScreenSize().y - 1);

		const char* first = "Score : ";
		char* s = new char[255];
		char* buffer = new char[255];
		snprintf(s, sizeof(s), "%d", score);

		strcpy_s(buffer, strlen(first) + 1, first);
		strcat_s(buffer, strlen(first) + strlen(s) + 1, s);

		ENGINE.Draw(UIPosition, buffer);
		delete[] buffer;
		delete[] s;
	}
	else if (currentMode == MODE::TOOL_MODE)
	{
		Vector2 UIPosition = Vector2(0, ENGINE.ScreenSize().y - 1);
		ENGINE.Draw(UIPosition, "1 : º®, 2 : À¯·É");
	}
}
