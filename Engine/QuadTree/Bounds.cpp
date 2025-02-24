#include "PreCompiledHeader.h"
#include "Bounds.h"

bool Bounds::Intersects(const Bounds& other) const
{
    // �ٸ� ������ ���� ������ ������ �ٱ��� �ִ� ���.
    if (other.x > MaxX()) return false;

    // �ٸ� ������ ���� ������ ���� �ٱ��� �ִ� ���.
    if (other.MaxX() < x) return false;

    // �ٸ� ������ ���� ������ �Ʒ��� �ٱ��� �ִ� ���.
    if (other.y > MaxY()) return false;

    // �ٸ� ������ ���� ������ ���� �ٱ��� �ִ� ���.
    if (other.MaxY() < y) return false;

    return true;
}