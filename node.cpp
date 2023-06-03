#include "Node.h"

Node::Node(int x, int y, int z, bool isObstacle, float cost, Node* parent) : x(x), y(y), z(z), isObstacle(isObstacle), cost(cost), parent(parent) {}
