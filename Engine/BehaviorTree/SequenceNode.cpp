#include "PreCompiledHeader.h"
#include "SequenceNode.h"

SequenceNode::SequenceNode()
{
}

SequenceNode::~SequenceNode()
{
	for (auto iter : m_ChildList)
	{
		delete iter;
	}
}

void SequenceNode::Add(Node* node)
{
	m_ChildList.push_back(node);
}

Node::STATE SequenceNode::Evaluate(float deltaTime)
{
	if (m_ChildList.size() == 0)
		return FAILED;

	for (auto iter : m_ChildList)
	{
		switch (iter->Evaluate(deltaTime))
		{
		case RUN:
			return RUN;
		case FAILED:
			return FAILED;
		}
	}

	return SUCCESS;
}
