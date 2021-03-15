#include <stdio.h>
#include <stdlib.h>

int main()
{
  char *x = (char *)malloc(10 * sizeof(char *));
  char *x_shadow = x;
  free(x);

  return x[5];
}
