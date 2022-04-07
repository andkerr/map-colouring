#include "assert.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

const int MAX_NAME_LEN = 2;
const int NUM_COLOURS = 4; // 4-colour theorem, oh yeah...

enum colour {
  ORANGE,
  GREEN,
  PURPLE,
  YELLOW
};

typedef struct ListNode ListNode;
struct ListNode {
  char *name;
  ListNode *next;
};
ListNode *new_ListNode(char *name);
ListNode *push(ListNode *head, ListNode *nptr);
ListNode *pop(ListNode *head);
ListNode *free_ListNodes(ListNode *head);

// Linked List traversal functions
void apply(ListNode *head, void (*fn)(ListNode *, void *), void *arg);
void print_ListNode(ListNode *nptr, void *arg);
void get_neighbour_cols(ListNode *nptr, void *arg);

// For representing an arbitrary map region that
// can be inserted into an ordered map.
typedef struct BSTNode BSTNode;
struct BSTNode {
  char *name;
  int colour;
  int visited;
  ListNode *neighbours;

  BSTNode *left;
  BSTNode *right;
};
BSTNode *new_BSTNode(char *name);
BSTNode *insert(BSTNode *root, BSTNode *rptr);
BSTNode *add_neighbour(BSTNode *root, ListNode *nptr);
BSTNode *lookup(BSTNode **root, char *name, int create);
BSTNode *free_BSTNodes(BSTNode *head);

// BST traversal functions
void apply_inorder(BSTNode *root,
                   void (*fn)(BSTNode *, void *), void *arg);
void print_BSTNode(BSTNode *nptr, void *arg);
void assign_colour(BSTNode *nptr, void *arg);

// Global ordered map object. In the future, it may be smart to update
// function signatures that act on the map to accept it as a parameter,
// instead of requiring that they access the global object directly.
BSTNode *map = NULL;
int init_map(BSTNode **map, char *fname);
void colour(BSTNode *map);

int main(void) {
  if (init_map(&map, "usa_edges.in") != 0) {
    return -1;
  }
  apply_inorder(map, print_BSTNode, "name: %s, colour: %d, neighbours: ");

  free_BSTNodes(map);
}

ListNode *new_ListNode(char *name) {
  ListNode *new_ListNode = malloc(sizeof(ListNode));
  if (new_ListNode != NULL) {
    new_ListNode->name = (char *) malloc(sizeof(char) * (strlen(name) + 1));
    if (new_ListNode->name != NULL) {
      strcpy(new_ListNode->name, name);
    }
    new_ListNode->next = NULL;
  }
  return new_ListNode;
}

ListNode *push(ListNode *head, ListNode *nptr) {
  nptr->next = head;
  head = nptr;
  return head;
}

ListNode *pop(ListNode *head) {
  ListNode *to_free;
  free(head->name);
  to_free = head;
  head = head->next;
  free(to_free);
  return head;
}

ListNode *free_ListNodes(ListNode *head) {
  while (head != NULL) {
    head = pop(head);
  }
  return head;
}

void apply(ListNode *head, void (*fn)(ListNode *, void *), void *arg) {
  for ( ; head != NULL; head = head->next) {
    (*fn)(head, arg);
  }
}

BSTNode *new_BSTNode(char *name) {
  BSTNode *new_BSTNode = malloc(sizeof(BSTNode));
  if (new_BSTNode != NULL) {
    new_BSTNode->name = (char *) malloc(sizeof(char) * (strlen(name) + 1));
    if (new_BSTNode->name != NULL) {
      strcpy(new_BSTNode->name, name);
    }
    new_BSTNode->colour = -1;
    new_BSTNode->visited = 0;
    new_BSTNode->neighbours = NULL;
    new_BSTNode->left = NULL;
    new_BSTNode->right = NULL;
  }
  return new_BSTNode;
}

BSTNode *insert(BSTNode *root, BSTNode *nptr) {
  if (root == NULL) {
    return nptr;
  }
  else {
    if (strcmp(nptr->name, root->name) < 0) {
      root->left = insert(root->left, nptr);
    }
    else if (strcmp(nptr->name, root->name) > 0) {
      root->right = insert(root->right, nptr);
    }
    else {
      assert(0);
    }
    return root;
  }
}

BSTNode *add_neighbour(BSTNode *root, ListNode *nptr) {
  assert(root != NULL);
  root->neighbours = push(root->neighbours, nptr);
  return root;
}

BSTNode *find(BSTNode *root, char *name) {
  if (root == NULL) {
    return root;
  }
  else {
    if (strcmp(name, root->name) < 0) {
      return find(root->left, name);
    }
    else if (strcmp(name, root->name) > 0) {
      return find(root->right, name);
    }
    else {
      return root;
    }
  }
}

BSTNode *lookup(BSTNode **root, char *name, int create) {
  BSTNode *match = find(*root, name);
  if (match != NULL) {
    return match;
  }
  else {
    if (create) {
      match = new_BSTNode(name);
      *root = insert(*root, match);
    }
    return match;
  }
}

BSTNode *free_BSTNodes(BSTNode *root) {
  if (root != NULL) {
    root->left = free_BSTNodes(root->left);
    root->right = free_BSTNodes(root->right);
    root->neighbours = free_ListNodes(root->neighbours);
    free(root->name);
    free(root);
    return root = NULL;
  }
  return root;
}

void apply_inorder(BSTNode *root,
                   void (*fn)(BSTNode *, void *), void *arg) {
  if (root == NULL) {
    return;
  }
  else {
    apply_inorder(root->left, fn, arg);
    (*fn)(root, arg);
    apply_inorder(root->right, fn, arg);
  }
}

void print_ListNode(ListNode *nptr, void *arg) {
  char *fmt = (char *) arg;
  printf(fmt, nptr->name);
}

void get_neighbour_cols(ListNode *nptr, void *arg) {
  int *used_cols = (int *) arg;
  BSTNode *neighbour = lookup(&map, nptr->name, 0);
  assert(neighbour != NULL);
  int colour = neighbour->colour;

  if (colour == ORANGE) {
    used_cols[ORANGE] = 1;
  }
  else if (colour == GREEN) {
    used_cols[GREEN] = 1;
  }
  else if (colour == PURPLE) {
    used_cols[PURPLE] = 1;
  }
  else if (colour == YELLOW) {
    used_cols[YELLOW] = 1;
  }
}

void print_BSTNode(BSTNode *nptr, void *arg) {
  char *fmt = (char *) arg;
  printf(fmt, nptr->name, nptr->colour);

  apply(nptr->neighbours, print_ListNode, "%s ");
  printf("\n");
}

void assign_colour(BSTNode *nptr, void *arg) {
  int used_cols[NUM_COLOURS] = {0, 0, 0, 0};
  apply(nptr->neighbours, get_neighbour_cols, used_cols);
  // printf("%s, neighbour colours -> %d %d %d %d\n", nptr->name,
  //        used_cols[0], used_cols[1], used_cols[2], used_cols[3]);
}

int init_map(BSTNode **map, char *fname) {
  FILE *fin = fopen(fname, "r");
  if (fin == NULL) {
    printf("error opening usa_edges.in\n");
    return -1;
  }

  char u[MAX_NAME_LEN + 1];
  char v[MAX_NAME_LEN + 1];
  while (fscanf(fin, "%s %s\n", u, v) == 2) {
    BSTNode *node_u = lookup(map, u, 1);
    BSTNode *node_v = lookup(map, v, 1);
    node_u = add_neighbour(node_u, new_ListNode(v));
    node_v = add_neighbour(node_v, new_ListNode(u));
  }
  if (map == NULL) {
    printf("map empty, exiting...");
    return -2;
  }

  return 0;
}

void colour(BSTNode *map) {
  // Perform a breadth-first traversal of map, assigning colours along
  // the way. A node is chosen (for now arbitrarily) to initally populate
  // the list of to-be-visited map regions.
  ListNode *to_visit_front = NULL; ListNode *to_visit_back = NULL;

  BSTNode *first = map;
  first->visited = 1;
  to_visit_back = push(to_visit_back, new_ListNode(first->name));
  while (to_visit_front != NULL || to_visit_back != NULL) {
    if (to_visit_front == NULL) {
      while (to_visit_back != NULL) {
        to_visit_front = push(to_visit_front,
                              new_ListNode(to_visit_back->name));
        to_visit_back = pop(to_visit_back);
      }
    }

    BSTNode *current = lookup(&map, to_visit_front->name, 0);
    assert(current != NULL);
    to_visit_front = pop(to_visit_front);

    ListNode *neighbour_key = current->neighbours;
    for ( ; neighbour_key != NULL; neighbour_key = neighbour_key->next) {
      BSTNode *neighbour = lookup(&map, neighbour_key->name, 0);
      assert(neighbour != NULL);
      if (!neighbour->visited) {
        to_visit_back = push(to_visit_back, new_ListNode(neighbour->name));
        neighbour->visited = 1;
      }
    }

    assign_colour(current, NULL);
  }
}
