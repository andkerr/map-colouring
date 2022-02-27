#include "State.h"
#include "assert.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

State *new_state(char* name) {
    State *new = (State *) malloc(sizeof(State));
    strcpy(new->name, name);
    new->next = NULL;
    return new;
}

State *add_state(State *n_list, State *sptr) {
    sptr->next = n_list;
    n_list = sptr;
    return n_list;
}

void print(State *n_list) {
    while(n_list) {
        printf("%s ", n_list->name);
        n_list = n_list->next;
    }
    printf("\n");
}
