#include "PreCompiledHeader.h"
#include "SelectorNode.h"

SelectorNode::SelectorNode()
{
}

SelectorNode::~SelectorNode()
{
	for (auto iter : m_ChildList)
	{
		delete iter;
	}
}

Node::STATE SelectorNode::Evaluate(float deltaTime)
{
	for (auto iter : m_ChildList)
	{
		STATE state = iter->Evaluate(deltaTime);

		if (state == SUCCESS)
			return SUCCESS;
		else if (state == RUN)
			return RUN;
	}

	return FAILED;
}
