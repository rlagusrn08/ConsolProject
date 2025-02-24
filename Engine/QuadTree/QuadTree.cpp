#include "PreCompiledHeader.h"
#include "QuadTree.h"

QuadTree::QuadTree(const Bounds& bounds)
{
    root = new QT_Node(bounds, nullptr);
}

QuadTree::~QuadTree()
{
    SafeDelete(root);
}

void QuadTree::Insert(QT_Node* node)
{
    root->Insert(node);
}

std::vector<Actor*> QuadTree::Query(QT_Node* queryNode)
{
    // ��ħ ���ɼ��� �ִ� ���� Ȯ��.
    std::vector<QT_Node*> possibleNodes;
    root->Query(queryNode->Get_Bounds(), possibleNodes);

    // ��ħ ���ɼ� �ִ� ��忡�� ������ ��ġ�� ���鸸 �ٽ� �˻�.
    std::vector<Actor*> actors;
    for (QT_Node* node : possibleNodes)
    {
        for (Actor* point : node->Points())
        {
            actors.push_back(point);
        }
    }

    // �˻��� ��� ���� ��ȯ.
    return actors;
}
