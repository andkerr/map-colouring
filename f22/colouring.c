#include <stdio.h>
#include <stdlib.h>

#define MAXNODES 1000

enum COLOURS {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    NONE,
};

const char *COLOUR_STR[4] = {"RED", "GREEN", "BLUE", "YELLOW"};

typedef struct Queue {
    int data[MAXNODES];
    size_t front;
    size_t back;
} Queue;

void defaultInit(Queue *qptr);
void push_back(Queue *qptr, int elt);
void pop_front(Queue *qptr);
int top(Queue *qptr);
int empty(Queue *qptr);

void assignColours(int g[MAXNODES][MAXNODES],
                   int neighbourCounts[MAXNODES],
                   int colours[MAXNODES],
                   int nNodes);

int main() {

    int g[MAXNODES][MAXNODES];
    int neighbourCounts[MAXNODES];
    int colours[MAXNODES];
    int nNodes = 0;

    for (size_t i = 0; i < MAXNODES; ++i) {
        colours[i] = NONE;
        neighbourCounts[i] = 0;
    }

    int u, v;
    while(scanf("%d %d\n", &u, &v) == 2) {
        g[u][neighbourCounts[u]] = v;
        ++neighbourCounts[u];
        if (neighbourCounts[u] == 1) {
            ++nNodes;
        }

        g[v][neighbourCounts[v]] = u;
        ++neighbourCounts[v];
        if (neighbourCounts[v] == 1) {
            ++nNodes;
        }
    }

    printf("node | neighbours\n"
           "-----------------\n");
    for (size_t i = 0; i < nNodes; ++i) {
        printf("  %zu  | ", i);
        for (size_t j = 0; j < neighbourCounts[i]; ++j) {
            printf("%d ", g[i][j]);
        }
        printf("\n");
    }
    
    printf("\ncomputing the answer to life, the universe, and everything...\n");
    assignColours(g, neighbourCounts, colours, nNodes);

    printf("\n");
    printf("node | colour\n"
           "-----------------\n");
    for (size_t i = 0; i < nNodes; ++i) {
        printf("  %zu  | %s\n", i, COLOUR_STR[colours[i]]);
    }

    return(0);
}

void defaultInit(Queue *qptr) {
    qptr->front = 0;
    qptr->back = 0;
}

void push_back(Queue *qptr, int elt) {
    if ((qptr->back + 1) % MAXNODES == qptr->front) {
        printf("error: Queue full\n");
        exit(1);
    }
    qptr->data[qptr->back] = elt;
    qptr->back = (qptr->back + 1) % MAXNODES;
}

void pop_front(Queue *qptr) {
    if (empty(qptr)) {
        printf("error: Queue empty\n");
        exit(1);
    }

    qptr->front = (qptr->front + 1) % MAXNODES;
}

int top(Queue *qptr) {
    if(empty(qptr)) {
        printf("error: Queue empty\n");
        exit(1);
    }

    return qptr->data[qptr->front];
}

int empty(Queue *qptr) {
    return qptr->front == qptr->back;
}

void assignColours(int g[MAXNODES][MAXNODES],
                   int neighbourCounts[MAXNODES],
                   int colours[],
                   int nNodes) {
    Queue search;
    Queue *sptr = &search;
    defaultInit(sptr);

    int discovered[nNodes]; /* assume nodes are numbered [0, n) */
    for (size_t i = 0; i < nNodes; ++i) {
        discovered[i] = 0;
    }

    push_back(sptr, 0); /* first node */
    discovered[0] = 1;

    int current, neighbour;
    int red, green, blue, yellow;
    while (!empty(sptr)) {
        current = top(sptr);
        pop_front(sptr);

        red = green = blue = yellow = 1;
        for (size_t i = 0; i < neighbourCounts[current]; ++i) {
            neighbour = g[current][i];
            switch (colours[neighbour]) {
                case RED:
                    red = 0;
                    break;
                case GREEN:
                    green = 0;
                    break;
                case BLUE:
                    blue = 0;
                    break;
                case YELLOW:
                    yellow = 0;
                    break;
            }
            
            if (!discovered[neighbour]) {
                push_back(sptr, neighbour);
                discovered[neighbour] = 1;
            }
        }

        if (red) {
            colours[current] = RED;
        }
        else if (green) {
            colours[current] = GREEN;
        }
        else if (blue) {
            colours[current] = BLUE;
        }
        else if (yellow) {
            colours[current] = YELLOW;
        }
        else {
            printf("error: unable to assign a valid 4-colouring\n");
            exit(1);
        }
    }
}
