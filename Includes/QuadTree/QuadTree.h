#pragma once
#include "QT_Node.h"
#include "Actor/Actor.h"

class ENGINE_API QuadTree
{
public:
	QuadTree(const Bounds& bounds);
	~QuadTree();

	void Insert(QTNode* node);
	vector<Actor*> Query(QTNode* queryNode);
	void Clear();

public:
	static const int maxDepth = 2;

private:
	QTNode* root = nullptr;
};