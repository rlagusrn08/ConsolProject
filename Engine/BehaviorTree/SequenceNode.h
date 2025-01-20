#pragma once
#include "Node.h"
#include <list>

class ENGINE_API SequenceNode : public Node
{
public:
	SequenceNode();
	virtual ~SequenceNode();

public:
	void Add(Node* node);
	virtual Node::STATE Evaluate(float deltaTime);

private:
	std::list<Node*> m_ChildList;
};

