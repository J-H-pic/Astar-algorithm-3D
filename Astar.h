#pragma once
#include <vector>
#include "Node.h"

class AStar {
public:
    AStar();
    ~AStar();

    std::vector<Node*> findPath(Node* start, Node* goal, std::vector<std::vector<std::vector<Node>>>& grid);
    std::vector<Node*> getNeighbors(Node* node, std::vector<std::vector<std::vector<Node>>>& grid);
    float heuristic(Node* a, Node* b);
};
