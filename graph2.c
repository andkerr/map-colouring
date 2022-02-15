#include "stdio.h"

const int NUM_STATES = 3;

typedef struct Node {
    char* name;
    char* colour;
    int num_neighbours;
    struct Node* neighbours[NUM_STATES];
} Node;

void add_edge(struct Node* n1, struct Node* n2);
void print_neighbours(struct Node* n);

int main() {
    Node ma = {"MA", "NONE", 0};
    Node vt = {"VT", "NONE", 0};
    Node nh = {"NH", "NONE", 0};

    add_edge(&ma, &vt);
    add_edge(&ma, &nh);
    add_edge(&vt, &nh);

    print_neighbours(&ma);
    print_neighbours(&vt);
    print_neighbours(&nh);
}

void add_edge(struct Node* n1, struct Node* n2) {
    n1->neighbours[n1->num_neighbours++] = n2;
    n2->neighbours[n2->num_neighbours++] = n1;
}

void print_neighbours(struct Node* n) {
    printf("neighbours to %s: ", n->name);
    for (int i = 0; i < n->num_neighbours; ++i) {
        printf("%s, ", n->neighbours[i]->name);
    }
    printf("\n");
}
