#include "stdio.h"
#include "stdlib.h"

const int MAX_REGIONS = 65536;

typedef struct Node Node;
struct Node {
  char *datum;
  Node *next;
};
Node *new_node(char *name);
Node *add_node(Node *head, Node *nptr);
Node *free_nodes(Node *head);

typedef struct Region Region;
struct Region {
  char *name;
  int colour;
  Node *neighbours;

  Region *next;
};
Region *new_region(char *name);
Region *add_region(Region *head, Region *rptr);
Region *free_regions(Region *head);

Region *map[MAX_REGIONS];

enum {MULTIPLIER = 31};

unsigned int hash(char *str);
Region *lookup(char *name, int create, int value);


int main(void) {
  printf("hello, world\n");
  // goal:
  //    Region *current = lookup('ME');
  //    current = add_neighbour(current, new_node('NH'));
}

Node *new_node(char *datum) {
  Node *new_node = malloc(sizeof(Node));
  if (new_node != NULL) {
    new_node->datum = datum;
    new_node->next = NULL;
  }
  return new_node;
}

Node *add_node(Node *head, Node *nptr) {
  nptr->next = head;
  head = nptr;
  return head;
}

Node *free_nodes(Node *head) {
  Node *to_free;
  while (head != NULL) {
    to_free = head;
    head = head->next;
    free(to_free);
  }
  return head;
}

Region *new_region(char *name) {
  Region *rptr = malloc(sizeof(Region));
  if (rptr != NULL) {
    rptr->name = name;
    rptr->colour = -1;
    rptr->neighbours = NULL;
  }

  return rptr;
}

Region *add_region(Region *head, Region *rptr) {
  rptr->next = head;
  head = rptr;
  return head;
}

Region *free_regions(Region *head) {
  while (head != NULL) {
    Region *to_free = head;
    head = head->next;
    free(to_free);
  }

  return head;
}

unsigned int hash(char *str) {
  unsigned int h = 0;
  for (unsigned char *p = (unsigned char *) str; *p != '\0'; ++p) {
    h = MULTIPLIER * h + *p;
  }
  return h % MAX_REGIONS;
}

Region *lookup(char *name, int create, int value) {
  int h = hash(name);
  Region *rptr;

  for (rptr = map[h]; rptr != NULL; rptr = rptr->next) {
    if (strcmp(name, rptr->name) == 0) {
      return rptr;
    }
  }
  if (create) {
    rptr = new_region(name);
  }
}
