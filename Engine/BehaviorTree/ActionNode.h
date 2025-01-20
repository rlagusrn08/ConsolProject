#pragma once
#include "Node.h"
#include <functional>

class ENGINE_API ActionNode : public Node
{
	RTTI_DECLARATIONS(ActionNode, Node)
public:
	using Action = std::function<Node::STATE(float)>;

public:
	ActionNode(Action _action);
	virtual ~ActionNode();

private:
	Action action;
	virtual Node::STATE Evaluate(float deltaTime);
};