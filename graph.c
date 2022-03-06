#include "assert.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct Node Node;
struct Node {
    int capacity;
    int num_neighbours;
    int *neighbours;
};
Node *new_node(int capacity);


typedef struct Graph Graph;
struct Graph {
    int capacity;
    int num_nodes;
    Node **nodes;
};
Graph *new_graph(int num_nodes);
Graph *add_node(Graph *gptr, Node *nptr);
Graph *add_edge(Graph *gptr, int id1, int id2);
void print(Graph *gptr);

Graph *initialize_from_file(const char *fname);

int main() {
    Graph *g = initialize_from_file("graph.in");
    if (g == NULL) {
        return -1;
    }

    print(g);
}

Node *new_node(int capacity) {
    Node *nptr = (Node *) malloc(sizeof(Node));
    nptr->capacity = capacity;
    nptr->neighbours = (int *) malloc(sizeof(int) * capacity);
    nptr->num_neighbours = 0;
    return nptr;
}

Graph *new_graph(int capacity) {
    Graph *gptr = (Graph *) malloc(sizeof(Graph));
    gptr->capacity = capacity;
    gptr->nodes = (Node **) malloc(sizeof(Node *) * capacity);
    gptr->num_nodes = 0;
    return gptr;
}

Graph *add_node(Graph* gptr, Node *nptr) {
    assert(gptr->num_nodes < gptr->capacity);
    gptr->nodes[gptr->num_nodes++] = nptr;
    return gptr;
}

Graph *add_edge(Graph *gptr, int idx1, int idx2) {
    Node *parent = gptr->nodes[idx1];
    assert(parent->num_neighbours < parent->capacity);
    parent->neighbours[parent->num_neighbours++] = idx2;
    return gptr;
}

void print(Graph *gptr) {
    for (int i = 0; i < gptr->num_nodes; ++i) {
        printf("node %d: neighbours: ", i);
        for (int j = 0; j < gptr->nodes[i]->num_neighbours; ++j) {
            printf("%d ", gptr->nodes[i]->neighbours[j]);
        }
        printf("\n");
    }
}

Graph *initialize_from_file(const char *fname) {
    FILE *fin = fopen(fname, "r");
    if (fin == NULL) {
        printf("error opening %s\n", fname);
        return NULL;
    }

    Graph *g = NULL;
    int nnodes_in;

    fscanf(fin, "%d\n", &nnodes_in);
    // printf("creating graph with %d nodes...\n", nnodes_in); // debug
    g = new_graph(nnodes_in);
    for (int i = 0; i < nnodes_in; ++i) {
        int nneighbours_in;

        fscanf(fin, "%d ", &nneighbours_in);
        // printf("node %d, %d neighbours...\n", i, nneighbours_in);
        g = add_node(g, new_node(nneighbours_in));
        for (int j = 0; j < nneighbours_in; ++j) {
            int neighbour_in;
            fscanf(fin, "%d ", &neighbour_in);
            // printf("  adding neighbour %d...\n", j);
            g = add_edge(g, i, neighbour_in);
        }
        // printf("new node created\n");
    }
    return g;
}
