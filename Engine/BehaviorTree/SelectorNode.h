#pragma once
#include "Node.h"
#include <list>

class ENGINE_API SelectorNode : public Node {
	RTTI_DECLARATIONS(SelectorNode, Node)

public:
	SelectorNode();
	virtual ~SelectorNode();

public:
	void Add(Node* node) { m_ChildList.push_back(node); }
	virtual Node::STATE Evaluate(float deltaTime);

private:
	std::list<Node*> m_ChildList;
};