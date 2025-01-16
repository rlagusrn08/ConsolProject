#include "PreCompiledHeader.h"
#include "DrawableActor.h"
#include "Engine/Engine.h"

DrawableActor::DrawableActor(const char* image)
	: Actor()/*, image(image)*/
{
	// 전달 받은 문자열 복사.
	auto length = strlen(image) + 1;
	this->image = new char[length];
	strcpy_s(this->image, length, image);

	// 너비 설정.
	width = (int)strlen(image);
}

DrawableActor::~DrawableActor()
{
	delete[] image;
}

void DrawableActor::Draw()
{
	Super::Draw();

	// 그리기.
	// 1단계: 콘솔 좌표 옮기기.
	Engine::Get().SetCursorPosition(position);

	// 2단계: 그리기 (콘솔 출력).
	Log(image);
}

void DrawableActor::SetPosition(const Vector2& newPosition)
{
	//// 이전의 위치를 먼저 지우기.
	//Engine::Get().SetCursorPosition(position);
	//Log(" ");

	// 위치를 새로 옮기기.
	Super::SetPosition(newPosition);
}

bool DrawableActor::Intersect(const DrawableActor& other)
{
	int min = position.x; // Left
	int max = position.x + width; // Right

	int otherMin = other.position.x;
	int otherMax = other.position.x + other.width;

	// 다른 액터의 왼쪽 끝 위치가 내 오른쪽 위치를 벗어나는 경우, 반대의 경우 충돌하지 않은 것
	if (otherMin > max || otherMax < min)
	{
		return false;
	}
	
	// X가 겹치는 경우 y위치를 비교한다.
	return position.y == other.position.y;
}
