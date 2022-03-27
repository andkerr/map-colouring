#include "assert.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

const int MAX_NAME_LEN = 2;

typedef struct ListNode ListNode;
struct ListNode {
  char *name;
  ListNode *next;
};
ListNode *new_node(char *name);
ListNode *add_node(ListNode *head, ListNode *nptr);
ListNode *free_ListNodes(ListNode *head);
void apply(ListNode *head, void (*fn)(ListNode *, void *), void *arg);

void print_ListNode(ListNode *nptr, void *arg) {
  char *fmt = (char *) arg;
  printf(fmt, nptr->name);
}

typedef struct BSTNode BSTNode;
struct BSTNode {
  char *name;
  int colour;
  ListNode *neighbours;

  BSTNode *left;
  BSTNode *right;
};
BSTNode *new_BSTNode(char *name);
BSTNode *insert(BSTNode *root, BSTNode *rptr);
BSTNode *add_neighbour(BSTNode *root, ListNode *nptr);
BSTNode *lookup(BSTNode **root, char *name, int create);
BSTNode *free_BSTNodes(BSTNode *head);
void apply_inorder(BSTNode *root, void (*fn)(BSTNode *, void *), void *arg);

void print_BSTNode(BSTNode *nptr, void *arg) {
  char *fmt = (char *) arg;
  printf(fmt, nptr->name);

  apply(nptr->neighbours, print_ListNode, "%s ");
  printf("\n");
}

int main(void) {
  // goal:
  //    BSTNode *current = lookup('ME');
  //    current = add_neighbour(current, new_node('NH'));
  BSTNode *map = NULL;

  FILE *fin = fopen("usa_edges.in", "r");
  if (fin == NULL) {
    printf("error opening usa_edges.in\n");
    return -1;
  }

  char u[MAX_NAME_LEN + 1];
  char v[MAX_NAME_LEN + 1];
  while (fscanf(fin, "%s %s\n", u, v) == 2) {
    BSTNode *node_u = lookup(&map, u, 1);
    BSTNode *node_v = lookup(&map, v, 1);
    node_u = add_neighbour(node_u, new_node(v));
    node_v = add_neighbour(node_v, new_node(u));
  }

  apply_inorder(map, print_BSTNode, "%s, neighbours: ");

  free_BSTNodes(map);
}

ListNode *new_node(char *name) {
  ListNode *new_node = malloc(sizeof(ListNode));
  if (new_node != NULL) {
    new_node->name = (char *) malloc(sizeof(char) * (strlen(name) + 1));
    if (new_node->name != NULL) {
      strcpy(new_node->name, name);
    }
    new_node->next = NULL;
  }
  return new_node;
}

ListNode *add_node(ListNode *head, ListNode *nptr) {
  nptr->next = head;
  head = nptr;
  return head;
}

ListNode *free_ListNodes(ListNode *head) {
  ListNode *to_free;
  while (head != NULL) {
    free(head->name);
    to_free = head;
    head = head->next;
    free(to_free);
  }
  return head;
}

void apply(ListNode *head, void (*fn)(ListNode *, void *), void *arg) {
  for ( ; head != NULL; head = head->next) {
    (*fn)(head, arg);
  }
}

BSTNode *new_BSTNode(char *name) {
  BSTNode *new_node = malloc(sizeof(BSTNode));
  if (new_node != NULL) {
    new_node->name = (char *) malloc(sizeof(char) * (strlen(name) + 1));
    if (new_node->name != NULL) {
      strcpy(new_node->name, name);
    }
    new_node->colour = -1;
    new_node->neighbours = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
  }
  return new_node;
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
  root->neighbours = add_node(root->neighbours, nptr);
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
