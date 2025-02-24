#pragma once
#include "QT_Node.h"
#include "Actor/Actor.h"

class ENGINE_API QuadTree
{
public:
	QuadTree(const Bounds& bounds);
	~QuadTree();

	void Insert(QT_Node* node);
	vector<Actor*> Query(QT_Node* queryNode);
	void Clear();

public:
	static const int maxDepth = 2;

private:
	QT_Node* root = nullptr;
};