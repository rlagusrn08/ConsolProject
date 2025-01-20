#include "Ghost.h"
#include "Tile/Tile_Manager.h"
#include "Manager/Data_Manager.h"
#include "BehaviorTree/SequenceNode.h"
#include "BehaviorTree/ActionNode.h"

Ghost::Ghost(const Vector2& _position)
	: DrawableActor("G")
{
	this->position = _position;
	color = Color::Blue;

	if (DM.Get_Mode() == GAME_MODE)
	{
		m_pRootNode = new SelectorNode;
		Make_BehaviorTree();
	}
}

Ghost::~Ghost()
{
	delete m_pRootNode;
}

void Ghost::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (DM.Get_Mode() == GAME_MODE)
	{
		Make_Route();
		m_pRootNode->Evaluate(deltaTime);
	}
}

const char* Ghost::Serialize()
{
	char* buffer = new char[256];
	snprintf(buffer, 256, "G %d %d\n", Position().x, Position().y);
	return buffer;
}

void Ghost::Make_Route()
{
	if (DM.Get_Mode() != GAME_MODE) return;

	if (DM.Get_Detect_Player_Move())
	{
		TM.Start_Astar(position, DM.Get_Player_Position(), m_BestRoute);
	}
}

Node::STATE Ghost::Check_Player_Item_Active(float deltaTime)
{
	if (DM.Get_ItemActive())
		return Node::STATE::SUCCESS;
	else
		return Node::STATE::FAILED;
}

Node::STATE Ghost::RunAway(float deltaTime)
{
	return Node::STATE::RUN;
}

Node::STATE Ghost::Attack_Distance_Check(float deltaTime)
{
	if (DM.Get_Distance_With_Player(Position()) > m_fAttackRange)
	{
		return Node::STATE::FAILED;
	}
	else
	{
		return Node::STATE::SUCCESS;
	}
}

Node::STATE Ghost::Attack_CoolTime_Check(float deltaTime)
{
	return Node::STATE::SUCCESS;
}

Node::STATE Ghost::Trace(float deltaTime)
{
	if (DM.Get_Mode() != GAME_MODE) return Node::STATE::FAILED;

	if (!m_BestRoute.empty())
	{
		Vector2 VTemp = position - m_BestRoute.front()->Position();

		if (VTemp.x == 1 || VTemp.x == -1)
		{
			m_fCurrentSpeed = m_fSpeedX;
		}
		else
		{
			m_fCurrentSpeed = m_fSpeedY;
		}
	}

	m_fMovement += deltaTime * m_fCurrentSpeed;
	if (m_fMovement >= 1.f)
	{
		m_fMovement -= 1.f;
		
		if (!m_BestRoute.empty())
		{
			TM.Set_ShouldDraw(Position());
			SetPosition(m_BestRoute.front()->Position());
			m_BestRoute.pop_front();
		}
	}

	return Node::STATE::RUN;
}

Node::STATE Ghost::RandomMove(float deltaTime)
{
	return Node::STATE::RUN;
}

void Ghost::Make_BehaviorTree()
{
	//                                             Selector
	//           RunAway                            Attack                         Patrol
	//  Plyaer State Check - RunAway       CoolTime, Distance Check - Trace       RandomMove

	SequenceNode* AttackSequence = new SequenceNode;
	SequenceNode* PatrolSequence = new SequenceNode;

	AttackSequence->Add(new ActionNode(std::bind(&Ghost::Attack_CoolTime_Check, this, std::placeholders::_1)));
	AttackSequence->Add(new ActionNode(std::bind(&Ghost::Attack_Distance_Check, this, std::placeholders::_1)));
	AttackSequence->Add(new ActionNode(std::bind(&Ghost::Trace, this, std::placeholders::_1)));

	PatrolSequence->Add(new ActionNode(std::bind(&Ghost::RandomMove, this, std::placeholders::_1)));

	m_pRootNode->Add(AttackSequence);
	m_pRootNode->Add(PatrolSequence);
}
