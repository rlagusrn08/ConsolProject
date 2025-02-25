#pragma once
#pragma once
#include <vector>
#include "Core.h"
#include "Bounds.h"
#include "Actor/Actor.h"

using namespace std;

enum class NodeIndex
{
	TOP_LEFT,
	TOP_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_RIGHT,
	STRADDLING,
	OUT_OF_AREA,
	END
};

class ENGINE_API QTNode
{
public:
	QTNode(const Bounds& bounds, Actor* owner, int depth = 0);
	~QTNode();

public:
	void Insert(QTNode* node);
	void Query(const Bounds& queryBounds, std::vector<QTNode*>& possibleNodes);
	void Clear();

public:
	Bounds Get_Bounds() { return bounds; }
	const vector<Actor*>& Points() const { return points; }

	QTNode* Get_TopLeft() const { return topLeft; }
	QTNode* Get_TopRight() const { return topRight; }
	QTNode* Get_BottomLeft() const { return bottomLeft; }
	QTNode* Get_BottomRight() const { return bottomRight; }
	Actor* Get_Owner() { return m_pOwner; }
private:
	NodeIndex TestRegion(const Bounds& _bounds);
	vector<NodeIndex> GetQuads(const Bounds& _bounds);
	bool Subdivide();
	bool IsDivided();
	void ClearChildren();

private:
	int depth = 0;

	Actor* m_pOwner = nullptr;

	Bounds bounds;
	vector<Actor*> points;

	bool isDivided = false;
	QTNode* topLeft = nullptr;
	QTNode* topRight = nullptr;
	QTNode* bottomLeft = nullptr;
	QTNode* bottomRight = nullptr;
};