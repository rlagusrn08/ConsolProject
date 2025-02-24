#pragma once

#include "Level/Level.h"
#include "QuadTree/QuadTree.h"

class Player;
class GameLevel : public Level
{
	// RTTI Àû¿ë.
	RTTI_DECLARATIONS(GameLevel, Level)
public:
	virtual ~GameLevel();
protected:
	void Load_Actor(const char* path);
	void Clear_Actor();
	void ProcessCollisionPlayerAndActor();
	void Check_GameClear();

private:
	QuadTree* m_pQuadTree = nullptr;
	vector<QT_Node*> vNodes;
	Player* m_pPlayer = nullptr;
};