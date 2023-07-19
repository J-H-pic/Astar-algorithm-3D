#pragma once
#include <limits>

struct Node {
    int x, y, z;
    bool isObstacle;
    float cost;
    Node* parent;

    Node(int x = 0, int y = 0, int z = 0, bool isObstacle = false, float cost = std::numeric_limits<float>::infinity(), Node* parent = nullptr)
        : x(x), y(y), z(z), isObstacle(isObstacle), cost(cost), parent(parent) {}

    void reset() {
        cost = std::numeric_limits<float>::infinity();
        parent = nullptr;
    }
};
