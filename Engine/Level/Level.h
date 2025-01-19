#pragma once

#include "Core.h"
#include "RTTI.h"
#include "Container/List.h"

// ���� ����(Forward Declaration).
class Actor;
class ENGINE_API Level : public RTTI
{
	// RTTI ����.
	RTTI_DECLARATIONS(Level, RTTI)

public:
	Level();
	virtual ~Level();

	// ���� �߰� �Լ�.
	void AddActor(Actor* newActor);
	void PushBackActor(Actor* Actor);

	// ���� ��û�� �� ���͸� �����ϴ� �Լ�.
	//void DestroyActor();
	void ProcessAddedAndDestroyedActor();
	void Clear_Level();

	// ���� ó�� �Լ�.
	virtual void Update(float deltaTime);
	virtual void Draw();

protected:
	// ���� ������ ��ġ�Ǵ� ��ü(����) �迭.
	List<Actor*> actors;

	// �߰� ��û�� ����.
	Actor* addRequestedActor = nullptr;
};