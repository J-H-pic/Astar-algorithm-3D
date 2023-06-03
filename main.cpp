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
};

std::vector<Node*> findPathAvoidingConflict(AStar& aStar, Agent& agent, Node* conflictNode, std::vector<std::vector<std::vector<Node>>>& grid) {
    conflictNode->isObstacle = true;
    std::vector<Node*> newPath = aStar.findPath(agent.start, agent.goal, grid);
    conflictNode->isObstacle = false;
    return newPath;
}

int main() {
    int size = 100; // 가로,세로 크기 설정
    std::vector<std::vector<std::vector<Node>>> grid(size, std::vector<std::vector<Node>>(size, std::vector<Node>(size)));

    // 맵의 사이즈 설정
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < 2; k++) {
                grid[i][j][k] = Node(i, j, k);
            }
        }
    }

    Agent agent1, agent2;
    agent1.start = &grid[0][0][0];
    agent1.goal = &grid[size - 1][size - 1][0];

    agent2.start = &grid[0][0][1];
    agent2.goal = &grid[size - 1][size - 1][1];

    AStar aStar;
    agent1.path = aStar.findPath(agent1.start, agent1.goal, grid);
    agent2.path = aStar.findPath(agent2.start, agent2.goal, grid);

    std::unordered_set<Node*> pathSet(agent1.path.begin(), agent1.path.end());
   

    for (Node* node : agent2.path) {
        if (pathSet.count(node)) {
            std::vector<Node*> newPath = findPathAvoidingConflict(aStar, agent2, node, grid);
            if (newPath.empty()) {
                std::cout << "No possible path for agent 2 avoiding conflict at node ("
                    << node->x << ", " << node->y << ", " << node->z << ").\n";
            }
            else if (agent2.path.size() > newPath.size()) {
                agent2.path = newPath;
            }
        }
    }

    // 두개의 경로 출력
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