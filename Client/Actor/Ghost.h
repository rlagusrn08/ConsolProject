#pragma once

#include "Actor/DrawableActor.h"
#include "BehaviorTree/SelectorNode.h"
#include "Tile/Tile.h"
#include <list>

class Tile;
class Ghost : public DrawableActor
{
	RTTI_DECLARATIONS(Ghost, DrawableActor)

public:
	Ghost(const Vector2& _position);
	virtual ~Ghost();

public:
	virtual void Update(float delatTime);
	virtual const char* Serialize() override;
	
private:
	void Make_Route();
	Node::STATE Check_Player_Item_Active(float deltaTime);
	Node::STATE Runaway(float deltaTime);
	Node::STATE Attack_Distance_Check(float deltaTime);
	Node::STATE Attack_CoolTime_Check(float deltaTime);
	void TimeCheck(float deltaTime);
	Node::STATE Trace(float deltaTime);
	Node::STATE CanRandomMove(float deltaTime);
	Node::STATE RandomMove(float deltaTime);
	Node::STATE Stop(float deltaTime);
private:
	list<Tile*> m_BestRoute;

	const float m_fSpeedX = 5.5f;
	const float m_fSpeedY = 3.f;
	float m_fCurrentSpeed = 0.f;
	float m_fMovement = 0.f;
	float m_fAttackRange = 10.f;

	bool m_bAttackCoolTime = false;
	DurationTimeInfo m_tAttackDurationTimeInfo;
	CoolTimeInfo m_tAttackCoolTimeInfo;

private:
	void Make_BehaviorTree();
	//For. Behavior Tree
	SelectorNode* m_pRootNode = nullptr;

};