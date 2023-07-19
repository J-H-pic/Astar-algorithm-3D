#include <iostream>
#include <vector>
#include <unordered_set>
#include "Node.h"
#include "AStar.h"

class Agent {
public:
    Node* start;
    Node* goal;
    std::vector<Node*> path;

    Agent()
        : start(nullptr), goal(nullptr) {}

    Agent(Node* start, Node* goal)
        : start(start), goal(goal) {}
};


std::vector<Node*> findPathAvoidingConflict(AStar& aStar, Agent& agent, Node* conflictNode, std::vector<std::vector<std::vector<Node>>>& grid) {
    conflictNode->isObstacle = true;
    std::vector<Node*> newPath = aStar.findPath(agent.start, agent.goal, grid);
    conflictNode->isObstacle = false;
    return newPath;
}

void resetGrid(std::vector<std::vector<std::vector<Node>>>& grid) {
    for (auto& matrix : grid) {
        for (auto& row : matrix) {
            for (auto& node : row) {
                node.reset();
            }
        }
    }
}

int main() {
    int size = 100;
    std::vector<std::vector<std::vector<Node>>> grid(size, std::vector<std::vector<Node>>(size, std::vector<Node>(size)));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                grid[i][j][k] = Node(i, j, k);
            }
        }
    }

    Agent agent1, agent2;
    agent1.start = &grid[0][0][0];
    agent1.goal = &grid[size - 1][size - 1][0];

    agent2.start = &grid[size - 1][0][0];
    agent2.goal = &grid[0][size - 1][0];

    AStar aStar;
    agent1.path = aStar.findPath(agent1.start, agent1.goal, grid);
    resetGrid(grid); // 생성한 경로를 reset agent2의 경로를 저장하기 위해서
    agent2.path = aStar.findPath(agent2.start, agent2.goal, grid);

    std::unordered_set<Node*> pathSet(agent1.path.begin(), agent1.path.end());

    for (Node* node : agent2.path) {
        if (pathSet.count(node)) {
            std::vector<Node*> newPath = findPathAvoidingConflict(aStar, agent2, node, grid);
            if (!newPath.empty() && agent2.path.size() > newPath.size()) {
                agent2.path = newPath;
            }
        }
    }

    std::cout << "Path for agent 1:\n";
    for (auto node : agent1.path) {
        std::cout << "(" << node->x << ", " << node->y << ", " << node->z << ")\n";
    }

    std::cout << "Path for agent 2:\n";
    for (auto node : agent2.path) {
        std::cout << "(" << node->x << ", " << node->y << ", " << node->z << ")\n";
    }

    return 0;
}
