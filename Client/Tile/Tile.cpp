#include "Tile.h"

Tile::Tile(const Vector2& _position)
{

}

void Tile::Draw()
{
	if (!m_bShouldDraw) return;

	// �׸���.
	// 1�ܰ�: �ܼ� ��ǥ �ű��.
	Engine::Get().SetCursorPosition(m_tInfo.vPos);

	// 2�ܰ�: �׸��� (�ܼ� ���).
	if (m_tInfo.eOption == 0)
		Log(" ");
	if (m_tInfo.eOption == 1)
		Log("��");

	// ���� ����.
	SetColor(Color::White);

	m_bShouldDraw = false;
}

