#pragma once
#include <limits>

struct Node {
    int x, y, z;
    bool isObstacle;
    float cost;
    Node* parent;

    Node(int x = 0, int y = 0, int z = 0, bool isObstacle = false, float cost = INFINITY, Node* parent = nullptr);
};
