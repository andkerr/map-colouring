#include "stdio.h"
#include "stdlib.h"
#include "string.h"

const int NAME_LENGTH = 2;
const int COLOUR_LENGTH = 2;

typedef struct Edge {
    struct Node* child;
    struct Edge* next;
} Edge;

typedef struct Node {
    char name[NAME_LENGTH + 1];
    char colour[COLOUR_LENGTH + 1];
    int num_neighbours;

    Edge* edges;
    struct Node* next;
} Node;

void add_node(Node* graph, Node* n);
void add_edge(struct Node* n1, struct Node* n2);
void print_neighbours(struct Node* n);
void destroy_graph(Node* graph);
void destroy_edges(Node* n);

int main(void) {
    FILE* fin = fopen("states.in", "r");
    if (!fin) {
        printf("error opening 3states.in\n");
        return -1;
    }

    Node* graph = NULL;
    int num_nodes, num_edges;
    fscanf(fin, "%d %d\n", &num_nodes, &num_edges);

    char name_buf[NAME_LENGTH + 1]; // room for null_terminator
    for (int i = 0; i < num_nodes; ++i) {
        fscanf(fin, "%s\n", name_buf);

        Node* nptr = malloc(sizeof(Node));
        strcpy(nptr->name, name_buf);
        strcpy(nptr->colour, "NA");
        nptr->num_neighbours = 0;
        nptr->edges = NULL;

        nptr->next = graph;
        graph = nptr;
    }

    char n1_buf[NAME_LENGTH + 1];
    char n2_buf[NAME_LENGTH + 1];
    for (int i = 0; i < num_edges; ++i) {
        fscanf(fin, "%s %s\n", n1_buf, n2_buf);

        Node* edge_end_1 = NULL;
        Node* edge_end_2 = NULL;

        for (Node* n = graph; n != NULL; n = n->next) {
            if (strcmp(n->name, n1_buf) == 0) {
                edge_end_1 = n;
            }
            if (strcmp(n->name, n2_buf) == 0) {
                edge_end_2 = n;
            }
        }

        if (!edge_end_1 || !edge_end_2) {
            printf("problem creating edge");
            printf("%s %s,\n", n1_buf, n2_buf);
            printf("one of the nodes does not exist\n");
            return -2;
        }
        else {
            add_edge(edge_end_1, edge_end_2);
        }

    }

    for (Node* n = graph; n != NULL; n = n->next) {
        print_neighbours(n);
    }

    destroy_graph(graph);
}

void add_node(Node* graph, Node* n) {
    n->next = graph;
    graph = n; // is this the trouble line, assigning to a local copy of graph?
}

void add_edge(struct Node* n1, struct Node* n2) {
    Edge* e1 = malloc(sizeof(Edge)); // allocate new edges
    Edge* e2 = malloc(sizeof(Edge));

    e1->child = n2; // point edges to the "child" nodes
    e2->child = n1;

    e1->next = n1->edges; // connect edges to their parent nodes' other edges
    e2->next = n2->edges;

    n1->edges = e1; // reset parent nodes' edge pointers to the new edges
    n2->edges = e2;
}

void print_neighbours(struct Node* n) {
    printf("neighbours to %s: ", n->name);
    for (Edge* e = n->edges; e != NULL; e = e->next) {
        printf("%s, ", e->child->name);
    }
    printf("\n");
}

void destroy_graph(Node* graph) {
    while (graph != NULL) {
        Node* to_delete = graph;
        destroy_edges(to_delete);
        graph = to_delete->next;
        free(to_delete);
    }
}

void destroy_edges(Node* n) {
    while (n->edges != NULL) {
        Edge* to_delete = n->edges;
        n->edges = n->edges->next;
        free(to_delete);
    }
}
