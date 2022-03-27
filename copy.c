#include "stdio.h"
#include "stdlib.h"
#include "string.h"

char *init_string(char *s_in) {
  char *copy = (char * ) malloc(sizeof(char) * (strlen(s_in) + 1));
  if (copy != NULL) {
    strcpy(copy, s_in);
  }
  return copy;
}

int main(void) {
  char *str = init_string("yo");
  if (str != NULL) {
    printf("%s\n", str);
  }
}
