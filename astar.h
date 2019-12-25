#ifndef ASTAR_H
#define ASTAR_H

#include "node.h"
#include <bits/stdc++.h>

class AStar
{
public:
    static Node* solve(std::vector<std::vector<int>> initial, int x, int y, std::vector<std::vector<int>> final, int& count);

private:
    static int calculateCost(std::vector<std::vector<int>> initial, std::vector<std::vector<int>> final);
};

#endif // ASTAR_H
