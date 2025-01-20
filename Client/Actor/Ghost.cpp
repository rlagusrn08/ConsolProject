#include "Ghost.h"
#include "Tile/Tile_Manager.h"
#include "Manager/Data_Manager.h"
#include "BehaviorTree/SequenceNode.h"
#include "BehaviorTree/ActionNode.h"

Ghost::Ghost(const Vector2& _position)
	: DrawableActor("G")
{
	this->position = _position;
	color = Color::Red;

	m_tAttackDurationTimeInfo.DurationTime = 8.f;
	m_tAttackCoolTimeInfo.CoolTime = 5.f;

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
		TimeCheck(deltaTime);
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

	
	TM.Start_Astar(position, DM.Get_Player_Position(), m_BestRoute);
	
}

Node::STATE Ghost::Check_Player_Item_Active(float deltaTime)
{
	if (DM.Get_ItemActive())
	{
		color = Color::Blue;
		return Node::STATE::SUCCESS;
	}
	else
	{
		color = Color::Red;
		return Node::STATE::FAILED;
	}
}

Node::STATE Ghost::Runaway(float deltaTime)
{
	m_bAttackCoolTime = false;
	m_tAttackCoolTimeInfo.AccCoolTime = 0.f;
	m_tAttackDurationTimeInfo.AccDurationTime = 0.f;

	Vector2 vRunawayPosition;
	if (!m_BestRoute.empty())
	{
		Vector2 vTemp = position - m_BestRoute.front()->Position();

		if (vTemp.x == 1 || vTemp.x == -1)
		{
			m_fCurrentSpeed = m_fSpeedX;
		}
		else
		{
			m_fCurrentSpeed = m_fSpeedY;
		}

		bool bPositionCheck = false;
		vRunawayPosition = position + vTemp;
		if (TM.Get_Tile_Type(vRunawayPosition) != TILE_NORMAL)
		{
			int iRandom = rand() % 2;
			if (m_fCurrentSpeed == m_fSpeedX)
			{
				if (iRandom == 0)
				{
					vRunawayPosition = Vector2(position.x, position.y + 1);
					if (TM.Get_Tile_Type(vRunawayPosition) == TILE_NORMAL)
					{
						bPositionCheck = true;
					}
					if (!bPositionCheck)
					{
						vRunawayPosition = Vector2(position.x, position.y - 1);
						if (TM.Get_Tile_Type(vRunawayPosition) == TILE_NORMAL)
						{
							bPositionCheck = true;
						}
					}
				}
				else
				{
					vRunawayPosition = Vector2(position.x, position.y - 1);
					if (TM.Get_Tile_Type(vRunawayPosition) == TILE_NORMAL)
					{
						bPositionCheck = true;
					}
					if (!bPositionCheck)
					{
						vRunawayPosition = Vector2(position.x, position.y + 1);
						if (TM.Get_Tile_Type(vRunawayPosition) == TILE_NORMAL)
						{
							bPositionCheck = true;
						}
					}
				}
			}
			if (m_fCurrentSpeed == m_fSpeedY)
			{
				if (iRandom == 0)
				{
					vRunawayPosition = Vector2(position.x + 1, position.y);
					if (TM.Get_Tile_Type(vRunawayPosition) == TILE_NORMAL)
					{
						bPositionCheck = true;
					}
					if (!bPositionCheck)
					{
						vRunawayPosition = Vector2(position.x - 1, position.y);
						if (TM.Get_Tile_Type(vRunawayPosition) == TILE_NORMAL)
						{
							bPositionCheck = true;
						}
					}
				}
				else
				{
					vRunawayPosition = Vector2(position.x - 1, position.y);
					if (TM.Get_Tile_Type(vRunawayPosition) == TILE_NORMAL)
					{
						bPositionCheck = true;
					}
					if (!bPositionCheck)
					{
						vRunawayPosition = Vector2(position.x + 1, position.y);
						if (TM.Get_Tile_Type(vRunawayPosition) == TILE_NORMAL)
						{
							bPositionCheck = true;
						}
					}
				}
			}
			if (!bPositionCheck)
			{
				vRunawayPosition = m_BestRoute.front()->Position();
			}
		}
	}

	m_fMovement += deltaTime * m_fCurrentSpeed;
	if (m_fMovement >= 1.f)
	{
		m_fMovement -= 1.f;

		if (!m_BestRoute.empty())
		{
			SetPosition(vRunawayPosition);
			m_BestRoute.pop_front();
		}
	}

	return Node::STATE::RUN;
}

Node::STATE Ghost::Attack_Distance_Check(float deltaTime)
{
	if (DM.Get_Distance_With_Player(Position()) < m_fAttackRange)
	{
		return Node::STATE::SUCCESS;
	}
	else
	{
		return Node::STATE::FAILED;
	}
}

Node::STATE Ghost::Attack_CoolTime_Check(float deltaTime)
{
	if (m_tAttackDurationTimeInfo.AccDurationTime < m_tAttackDurationTimeInfo.DurationTime)
	{
		return Node::STATE::SUCCESS;
	}
	else
	{
		return Node::STATE::FAILED;
	}
}

void Ghost::TimeCheck(float deltaTime)
{
	if (m_tAttackDurationTimeInfo.AccDurationTime >= m_tAttackDurationTimeInfo.DurationTime && !m_bAttackCoolTime)
	{
		m_bAttackCoolTime = true;
		m_tAttackCoolTimeInfo.AccCoolTime = 0.f;
	}
	if (m_bAttackCoolTime)
	{
		m_tAttackCoolTimeInfo.AccCoolTime += deltaTime;
		if (m_tAttackCoolTimeInfo.AccCoolTime >= m_tAttackCoolTimeInfo.CoolTime)
		{
			m_bAttackCoolTime = false;
			m_tAttackDurationTimeInfo.AccDurationTime = 0.f;
		}
	}
}

Node::STATE Ghost::Trace(float deltaTime)
{
	m_tAttackDurationTimeInfo.AccDurationTime += deltaTime;

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
			SetPosition(m_BestRoute.front()->Position());
			m_BestRoute.pop_front();
		}
	}

	return Node::STATE::RUN;
}

Node::STATE Ghost::CanRandomMove(float deltaTime)
{
	bool bCanMove = false;
	int dx[4] = {1, 0, -1, 0};
	int dy[4] = { 0, 1, 0, -1 };

	for (int i = 0; i < 4; i++)
	{
		Vector2 vTemp = Vector2(position.x + dx[i], position.y + dy[i]);
		if (TM.Get_Tile_Type(vTemp) == TILE_NORMAL)
		{
			return Node::STATE::SUCCESS;
		}
	}
	return Node::STATE::FAILED;
}

Node::STATE Ghost::RandomMove(float deltaTime)
{
	int dx[4] = { 1, 0, -1, 0 };
	int dy[4] = { 0, 1, 0, -1 };

	while (true)
	{
		int iRandom = rand() % 4;
		Vector2 vTemp = Vector2(position.x + dx[iRandom], position.y + dy[iRandom]);
		if (TM.Get_Tile_Type(vTemp) == TILE_NORMAL)
		{
			if (iRandom == 0 || iRandom == 2)
			{
				m_fCurrentSpeed = m_fSpeedX;
			}
			else
			{
				m_fCurrentSpeed = m_fSpeedY;
			}

			m_fMovement += deltaTime * m_fCurrentSpeed;
			if (m_fMovement >= 1.f)
			{
				m_fMovement = 0.f;
				SetPosition(vTemp);
			}
			break;
		}
	}

	return Node::STATE::RUN;
}

Node::STATE Ghost::Stop(float deltaTime)
{
	return Node::STATE::RUN;
}

void Ghost::Make_BehaviorTree()
{
	//                                             Selector
	//           RunAway                            Attack                             Patrol                Stop
	//  Plyaer State Check - RunAway       CoolTime, Distance Check - Trace      CanMove? - RandomMove       Stop

	SequenceNode* RunawaySequence = new SequenceNode;
	SequenceNode* AttackSequence = new SequenceNode;
	SequenceNode* PatrolSequence = new SequenceNode;
	SequenceNode* StopSequence = new SequenceNode;

	RunawaySequence->Add(new ActionNode(std::bind(&Ghost::Check_Player_Item_Active, this, std::placeholders::_1)));
	RunawaySequence->Add(new ActionNode(std::bind(&Ghost::Runaway, this, std::placeholders::_1)));

	AttackSequence->Add(new ActionNode(std::bind(&Ghost::Attack_CoolTime_Check, this, std::placeholders::_1)));
	AttackSequence->Add(new ActionNode(std::bind(&Ghost::Attack_Distance_Check, this, std::placeholders::_1)));
	AttackSequence->Add(new ActionNode(std::bind(&Ghost::Trace, this, std::placeholders::_1)));

	PatrolSequence->Add(new ActionNode(std::bind(&Ghost::CanRandomMove, this, std::placeholders::_1)));
	PatrolSequence->Add(new ActionNode(std::bind(&Ghost::RandomMove, this, std::placeholders::_1)));

	StopSequence->Add(new ActionNode(std::bind(&Ghost::Stop, this, std::placeholders::_1)));

	m_pRootNode->Add(RunawaySequence);
	m_pRootNode->Add(AttackSequence);
	m_pRootNode->Add(PatrolSequence);
	m_pRootNode->Add(StopSequence);
}
