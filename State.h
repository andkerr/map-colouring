#ifndef STATE_H
#define STATE_H

#define NAME_LENGTH 2

typedef struct State State;
struct State {
    char name[NAME_LENGTH + 1];
    State *next;
};

State *new_state(char* name);

State *add_state(State *n_list, State *sptr);

void print(State *n_list);

#endif
