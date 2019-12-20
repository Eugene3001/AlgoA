#include "node.h"

Node::Node()
    : m_parent(nullptr), m_matrix(), m_x(0), m_y(0), m_cost(0), m_level(0)
{}


Node::Node(const std::vector<std::vector<int>>& matrix, int x, int y, int newX, int newY, int level, Node* parent)
    : m_parent(parent), m_matrix(matrix), m_cost(INT_MAX), m_level(level), m_x(newX), m_y(newY)
{
    std::swap(m_matrix[x][y], m_matrix[newX][newY]);
}

Node* Node::getParent() const { return m_parent; }
void Node::setParent(Node* parent) { m_parent = parent; }

const std::vector<std::vector<int>>& Node::getMatrix() const{ return m_matrix; }
void Node::setMatrix(const std::vector<std::vector<int>>& matrix){ m_matrix = matrix; }

int Node::getCost() const{ return m_cost; }
void Node::setCost(int cost){ m_cost = cost; }

int Node::getLevel() const{ return m_level; }
void Node::setLevel(int level){ m_level = level; }

int Node::getX() const{ return m_x; }
void Node::setX(int x){ m_x = x; }

int Node::getY() const{ return m_y; }
void Node::setY(int y){ m_y = y; }

bool Node::isSafe(int x, int y) const {
    return (x >= 0 && x < m_matrix.size() && y >= 0 && y < m_matrix.size());
}
