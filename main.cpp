#include <iostream>
#include "Node.h"
#include "AStar.h"

int main() {
    int size = 20; // grid size
    std::vector<std::vector<std::vector<Node>>> grid(size, std::vector<std::vector<Node>>(size, std::vector<Node>(size)));

    // Initialize the grid
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < 2; k++) {
                grid[i][j][k] = Node(i, j, k);
            }
        }
    }

    // Add some obstacles
    for (int i = 0; i < size; i++) {
        grid[i][5][0].isObstacle = true;
    }

    Node* start = &grid[0][0][0]; // starting position
    Node* goal = &grid[size - 1][size - 1][1]; // goal position

    AStar aStar;
    std::vector<Node*> path = aStar.findPath(start, goal, grid);

    // Print the path
    for (auto node : path) {
        std::cout << "(" << node->x << ", " << node->y << ", " << node->z << ")\n";
    }

    return 0;
}
