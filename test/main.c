#include <stdio.h>
#include "../src/malloc.h"

int main()
{
  char *name;

  printf("\n======== TEST START\n");
  name = malloc(17);
  name = malloc(sizeof(int));
  free(name);
  printf("======== TEST END\n");
  return 0;
}
