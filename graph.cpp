#include <iostream>
#include <vector>

using namespace std;

class Node {
public:
    int colour;
    Node* children;
};

class Graph {
public:
    int num_nodes;
    vector<Node> nodes;
};
