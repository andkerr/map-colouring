#include "assert.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

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
Region *add_neighbour(Region *rptr, Node *nptr);
Region *free_regions(Region *head);

Region *map[MAX_REGIONS];

enum {MULTIPLIER = 31};

unsigned int hash(char *str);
Region *lookup(char *name, int create);


int main(void) {
  // goal:
  //    Region *current = lookup('ME');
  //    current = add_neighbour(current, new_node('NH'));

  Region *nh = lookup("NH", 1);
  printf("%s\n", nh->name);

  for (int i = 0; i < MAX_REGIONS; ++i) {
    map[i] = free_regions(map[i]);
  }
}

Node *new_node(char *datum) {
  Node *new_node = malloc(sizeof(Node));
  if (new_node != NULL) {
    new_node->datum = (char *) malloc(sizeof(char) * (strlen(datum) + 1));
    if (new_node->datum != NULL) {
      strcpy(new_node->datum, datum);
    }
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
    free(head->datum);
    to_free = head;
    head = head->next;
    free(to_free);
  }
  return head;
}

Region *new_region(char *name) {
  Region *rptr = malloc(sizeof(Region));
  if (rptr != NULL) {
    rptr->name = (char *) malloc(sizeof(char) * (strlen(name) + 1));
    if (rptr->name != NULL) {
      strcpy(rptr->name, name);
    }
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

Region *add_neighbour(Region *rptr, Node *nptr) {
  assert(rptr != NULL);
  rptr->neighbours = add_node(rptr->neighbours, nptr);
  return rptr;
}

Region *free_regions(Region *head) {
  while (head != NULL) {
    free(head->name);
    head->neighbours = free_nodes(head->neighbours);
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

Region *lookup(char *name, int create) {
  int h = hash(name);
  Region *rptr;

  for (rptr = map[h]; rptr != NULL; rptr = rptr->next) {
    if (strcmp(name, rptr->name) == 0) {
      return rptr;
    }
  }
  if (create) {
    assert(rptr == NULL);
    rptr = add_region(rptr, new_region(name));
  }
  return rptr;
}
