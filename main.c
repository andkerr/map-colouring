#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_NODES 50

typedef struct Graph {
    struct Node* head[MAX_NODES];
} Graph;

typedef struct Node {
    int colour;
    struct Node* neighbour;
} Node;

int main() {
    int num_nodes = 10;
    Graph g;
}
