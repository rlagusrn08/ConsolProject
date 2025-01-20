#pragma once
#include "Core.h"
#include "RTTI.h"

class ENGINE_API Node : public RTTI
{
	RTTI_DECLARATIONS(Node, RTTI)
public:
	enum STATE
	{
		RUN,
		SUCCESS,
		FAILED
	};

public:
	virtual ~Node() = 0;

public:
	virtual STATE Evaluate(float deltaTime) = 0;
};