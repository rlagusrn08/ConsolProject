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
    // 겹침 가능성이 있는 영역 확인.
    std::vector<QTNode*> possibleNodes;
    root->Query(queryNode->Get_Bounds(), possibleNodes);

    // 겹침 가능성 있는 노드에서 실제로 겹치는 노드들만 다시 검사.
    std::vector<Actor*> actors;
    for (QTNode* node : possibleNodes)
    {
        for (Actor* point : node->Points())
        {
            actors.push_back(point);
        }
    }

    // 검사한 결과 최종 반환.
    return actors;
}

void QuadTree::Clear()
{
    root->Clear();
}
