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
    // 겹침 가능성이 있는 영역 확인.
    std::vector<QT_Node*> possibleNodes;
    root->Query(queryNode->Get_Bounds(), possibleNodes);

    // 겹침 가능성 있는 노드에서 실제로 겹치는 노드들만 다시 검사.
    std::vector<Actor*> actors;
    for (QT_Node* node : possibleNodes)
    {
        for (Actor* point : node->Points())
        {
            actors.push_back(point);
        }
    }

    // 검사한 결과 최종 반환.
    return actors;
}
