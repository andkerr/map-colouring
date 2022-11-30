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
} queue_t;

void queue_init(queue_t *qptr);
void queue_push(queue_t *qptr, int elt);
void queue_pop(queue_t *qptr);
int queue_top(queue_t *qptr);
int queue_empty(queue_t *qptr);

void assign_colours(int g[MAXNODES][MAXNODES],
                    int n_neighbours[MAXNODES],
                    int colours[MAXNODES],
                    int nNodes);

int main() {
    int g[MAXNODES][MAXNODES];
    int n_neighbours[MAXNODES];
    int colours[MAXNODES];
    int nNodes = 0;

    for (int i = 0; i < MAXNODES; ++i) {
        colours[i] = NONE;
        n_neighbours[i] = 0;
    }

    int u, v;
    while(scanf("%d %d\n", &u, &v) == 2) {
        g[u][n_neighbours[u]] = v;
        ++n_neighbours[u];
        if (n_neighbours[u] == 1) {
            ++nNodes;
        }

        g[v][n_neighbours[v]] = u;
        ++n_neighbours[v];
        if (n_neighbours[v] == 1) {
            ++nNodes;
        }
    }

#ifdef DEBUG
    printf("node | neighbours\n"
           "-----------------\n");
    for (int i = 0; i < nNodes; ++i) {
        printf("  %d  | ", i);
        for (int j = 0; j < n_neighbours[i]; ++j) {
            printf("%d ", g[i][j]);
        }
        printf("\n");
    }
    
    printf("\ncomputing the answer to life, the universe, and everything...\n");
#endif

    assign_colours(g, n_neighbours, colours, nNodes);

#ifdef DEBUG
    printf("\n");
    printf("node | colour\n"
           "-----------------\n");
    for (int i = 0; i < nNodes; ++i) {
        printf("  %d  | %s\n", i, COLOUR_STR[colours[i]]);
    }
#else
    for (int i = 0; i < nNodes; ++i) {
        printf("%d %d\n", i, colours[i]);
    }
#endif

    return(0);
}

void queue_init(queue_t *qptr) {
    qptr->front = 0;
    qptr->back = 0;
}

void queue_push(queue_t *qptr, int elt) {
    if ((qptr->back + 1) % MAXNODES == qptr->front) {
        printf("error: Queue full\n");
        exit(1);
    }
    qptr->data[qptr->back] = elt;
    qptr->back = (qptr->back + 1) % MAXNODES;
}

void queue_pop(queue_t *qptr) {
    if (queue_empty(qptr)) {
        printf("error: Queue empty\n");
        exit(1);
    }

    qptr->front = (qptr->front + 1) % MAXNODES;
}

int top(queue_t *qptr) {
    if(queue_empty(qptr)) {
        printf("error: Queue empty\n");
        exit(1);
    }

    return qptr->data[qptr->front];
}

int queue_empty(queue_t *qptr) {
    return qptr->front == qptr->back;
}

void assign_colours(int g[MAXNODES][MAXNODES],
                   int n_neighbours[MAXNODES],
                   int colours[],
                   int nNodes) {
    queue_t search;
    queue_t *sptr = &search;
    queue_init(sptr);

    int discovered[nNodes]; /* assume nodes are numbered [0, n) */
    for (int i = 0; i < nNodes; ++i) {
        discovered[i] = 0;
    }

    queue_push(sptr, 0); /* first node */
    discovered[0] = 1;

    int current, neighbour;
    int red, green, blue, yellow;
    while (!queue_empty(sptr)) {
        current = top(sptr);
        queue_pop(sptr);

        red = green = blue = yellow = 1;
        for (int i = 0; i < n_neighbours[current]; ++i) {
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
                queue_push(sptr, neighbour);
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
