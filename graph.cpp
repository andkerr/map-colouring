#include <iostream>
#include <string>

using namespace std;

class Node {
public:
    Node(const string& name_in, const string& colour_in)
        : name(name_in), colour(colour_in), next(nullptr), neighbours(nullptr) {};

    string name;
    string colour;

    Node* next;
    Node** neighbours;
};

class Graph {
public:
    Graph()
        : num_nodes(0), nodes(nullptr) {};

    int num_nodes;
    Node* nodes;
};

void add_node(Graph* g, Node* n);
void add_edge(Node* n1, Node* n2);

int main() {
    Node ont = {"Ontario", "red"};
    Node man = {"Manitoba", "green"};
    Node que = {"Quebec", "blue"};

    Graph g;
    add_node(&g, &ont);
    add_node(&g, &man);
    add_node(&g, &que);
    cout << "this graph has " << g.num_nodes << " nodes\n";
}

void add_node(Graph* g, Node* n) {
    n->next = g->nodes;
    g->nodes = n;
    g->num_nodes += 1;
    cout << "added " << n->name << " to graph\n";
}

void add_edge(Graph* g, Node* n1, Node* n2) {
    
}
