#include "astar.h"
int  AStar::calculateCost(std::vector<std::vector<int>> initial, std::vector<std::vector<int>> final){
    int count = 0;
        for (int i = 0; i < initial.size(); i++)
            for (int j = 0; j < initial.size(); j++)
                if (initial[i][j] && initial[i][j] != final[i][j])
                    count++;
        return count;
}

Node* AStar::solve(std::vector<std::vector<int>> initial, int x, int y, std::vector<std::vector<int>> final)
{
    int row[] = { 1, 0, -1, 0 };
    int col[] = { 0, -1, 0, 1 };

    std::priority_queue<Node*, std::vector<Node*>, comp> pq;

    Node* root = new Node(initial, x, y, x, y, 0, nullptr);
    root->setCost(calculateCost(initial, final));

    pq.push(root);

    while (!pq.empty())
    {
        Node* min = pq.top();

        pq.pop();

        if (min->getCost() == 0)
        {
            return min;
        }

        for (int i = 0; i < 4; i++)
        {
            if (min->isSafe(min->getX() + row[i], min->getY() + col[i]))
            {
                Node* child = new Node(min->getMatrix(), min->getX(),
                                      min->getY(), min->getX() + row[i],
                                      min->getY() + col[i],
                                      min->getLevel() + 1, min);
                child->setCost( calculateCost(child->getMatrix(), final) );

                pq.push(child);
            }
        }
    }

    return nullptr;
}
