#include "State.h"
#include "assert.h"
#include "stdio.h"
#include "string.h"

const int MAX_STATES = 52;

int main(void) {
    char states[MAX_STATES][NAME_LENGTH + 1];
    State *neighbours[MAX_STATES];
    int colours[MAX_STATES];
    int num_states;

    FILE *fin = fopen("simple_graph.in", "r");
    if (fin == NULL) {
        printf("problem opening simple_graph.in\n");
        return -1;
    }

    fscanf(fin, "%d\n", &num_states);
    assert(num_states < MAX_STATES);

    char name_in[NAME_LENGTH + 1];
    int num_neighbours;
    for (int i = 0; i < num_states; ++i) {
        fscanf(fin, "%s %d\n", name_in, &num_neighbours);
        strcpy(states[i], name_in);
        neighbours[i] = NULL;
        colours[i] = 0;
        for (int j = 0; j < num_neighbours; ++j) {
            fscanf(fin, "%s ", name_in);
            neighbours[i] = add_state(neighbours[i], new_state(name_in));
        }
    }

    // for (int i = 0; i < num_states; ++i) {
    //     printf("%s, neighbours: ", states[i]);
    //     print(neighbours[i]);
    // }

    fclose(fin);
    return 0;
}
