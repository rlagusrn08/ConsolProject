#include "PreCompiledHeader.h"
#include "QT_NODE.h"
#include "QuadTree.h"

QTNode::QTNode(const Bounds& bounds, Actor* owner, int depth)
	: bounds(bounds), depth(depth)
{
	m_pOwner = owner;
}

QTNode::~QTNode()
{
	Clear();
}

void QTNode::Insert(QTNode* node)
{
	NodeIndex result = TestRegion(node->Get_Bounds());

	if (result == NodeIndex::STRADDLING)
	{
		points.push_back(node->Get_Owner());
	}
	else if (result != NodeIndex::OUT_OF_AREA)
	{
		if (Subdivide())
		{
			if (result == NodeIndex::TOP_LEFT)
			{
				topLeft->Insert(node);
			}
			else if (result == NodeIndex::TOP_RIGHT)
			{
				topRight->Insert(node);
			}
			else if (result == NodeIndex::BOTTOM_LEFT)
			{
				bottomLeft->Insert(node);
			}
			else if (result == NodeIndex::BOTTOM_RIGHT)
			{
				bottomRight->Insert(node);
			}
		}
		else
		{
			points.push_back(node->Get_Owner());
		}
	}
}

void QTNode::Query(const Bounds& queryBounds, std::vector<QTNode*>& possibleNodes)
{
	possibleNodes.push_back(this);

	if (isDivided)
	{
		vector<NodeIndex> quads = GetQuads(queryBounds);

		for (NodeIndex& index : quads)
		{
			if (index == NodeIndex::TOP_LEFT)
			{
				topLeft->Query(queryBounds, possibleNodes);
			}
			else if (index == NodeIndex::TOP_RIGHT)
			{
				topRight->Query(queryBounds, possibleNodes);
			}
			else if (index == NodeIndex::BOTTOM_LEFT)
			{
				bottomLeft->Query(queryBounds, possibleNodes);
			}
			else if (index == NodeIndex::BOTTOM_RIGHT)
			{
				bottomRight->Query(queryBounds, possibleNodes);
			}
		}
	}
}

void QTNode::Clear()
{
	points.clear();
	if (isDivided)
	{
		if(topLeft != nullptr)
			topLeft->Clear();
		if(topRight != nullptr)
			topRight->Clear();
		if(bottomLeft != nullptr)
			bottomLeft->Clear();
		if (bottomRight != nullptr)
			bottomRight->Clear();

		ClearChildren();
	}
	isDivided = false;
}

NodeIndex QTNode::TestRegion(const Bounds& other)
{
	vector<NodeIndex> quads = GetQuads(other);

	if (quads.size() == 0)
	{
		return NodeIndex::OUT_OF_AREA;
	}

	if (quads.size() == 1)
	{
		return quads[0];
	}

	return NodeIndex::STRADDLING;
}

vector<NodeIndex> QTNode::GetQuads(const Bounds& other)
{
	std::vector<NodeIndex> quads;

	// ���� ��꿡 �ʿ��� ����.
	float x = this->bounds.X();
	float y = this->bounds.Y();
	float halfWidth = this->bounds.Width() / 2.0f;
	float halfHeight = this->bounds.Height() / 2.0f;
	float centerX = x + halfWidth;
	float centerY = y + halfHeight;

	// ���� �����̶� ��ġ���� Ȯ��.
	bool left = other.X() < centerX && other.MaxX() >= x;

	// ������ �����̶� ��ġ���� Ȯ��.
	bool right = other.MaxX() >= centerX && other.X() < this->bounds.MaxX();

	// ���� �����̶� ��ġ���� Ȯ��.
	bool top = other.Y() < centerY && other.MaxY() >= y;

	// �Ʒ��� �����̶� ��ġ���� Ȯ��.
	bool bottom = other.MaxY() >= centerY && other.Y() < this->bounds.MaxY();

	if (top && left)
	{
		quads.emplace_back(NodeIndex::TOP_LEFT);
	}
	if (top && right)
	{
		quads.emplace_back(NodeIndex::TOP_RIGHT);
	}
	if (bottom && left)
	{
		quads.emplace_back(NodeIndex::BOTTOM_LEFT);
	}
	if (bottom && right)
	{
		quads.emplace_back(NodeIndex::BOTTOM_RIGHT);
	}

	return quads;
}

bool QTNode::Subdivide()
{
	// �ִ� ���̿� ���������� ���̻� �ȳ���.
	if (depth == QuadTree::maxDepth)
	{
		return false;
	}

	// ���� ���� �ȵ�����, ���� ����.
	if (!isDivided)
	{
		isDivided = true;
		// ������ ������ ���� �� ���.
		float x = bounds.X();
		float y = bounds.Y();
		float halfWidth = bounds.Width() / 2;
		float halfHeight = bounds.Height() / 2;

		// �� 4�и��� �ڽ� ��ü ����.
		topLeft = new QTNode(Bounds(x, y, halfWidth, halfHeight), nullptr, depth + 1);
		topRight = new QTNode(Bounds(x + halfWidth, y, halfWidth, halfHeight), nullptr, depth + 1);
		bottomLeft = new QTNode(Bounds(x, y + halfHeight, halfWidth, halfHeight), nullptr, depth + 1);
		bottomRight = new QTNode(Bounds(x + halfWidth, y + halfHeight, halfWidth, halfHeight), nullptr, depth + 1);
	}

	return true;
}


bool QTNode::IsDivided()
{
	return topLeft != nullptr;
}

void QTNode::ClearChildren()
{
	if (isDivided)
	{
		SafeDelete(topLeft);
		SafeDelete(topRight);
		SafeDelete(bottomLeft);
		SafeDelete(bottomRight);
	}
}


