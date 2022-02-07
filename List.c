#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} node;

void insert_nodes(node* root, const int n);

void delete_nodes(node* root);

void print_list(node* const root);

void reverse_list(node* root);

int main(void) {
    node* root = NULL;

    insert_nodes(root, 5);

    print_list(root);

    delete_nodes(root);

    return 0;
}

void insert_nodes(node* root, const int n) {
    for (int i = 0; i < n; ++i) {
        printf("creating new node\n");
        node* new_node = malloc(sizeof(node));
        new_node->data = i;
        new_node->next = root;
        root = new_node;
        printf("%d\n", root->data);
    }
    return;
}

void delete_nodes(node* root) {
    while (root != NULL) {
        node* to_delete = root;
        root = root->next;
        free(to_delete);
    }
    free(root);
    return;
}

void print_list(node* const root) {
    if (root == NULL) {
        printf("Your list is empty, returning...\n");
        return;
    }

    for (node* np = root; np != NULL; np = np->next) {
        printf("%d\n", np->data);
    }
    printf("done\n");
    return;
}

void reverse_list(node* root) {
}
