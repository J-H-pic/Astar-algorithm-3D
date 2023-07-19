#include <cmath>
#include <queue>
#include "AStar.h"

AStar::AStar() {}

AStar::~AStar() {}

std::vector<Node*> AStar::getNeighbors(Node* node, std::vector<std::vector<std::vector<Node>>>& grid) {
    std::vector<Node*> neighbors;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            for (int dz = -1; dz <= 1; dz++) {
                int nx = node->x + dx;
                int ny = node->y + dy;
                int nz = node->z + dz;
                if (nx >= 0 && nx < grid.size() && ny >= 0 && ny < grid[0].size() && nz >= 0 && nz < grid[0][0].size() && !grid[nx][ny][nz].isObstacle) {
                    neighbors.push_back(&grid[nx][ny][nz]);
                }
            }
        }
    }
    return neighbors;
}

float AStar::heuristic(Node* a, Node* b) {
    int dx = a->x - b->x;
    int dy = a->y - b->y;
    int dz = a->z - b->z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

std::vector<Node*> AStar::findPath(Node* start, Node* goal, std::vector<std::vector<std::vector<Node>>>& grid) {
    struct NodeCompare {
        bool operator()(const Node* lhs, const Node* rhs) const {
            return lhs->cost > rhs->cost;
        }
    };
    std::priority_queue<Node*, std::vector<Node*>, NodeCompare> openSet;
    start->cost = 0.0f;
    openSet.push(start);

    while (!openSet.empty()) {
        Node* current = openSet.top();
        openSet.pop();

        if (current == goal) {
            std::vector<Node*> path;
            while (current != nullptr) {
                path.push_back(current);
                current = current->parent;
            }
            return path;
        }

        for (Node* neighbor : getNeighbors(current, grid)) {
            float newCost = current->cost + heuristic(current, neighbor);
            if (newCost < neighbor->cost) {
                neighbor->cost = newCost;
                neighbor->parent = current;
                openSet.push(neighbor);
            }
        }
    }
    return std::vector<Node*>();
}
