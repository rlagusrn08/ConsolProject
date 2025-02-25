#include "PreCompiledHeader.h"
#include "QuadTree.h"

QuadTree::QuadTree(const Bounds& bounds)
{
    root = new QTNode(bounds, nullptr);
}

QuadTree::~QuadTree()
{
    SafeDelete(root);
}

void QuadTree::Insert(QTNode* node)
{
    root->Insert(node);
}

std::vector<Actor*> QuadTree::Query(QTNode* queryNode)
{
    // ��ħ ���ɼ��� �ִ� ���� Ȯ��.
    std::vector<QTNode*> possibleNodes;
    root->Query(queryNode->Get_Bounds(), possibleNodes);

    // ��ħ ���ɼ� �ִ� ��忡�� ������ ��ġ�� ���鸸 �ٽ� �˻�.
    std::vector<Actor*> actors;
    for (QTNode* node : possibleNodes)
    {
        for (Actor* point : node->Points())
        {
            actors.push_back(point);
        }
    }

    // �˻��� ��� ���� ��ȯ.
    return actors;
}

void QuadTree::Clear()
{
    root->Clear();
}
