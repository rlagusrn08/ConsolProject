#include "PreCompiledHeader.h"
#include "QT_NODE.h"
#include "QuadTree.h"

QT_Node::QT_Node(const Bounds& bounds, Actor* owner, int depth)
	: bounds(bounds), depth(depth)
{
	m_pOwner = owner;
}

QT_Node::~QT_Node()
{
	Clear();
}

void QT_Node::Insert(QT_Node* node)
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

void QT_Node::Query(const Bounds& queryBounds, std::vector<QT_Node*>& possibleNodes)
{
	possibleNodes.push_back(this);

	if (IsDivided())
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

void QT_Node::Clear()
{
	if (IsDivided())
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
}

NodeIndex QT_Node::TestRegion(const Bounds& other)
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

vector<NodeIndex> QT_Node::GetQuads(const Bounds& other)
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

bool QT_Node::Subdivide()
{
	// �ִ� ���̿� ���������� ���̻� �ȳ���.
	if (depth == QuadTree::maxDepth)
	{
		return false;
	}

	// ���� ���� �ȵ�����, ���� ����.
	if (!IsDivided())
	{
		// ������ ������ ���� �� ���.
		float x = bounds.X();
		float y = bounds.Y();
		float halfWidth = bounds.Width() / 2;
		float halfHeight = bounds.Height() / 2;

		// �� 4�и��� �ڽ� ��ü ����.
		topLeft = new QT_Node(Bounds(x, y, halfWidth, halfHeight), nullptr, depth + 1);
		topRight = new QT_Node(Bounds(x + halfWidth, y, halfWidth, halfHeight), nullptr, depth + 1);
		bottomLeft = new QT_Node(Bounds(x, y + halfHeight, halfWidth, halfHeight), nullptr, depth + 1);
		bottomRight = new QT_Node(Bounds(x + halfWidth, y + halfHeight, halfWidth, halfHeight), nullptr, depth + 1);
	}

	return true;
}


bool QT_Node::IsDivided()
{
	return topLeft != nullptr;
}

void QT_Node::ClearChildren()
{
	//if (IsDivided())
	//{
	//	SafeDelete(topLeft);
	//	SafeDelete(topRight);
	//	SafeDelete(bottomLeft);
	//	SafeDelete(bottomRight);
	//}
}


