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
	bool Get_ItemActive() { return bItemActive; }
	void Set_ItemActive(bool _bCheck) { bItemActive = _bCheck; }
	float Get_Distance_With_Player(const Vector2& _position);
	void Reset_Score() { score = 0; }
	void Increase_Score(int _score) { score += _score; }
	
	void Set_Mode(MODE eMode) { currentMode = eMode; }
	MODE Get_Mode() { return currentMode; }

	void Set_Ready(bool bReady) { bReadyGame = bReady; }
	bool Get_Ready() { return bReadyGame; }

	void Set_Level(GAMELEVEL _level) { eCurrentLevel = _level; }
	GAMELEVEL Get_Level() { return eCurrentLevel; }
private:
	static Data_Manager* instance;

private:
	Player* CurrentPlayer = nullptr;
	bool bItemActive = false;
	bool bReadyGame = true;
	bool bDetectPlayerMove = false;
	int score = 0;
	GAMELEVEL eCurrentLevel = GAMELEVEL_END;
	MODE currentMode = MENU_MODE;
};
