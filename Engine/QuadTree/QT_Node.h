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

class ENGINE_API QT_Node
{
public:
	QT_Node(const Bounds& bounds, Actor* owner, int depth = 0);
	~QT_Node();

public:
	void Insert(QT_Node* node);
	void Query(const Bounds& queryBounds, std::vector<QT_Node*>& possibleNodes);
	void Clear();

public:
	Bounds Get_Bounds() { return bounds; }
	const vector<Actor*>& Points() const { return points; }

	QT_Node* Get_TopLeft() const { return topLeft; }
	QT_Node* Get_TopRight() const { return topRight; }
	QT_Node* Get_BottomLeft() const { return bottomLeft; }
	QT_Node* Get_BottomRight() const { return bottomRight; }
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

	QT_Node* topLeft = nullptr;
	QT_Node* topRight = nullptr;
	QT_Node* bottomLeft = nullptr;
	QT_Node* bottomRight = nullptr;
};