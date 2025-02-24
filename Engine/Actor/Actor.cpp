#include "PreCompiledHeader.h"
#include "Actor.h"
#include "../QuadTree/QT_Node.h"
#include "Core.h"

Actor::Actor()
	: isActive(true), isExpired(false)
{
}

Actor::~Actor()
{
}

void Actor::Update(float delatTime)
{
}

void Actor::Draw()
{
}

void Actor::SetPosition(const Vector2& newPosition)
{
	position = newPosition;
}

inline Vector2 Actor::Position() const
{
	return position;
}

const char* Actor::Serialize()
{
	return nullptr;
}

void Actor::Intersect(Actor* other)
{
}

QT_Node* Actor::Get_QT_Node()
{
	return node;
}
