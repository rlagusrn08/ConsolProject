#include "Tile.h"

Tile::Tile(const Vector2& _position)
{

}

void Tile::Draw()
{
	if (!m_bShouldDraw) return;

	// 그리기.
	// 1단계: 콘솔 좌표 옮기기.
	Engine::Get().SetCursorPosition(m_tInfo.vPos);

	// 2단계: 그리기 (콘솔 출력).
	if (m_tInfo.eOption == 0)
		Log(" ");
	if (m_tInfo.eOption == 1)
		Log("◆");

	// 색상 복구.
	SetColor(Color::White);

	m_bShouldDraw = false;
}

