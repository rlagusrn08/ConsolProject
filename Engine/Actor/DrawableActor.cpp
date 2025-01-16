#include "PreCompiledHeader.h"
#include "DrawableActor.h"
#include "Engine/Engine.h"

DrawableActor::DrawableActor(const char* image)
	: Actor()/*, image(image)*/
{
	// ���� ���� ���ڿ� ����.
	auto length = strlen(image) + 1;
	this->image = new char[length];
	strcpy_s(this->image, length, image);

	// �ʺ� ����.
	width = (int)strlen(image);
}

DrawableActor::~DrawableActor()
{
	delete[] image;
}

void DrawableActor::Draw()
{
	Super::Draw();

	// �׸���.
	// 1�ܰ�: �ܼ� ��ǥ �ű��.
	Engine::Get().SetCursorPosition(position);

	// 2�ܰ�: �׸��� (�ܼ� ���).
	Log(image);
}

void DrawableActor::SetPosition(const Vector2& newPosition)
{
	//// ������ ��ġ�� ���� �����.
	//Engine::Get().SetCursorPosition(position);
	//Log(" ");

	// ��ġ�� ���� �ű��.
	Super::SetPosition(newPosition);
}

bool DrawableActor::Intersect(const DrawableActor& other)
{
	int min = position.x; // Left
	int max = position.x + width; // Right

	int otherMin = other.position.x;
	int otherMax = other.position.x + other.width;

	// �ٸ� ������ ���� �� ��ġ�� �� ������ ��ġ�� ����� ���, �ݴ��� ��� �浹���� ���� ��
	if (otherMin > max || otherMax < min)
	{
		return false;
	}
	
	// X�� ��ġ�� ��� y��ġ�� ���Ѵ�.
	return position.y == other.position.y;
}
