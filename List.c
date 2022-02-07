#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* first;
} List;

void insert(List* list, const int val);

void clear_all(List* list);

void print(List* list);

void reverse(List* list);

int main(void) {
    List my_list = {NULL};

    for (int i = 0; i < 5; ++i) {
        insert(&my_list, i);
    }

    print(&my_list);

    reverse(&my_list);

    printf("\n");
    print(&my_list);

    clear_all(&my_list);

    if (my_list.first == NULL) {
        printf("all clear\n");
    }
    return 0;
}

void insert(List* list, const int val) {
    if (list->first == NULL) {
        list->first = malloc(sizeof(Node));
        list->first->data = val;
        list->first->next = NULL;
    }
    else {
        Node* new_node = malloc(sizeof(Node));
        new_node->data = val;
        new_node->next = list->first;
        list->first = new_node;
    }
}

void clear_all(List* list) {
    while (list->first != NULL) {
        Node* to_delete = list->first;
        list->first = list->first->next;
        free(to_delete);
    }
}

void print(List* list) {
    for (Node* np = list->first; np != NULL; np = np->next) {
        printf("%d\n", np->data);
    }
}

void reverse(List* list) {
    Node* prev = NULL;
    while (list->first->next != NULL) {
        Node* temp = list->first->next;
        list->first->next = prev;
        prev = list->first;
        list->first = temp;
    }
    list->first->next = prev;
}
