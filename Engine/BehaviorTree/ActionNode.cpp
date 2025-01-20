#include "PreCompiledHeader.h"
#include "ActionNode.h"

ActionNode::ActionNode(Action _action)
    : action(_action)
{

}

ActionNode::~ActionNode()
{

}

Node::STATE ActionNode::Evaluate(float deltaTime)
{
    return action ? action(deltaTime) : FAILED;
}
