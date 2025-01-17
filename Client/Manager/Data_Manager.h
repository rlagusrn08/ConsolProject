#pragma once
#include "Include.h"
#include "Actor/Player.h"

enum MODE {
	GAME_MODE,
	TOOL_MODE,
	MENU_MODE,
	MODE_END
};

class Data_Manager
{
public:
	Data_Manager();
	~Data_Manager();
	static Data_Manager& Get() { return *instance; }

public:
	void Draw();

public:
	Vector2 Get_Player_Position() { return CurrentPlayer->Position(); }
	void Set_Player_Pointer(Player* _player) { CurrentPlayer = _player; }
	void Set_Detect_Player_Move(bool _value) { bDetectPlayerMove = _value; }
	bool Get_Detect_Player_Move() { return bDetectPlayerMove; }
	void Increase_Score(int _score) { score += _score; }
	
	void Set_Mode(MODE eMode) { currentMode = eMode; }
	MODE Get_Mode() { return currentMode; }

private:
	static Data_Manager* instance;

private:
	Player* CurrentPlayer = nullptr;
	bool bDetectPlayerMove = false;
	int score = 0;
	MODE currentMode = MENU_MODE;
};
