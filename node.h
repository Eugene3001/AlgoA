#ifndef NODE_H
#define NODE_H
#include<bits/stdc++.h>

class Node
{
public:
    Node();
    Node(const std::vector<std::vector<int>>& matrix, int x, int y, int newX, int newY, int level, Node* parent);

    Node* getParent() const;
    void setParent(Node* parent);

    const std::vector<std::vector<int>>& getMatrix() const;
    void setMatrix(const std::vector<std::vector<int>>& matrix);

    int getCost() const;
    void setCost(int cost);

    int getLevel() const;
    void setLevel(int level);

    int getX() const;
    void setX(int x);

    int getY() const;
    void setY(int y);

    bool isSafe(int x, int y) const;

private:
    Node* m_parent;
    std::vector<std::vector<int>> m_matrix;
    int m_cost;
    int m_level;
    int m_x, m_y;
};

struct comp
{
    bool operator()(const Node* lhs, const Node* rhs) const
    {
        return (lhs->getCost() + lhs->getLevel()) > (rhs->getCost() + rhs->getLevel());
    }
};


#endif // NODE_H
